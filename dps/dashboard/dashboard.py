"""VPython dashboard with a scalar Kalman filter for an MPU6050.

The filter follows the supplied paper: gyro angular rate predicts roll/pitch
and the gravity angle calculated from the accelerometer corrects that estimate.
The Arduino sketch paired with this file sends the M2 packet format documented
in ``read_telemetry`` below.
"""

from vpython import *
import struct
import time

import numpy as np
import serial


# ---------------------------------------------------------------------------
# SERIAL PROTOCOL AND TUNING
# ---------------------------------------------------------------------------

SERIAL_PORT = "COM9"
BAUD_RATE = 115200
PACKET_SIZE = 100

# M2 is the updated form of the supplied sketch. It changes only floats 3..5:
# M1: roll, pitch, yaw already calculated by Madgwick.
# M2: gyro X, gyro Y, gyro Z in degrees/second, after bias calibration.
EXPECTED_SENDER = b"M2"
FLOAT_COUNT = 10

# The dashboard is declared offline after one second without a real packet.
# It holds the last pose; it does not invent motion while disconnected.
STALE_AFTER_SECONDS = 1.0
SERIAL_RETRY_SECONDS = 2.0

# Kalman noise terms. Both use degree units because the filter state is angle.
# - Raise GYRO_RATE_STD_DPS if the prediction follows the gyro too strongly.
# - Raise ACCEL_ANGLE_STD_DEG if gravity angles visibly shake while stationary.
GYRO_RATE_STD_DPS = 4.0
ACCEL_ANGLE_STD_DEG = 3.0

# Acceleration represents the gravity vector only when its norm is near 1 g.
# In free fall or under a strong thrust/impact we therefore skip the accel
# correction. This is essential for a CanSat and avoids false tilt readings.
ACCEL_GRAVITY_MIN_G = 0.85
ACCEL_GRAVITY_MAX_G = 1.15

# A severe isolated accelerometer angle is down-weighted rather than accepted
# as a full correction. This is a robust extension around the paper's S term.
ACCEL_SOFT_INNOVATION_DEG = 25.0

# If the board reports a temporary invalid IMU sample, retain the last valid
# gyro rate for a short Kalman-only prediction. The rate then decays smoothly
# to zero, so a longer hardware fault never makes the CanSat spin forever.
INVALID_SAMPLE_FULL_GYRO_SECONDS = 0.25
INVALID_SAMPLE_GYRO_DECAY_SECONDS = 0.50

DISPLAY_RATE_HZ = 60
GRAPH_HISTORY_POINTS = 600


def wrap_degrees(angle):
    """Map an angle difference into [-180, 180), avoiding 360 degree jumps."""
    return (angle + 180.0) % 360.0 - 180.0


class PaperKalmanAngle:
    """One-dimensional Kalman filter for either roll or pitch.

    State: angle in degrees.
    Input: gyro angular speed in degrees per second.
    Measurement: angle computed from the accelerometer gravity vector.
    """

    def __init__(self):
        self.angle = 0.0
        self.variance = ACCEL_ANGLE_STD_DEG ** 2  # Paper's Psi.
        self.initialized = False
        self.last_correction_used = False
        self.last_correction_softened = False
        self.last_gain = 0.0

    def update(self, gyro_rate_dps, accel_angle_deg, dt, accel_reliable):
        """Make one prediction and one possible accelerometer correction."""

        # An initial pose requires gravity. Hold the model until the CanSat is
        # still enough for at least one valid accelerometer reading.
        if not self.initialized:
            self.last_correction_used = False
            self.last_correction_softened = False
            self.last_gain = 0.0
            if accel_reliable:
                self.angle = accel_angle_deg
                self.variance = ACCEL_ANGLE_STD_DEG ** 2
                self.initialized = True
                self.last_correction_used = True
                self.last_gain = 1.0
            return

        # Paper prediction equations:
        #   theta_pred = theta_previous + gyro_rate * dt
        #   Psi_pred   = Psi_previous + (dt * sigma_gyro)^2
        predicted_angle = self.angle + gyro_rate_dps * dt
        predicted_variance = self.variance + (dt * GYRO_RATE_STD_DPS) ** 2

        self.last_correction_used = False
        self.last_correction_softened = False
        self.last_gain = 0.0

        if not accel_reliable:
            # No gravity reference exists in free fall, so retain gyro result.
            self.angle = predicted_angle
            self.variance = predicted_variance
            return

        # Accelerometer roll/pitch is periodic. Align it to the prediction
        # before computing the innovation so a -180/180 crossing is harmless.
        innovation = wrap_degrees(accel_angle_deg - predicted_angle)

        # The paper has a fixed accelerometer variance S. A very large single
        # innovation often comes from impact or linear acceleration, so use a
        # larger S and make that correction proportionally weaker.
        measurement_variance = ACCEL_ANGLE_STD_DEG ** 2
        if abs(innovation) > ACCEL_SOFT_INNOVATION_DEG:
            scale = abs(innovation) / ACCEL_SOFT_INNOVATION_DEG
            measurement_variance *= scale ** 2
            self.last_correction_softened = True

        # Paper correction equations:
        #   G     = Psi_pred / (Psi_pred + S)
        #   theta = theta_pred + G * innovation
        #   Psi   = (1 - G) * Psi_pred
        self.last_gain = (
            predicted_variance / (predicted_variance + measurement_variance)
        )
        self.angle = predicted_angle + self.last_gain * innovation
        self.variance = (1.0 - self.last_gain) * predicted_variance
        self.last_correction_used = True

    def predict_only(self, gyro_rate_dps, dt):
        """Advance the state without trusting an accelerometer measurement.

        This is used only while the microcontroller explicitly flags a
        temporary invalid I2C sample. Increasing the variance here means that
        the next valid measurement will be allowed to correct promptly.
        """
        self.last_correction_used = False
        self.last_correction_softened = False
        self.last_gain = 0.0

        if not self.initialized:
            return

        self.angle += gyro_rate_dps * dt
        self.variance += (dt * GYRO_RATE_STD_DPS) ** 2


def accelerometer_angles(acc_x, acc_y, acc_z):
    """Calculate roll and pitch from acceleration expressed in g."""
    roll = np.degrees(np.arctan2(acc_y, acc_z))
    pitch = np.degrees(
        np.arctan2(-acc_x, np.sqrt(acc_y ** 2 + acc_z ** 2))
    )
    return roll, pitch


def gravity_is_reliable(acc_x, acc_y, acc_z):
    """Return whether the sample can be used as a gravity measurement."""
    magnitude = float(np.sqrt(acc_x ** 2 + acc_y ** 2 + acc_z ** 2))
    return ACCEL_GRAVITY_MIN_G <= magnitude <= ACCEL_GRAVITY_MAX_G


def telemetry_values_are_finite(telemetry):
    """Reject NaN/Infinity packets before they reach the Kalman state."""
    values = (*telemetry["acceleration"], *telemetry["gyro"])
    return bool(np.all(np.isfinite(values)))


def open_serial_port():
    """Open the COM port, but leave the graphical UI alive when it fails."""
    try:
        connection = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0)
        connection.reset_input_buffer()
        print(f"Reading M2 telemetry from {SERIAL_PORT} at {BAUD_RATE} baud.")
        return connection
    except serial.SerialException as error:
        print(f"Cannot open {SERIAL_PORT}: {error}")
        return None


def read_telemetry(connection, buffer):
    """Return the newest valid M2 packet and whether a legacy M1 was seen.

    M2 packet (100 bytes):
      0..3   CSWS header
      4..5   M2 sender identifier
      6..7   GS receiver identifier
      8..47  10 little-endian floats:
              accX, accY, accZ, gyroX, gyroY, gyroZ,
              temperature, pressure, humidity, speed
      48     parachute status (preserved from the original protocol)
      49     I2C validity: 0 means a fresh MPU6050 sample; 255 means that the
             board could not obtain a fresh reading and sent its last values
             only to keep the telemetry heartbeat alive.
      96..99 DTLB footer
    """
    available = connection.in_waiting
    if available:
        buffer.extend(connection.read(available))

    newest = None
    saw_legacy_m1 = False

    while len(buffer) >= PACKET_SIZE:
        header_index = buffer.find(b"CSWS")
        if header_index == -1:
            # Keep possible first bytes of the next header.
            del buffer[:-3]
            break
        if header_index:
            del buffer[:header_index]
        if len(buffer) < PACKET_SIZE:
            break

        packet = bytes(buffer[:PACKET_SIZE])
        del buffer[:PACKET_SIZE]

        if packet[96:100] != b"DTLB":
            continue
        if packet[4:6] != EXPECTED_SENDER:
            saw_legacy_m1 = saw_legacy_m1 or packet[4:6] == b"M1"
            continue

        values = struct.unpack("<10f", packet[8:48])
        newest = {
            "acceleration": values[0:3],
            "gyro": values[3:6],
            "temperature": values[6],
            "pressure": values[7],
            "humidity": values[8],
            "speed": values[9],
            "parachute_status": packet[48],
            # Zero is deliberately the normal value so an early M2 sketch
            # without this diagnostic byte remains compatible.
            "imu_valid": packet[49] != 0xFF,
        }

    return newest, saw_legacy_m1


# ---------------------------------------------------------------------------
# VPYTHON VIEW
# ---------------------------------------------------------------------------

cansat_canvas = canvas(
    align="left",
    background=vec(0.15, 0.15, 0.15),
    width=750,
)
cansat_canvas.forward = vec(0, 1, 0)

cansat_body = cylinder(
    canvas=cansat_canvas,
    pos=vec(0, 0, 0),
    axis=vec(0, 0, 3),
    radius=0.8,
    color=vec(1, 0.84, 0),
    shininess=0.8,
    opacity=0.9,
)
rotating_parts = [cansat_body]

angle_x = 0.0
angle_y = 0.0
angle_z = 0.0

warning_label = label(
    pos=vec(0, 2, 0),
    text="Waiting for M2 IMU telemetry",
    color=color.red,
    height=18,
    box=True,
    background=color.white * 0.1,
    opacity=0.6,
)


def update_rotation():
    """Rotate the cylinder using current roll, pitch and yaw in radians."""
    rotation_z = np.array([
        [np.cos(angle_z), -np.sin(angle_z), 0],
        [np.sin(angle_z), np.cos(angle_z), 0],
        [0, 0, 1],
    ])
    rotation_y = np.array([
        [np.cos(angle_y), 0, np.sin(angle_y)],
        [0, 1, 0],
        [-np.sin(angle_y), 0, np.cos(angle_y)],
    ])
    rotation_x = np.array([
        [1, 0, 0],
        [0, np.cos(angle_x), -np.sin(angle_x)],
        [0, np.sin(angle_x), np.cos(angle_x)],
    ])

    new_axis = rotation_z @ rotation_y @ rotation_x @ np.array([0, 0, 3])
    for part in rotating_parts:
        part.axis = vec(new_axis[0], new_axis[1], new_axis[2])


atmospheric_pressure_graph = graph(
    title="<b>Atmospheric Pressure</b>",
    xtitle="<b>Sample</b>",
    ytitle="<b>Pressure (Pa)</b>",
    xmin=0,
    ymin=90000,
    fast=True,
    align="right",
    background=color.black,
    foreground=color.white,
    width=750,
)
atmospheric_pressure_curve = gcurve(
    graph=atmospheric_pressure_graph, color=color.red, width=4
)

temperature_graph = graph(
    title="<b>Temperature</b>",
    xtitle="<b>Sample</b>",
    ytitle="<b>Temperature (C)</b>",
    xmin=0,
    ymin=-10,
    fast=True,
    align="left",
    background=color.black,
    foreground=color.white,
    width=750,
)
temperature_curve = gcurve(graph=temperature_graph, color=color.cyan, width=4)

relative_humidity_graph = graph(
    title="<b>Relative Humidity</b>",
    xtitle="<b>Sample</b>",
    ytitle="<b>Humidity (%)</b>",
    xmin=0,
    ymin=0,
    ymax=100,
    fast=True,
    align="right",
    background=color.black,
    foreground=color.white,
    width=750,
)
relative_humidity_curve = gcurve(
    graph=relative_humidity_graph, color=color.green, width=4
)


def reset_graph_curves():
    """Prevent unbounded graph memory while preserving the dashboard layout."""
    global atmospheric_pressure_curve
    global temperature_curve
    global relative_humidity_curve

    atmospheric_pressure_curve.delete()
    temperature_curve.delete()
    relative_humidity_curve.delete()

    atmospheric_pressure_curve = gcurve(
        graph=atmospheric_pressure_graph, color=color.red, width=4
    )
    temperature_curve = gcurve(
        graph=temperature_graph, color=color.cyan, width=4
    )
    relative_humidity_curve = gcurve(
        graph=relative_humidity_graph, color=color.green, width=4
    )


# ---------------------------------------------------------------------------
# LIVE TELEMETRY LOOP
# ---------------------------------------------------------------------------

sample_index = 0
serial_connection = None
serial_buffer = bytearray()
next_serial_attempt = 0.0
last_packet_time = 0.0
last_imu_time = None
last_valid_imu_time = None
legacy_m1_seen = False
last_packet_sensor_valid = False
last_good_gyro = (0.0, 0.0, 0.0)
last_good_environment = None

roll_filter = PaperKalmanAngle()
pitch_filter = PaperKalmanAngle()
yaw_angle = 0.0


while True:
    now = time.monotonic()

    # An unplugged/reset board no longer terminates the dashboard. The program
    # holds the last real pose and automatically retries the port every 2 s.
    if serial_connection is None and now >= next_serial_attempt:
        serial_connection = open_serial_port()
        next_serial_attempt = now + SERIAL_RETRY_SECONDS
        serial_buffer.clear()

    telemetry = None
    if serial_connection is not None:
        try:
            telemetry, saw_legacy = read_telemetry(
                serial_connection, serial_buffer
            )
            legacy_m1_seen = legacy_m1_seen or saw_legacy
        except serial.SerialException as error:
            print(f"Serial connection lost: {error}")
            try:
                serial_connection.close()
            except serial.SerialException:
                pass
            serial_connection = None
            next_serial_attempt = now + SERIAL_RETRY_SECONDS

    if telemetry is not None:
        # A packet proves that serial is working. The packet may still contain
        # an invalid IMU sample, in which case only Kalman prediction is used.
        last_packet_time = now
        sample_is_valid = (
            telemetry["imu_valid"] and telemetry_values_are_finite(telemetry)
        )
        last_packet_sensor_valid = sample_is_valid
        legacy_m1_seen = False

        # Every heartbeat advances the model by a normal, bounded time step.
        # This is what prevents a transient invalid sample from freezing it.
        dt = 0.0 if last_imu_time is None else min(now - last_imu_time, 0.25)
        last_imu_time = now

        if sample_is_valid:
            last_valid_imu_time = now
            acc_x, acc_y, acc_z = telemetry["acceleration"]
            gyro_x, gyro_y, gyro_z = telemetry["gyro"]
            last_good_gyro = (gyro_x, gyro_y, gyro_z)

            accel_roll, accel_pitch = accelerometer_angles(acc_x, acc_y, acc_z)
            accel_reliable = gravity_is_reliable(acc_x, acc_y, acc_z)

            # The supplied sketch uses X gyro for roll and Y gyro for pitch.
            roll_filter.update(gyro_x, accel_roll, dt, accel_reliable)
            pitch_filter.update(gyro_y, accel_pitch, dt, accel_reliable)
            yaw_angle = wrap_degrees(yaw_angle + gyro_z * dt)
        elif last_valid_imu_time is not None:
            # The microcontroller sends the last good values while I2C is
            # recovering. Use them only as a short-term state prediction, not
            # as a new measurement. The exponential decay prevents a stale
            # gyro rate from rotating the 3D model indefinitely.
            invalid_age = now - last_valid_imu_time
            excess_age = max(0.0, invalid_age - INVALID_SAMPLE_FULL_GYRO_SECONDS)
            gyro_weight = np.exp(-excess_age / INVALID_SAMPLE_GYRO_DECAY_SECONDS)
            gyro_x, gyro_y, gyro_z = last_good_gyro

            roll_filter.predict_only(gyro_x * gyro_weight, dt)
            pitch_filter.predict_only(gyro_y * gyro_weight, dt)
            yaw_angle = wrap_degrees(yaw_angle + gyro_z * gyro_weight * dt)

        # Draw both corrected and predicted states. Nothing is redrawn from a
        # raw invalid angle, so a bad packet cannot force a visible jump.
        if roll_filter.initialized and pitch_filter.initialized:
            angle_x = np.radians(roll_filter.angle)
            angle_y = np.radians(pitch_filter.angle)
            angle_z = np.radians(yaw_angle)
            update_rotation()

        # The environmental plots also remain alive during an IMU recovery.
        # If those values are non-finite, repeat their last usable values.
        environment = (
            telemetry["pressure"],
            telemetry["temperature"],
            telemetry["humidity"],
        )
        if np.all(np.isfinite(environment)):
            last_good_environment = environment

        if last_good_environment is not None:
            if sample_index >= GRAPH_HISTORY_POINTS:
                reset_graph_curves()
                sample_index = 0

            pressure, temperature, humidity = last_good_environment
            atmospheric_pressure_curve.plot(sample_index, pressure)
            temperature_curve.plot(sample_index, temperature)
            relative_humidity_curve.plot(sample_index, humidity)
            sample_index += 1
    signal_age = now - last_packet_time if last_packet_time else float("inf")

    if legacy_m1_seen and last_packet_time == 0.0:
        warning_label.text = "M1 detected: upload the M2 MPU sketch"
        warning_label.color = color.red
    elif last_packet_time == 0.0:
        warning_label.text = "Waiting for M2 IMU telemetry"
        warning_label.color = color.red
    elif signal_age > STALE_AFTER_SECONDS:
        warning_label.text = "IMU offline: last real attitude held"
        warning_label.color = color.red
    elif not last_packet_sensor_valid:
        warning_label.text = "IMU sample invalid: Kalman prediction active"
        warning_label.color = color.orange
    elif not (roll_filter.initialized and pitch_filter.initialized):
        warning_label.text = "Waiting for a stable gravity sample"
        warning_label.color = color.orange
    elif not roll_filter.last_correction_used:
        warning_label.text = "Accel correction paused: free fall / acceleration"
        warning_label.color = color.orange
    elif (
        roll_filter.last_correction_softened
        or pitch_filter.last_correction_softened
    ):
        warning_label.text = "Large accel reading: Kalman correction softened"
        warning_label.color = color.orange
    else:
        warning_label.text = ""

    rate(DISPLAY_RATE_HZ)
