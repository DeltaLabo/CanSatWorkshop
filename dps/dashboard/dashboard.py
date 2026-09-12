from vpython import *
from collections import deque
import struct
import time
import numpy as np
import serial
from filterpy.common import Q_discrete_white_noise
from filterpy.kalman import KalmanFilter

# ---------------------------------------------------------------------------
# CONFIGURACIÓN
# ---------------------------------------------------------------------------

SERIAL_PORT = "COM9"
BAUD_RATE = 115200
PACKET_SIZE = 100

# Tras este tiempo sin una medición válida se muestra la predicción.
MAX_PREDICTION_SECONDS = 3.0

# Tras este tiempo se indica pérdida importante de telemetría.
STALE_AFTER_SECONDS = 5.0

# Ventana de mediciones válidas para estimar la velocidad angular.
VELOCITY_HISTORY_SECONDS = 1.0

# Rechaza mediciones a más de 3 desviaciones estándar de la predicción.
MEASUREMENT_GATE_SIGMA = 3.0

# Dos outliers similares consecutivos se consideran una maniobra real.
OUTLIER_CONFIRMATION_COUNT = 2
OUTLIER_CONFIRMATION_WINDOW_SECONDS = 0.7
OUTLIER_MATCH_DEGREES = 12.0

# Ajustes de Kalman.
MEASUREMENT_STD_DEG = 4.0
PROCESS_ACCELERATION_VARIANCE = 4.0

# Ajustes visuales.
DISPLAY_RATE_HZ = 30
VISUAL_SMOOTHING_HZ = 12.0
GRAPH_HISTORY_POINTS = 600


class AngleKalmanFilter:
    # Estado: [ángulo en grados, velocidad angular en grados/s].

    def __init__(self):
        self.filter = KalmanFilter(dim_x=2, dim_z=1)

        self.filter.x = np.array([[0.0], [0.0]])
        self.filter.H = np.array([[1.0, 0.0]])
        self.filter.P = np.diag([25.0, 100.0])
        self.filter.R = np.array([[MEASUREMENT_STD_DEG**2]])

        # Historial de mediciones aceptadas.
        self.history = deque()

        # Se usa para detectar maniobras reales bruscas.
        self.outlier_candidate = None
        self.outlier_candidate_time = 0.0
        self.outlier_candidate_count = 0

        self.initialized = False

    @property
    def angle(self):
        return float(self.filter.x[0, 0])

    def predict(self, dt, signal_age):
        # Este método se ejecuta siempre.
        self.filter.F = np.array([
            [1.0, dt],
            [0.0, 1.0]
        ])

        self.filter.Q = Q_discrete_white_noise(
            dim=2,
            dt=dt,
            var=PROCESS_ACCELERATION_VARIANCE
        )

        self.filter.predict()

        # Si no hay señal por mucho tiempo, frena la velocidad estimada.
        if signal_age > MAX_PREDICTION_SECONDS:
            self.filter.x[1, 0] *= np.exp(-1.5 * dt)

    def update_if_plausible(self, measurement, now):
        # Devuelve True si la medición es aceptada.

        if not self.initialized:
            self.filter.x[0, 0] = measurement
            self.initialized = True
            self.history.append((now, measurement))
            return True

        # Evita saltos grandes al cruzar -180 / 180 grados.
        residual = (measurement - self.angle + 180.0) % 360.0 - 180.0
        aligned_measurement = self.angle + residual

        # S = HPH' + R
        innovation_covariance = (
            self.filter.H @ self.filter.P @ self.filter.H.T + self.filter.R
        )

        innovation_std = float(np.sqrt(innovation_covariance[0, 0]))

        # Si la lectura se aleja demasiado, puede ser un outlier.
        if abs(residual) > MEASUREMENT_GATE_SIGMA * innovation_std:
            # Si se repite de forma coherente, se acepta como maniobra real.
            if self._confirm_outlier(measurement, now):
                self.filter.x[0, 0] = aligned_measurement
                self.filter.P[0, 0] = MEASUREMENT_STD_DEG**2
                self.filter.P[1, 1] = max(self.filter.P[1, 1], 100.0)

                self.history.append((now, self.angle))
                self._update_velocity_from_history(now)
                return True

            return False

        # Medición normal: corrige el filtro.
        self.filter.update(np.array([[aligned_measurement]]))

        self.history.append((now, self.angle))
        self._update_velocity_from_history(now)
        self._clear_outlier_candidate()

        return True

    def _confirm_outlier(self, measurement, now):
        # Requiere varios outliers similares para aceptar una maniobra brusca.

        if self.outlier_candidate is None:
            self.outlier_candidate = measurement
            self.outlier_candidate_time = now
            self.outlier_candidate_count = 1
            return False

        candidate_difference = (
            (measurement - self.outlier_candidate + 180.0) % 360.0 - 180.0
        )

        is_recent = (
            now - self.outlier_candidate_time
            <= OUTLIER_CONFIRMATION_WINDOW_SECONDS
        )

        is_similar = abs(candidate_difference) <= OUTLIER_MATCH_DEGREES

        if is_recent and is_similar:
            self.outlier_candidate_count += 1
        else:
            self.outlier_candidate = measurement
            self.outlier_candidate_count = 1

        self.outlier_candidate_time = now

        confirmed = (
            self.outlier_candidate_count >= OUTLIER_CONFIRMATION_COUNT
        )

        if confirmed:
            self._clear_outlier_candidate()

        return confirmed

    def _clear_outlier_candidate(self):
        self.outlier_candidate = None
        self.outlier_candidate_time = 0.0
        self.outlier_candidate_count = 0

    def _update_velocity_from_history(self, now):
        # Usa la pendiente de los últimos valores válidos.

        while (
            self.history
            and now - self.history[0][0] > VELOCITY_HISTORY_SECONDS
        ):
            self.history.popleft()

        if len(self.history) < 2:
            return

        times = np.array([sample[0] for sample in self.history])
        angles = np.array([sample[1] for sample in self.history])

        relative_times = times - times[0]
        recent_velocity = np.polyfit(relative_times, angles, 1)[0]

        # Combina la estimación Kalman con la velocidad reciente.
        self.filter.x[1, 0] = (
            0.5 * self.filter.x[1, 0]
            + 0.5 * recent_velocity
        )


def open_serial_port():
    try:
        connection = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0)
        connection.reset_input_buffer()

        print(
            f"Leyendo telemetría desde {SERIAL_PORT} "
            f"a {BAUD_RATE} baud."
        )

        return connection

    except serial.SerialException as error:
        raise SystemExit(
            f"No se pudo abrir {SERIAL_PORT}: {error}\n"
            "Cierra el Monitor Serie y revisa SERIAL_PORT."
        )


def read_telemetry(connection, buffer):
    # Paquete esperado:
    # bytes 0-3: CSWS
    # bytes 8-47: 10 floats
    # byte 48: estado de paracaídas
    # bytes 96-99: DTLB

    available = connection.in_waiting

    if available:
        buffer.extend(connection.read(available))

    latest_packet = None

    while len(buffer) >= PACKET_SIZE:
        header_index = buffer.find(b"CSWS")

        if header_index == -1:
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

        values = struct.unpack("<10f", packet[8:48])

        latest_packet = {
            "acceleration": values[0:3],
            "roll": values[3],
            "pitch": values[4],
            "yaw": values[5],
            "temperature": values[6],
            "pressure": values[7],
            "humidity": values[8],
            "speed": values[9],
            "parachute_status": packet[48],
        }

    return latest_packet


# ---------------------------------------------------------------------------
# INTERFAZ VPYTHON
# ---------------------------------------------------------------------------

cansat_canvas = canvas(
    align="left",
    background=vec(0.15, 0.15, 0.15),
    width=750
)

cansat_canvas.forward = vec(0, 1, 0)

cansat_body = cylinder(
    canvas=cansat_canvas,
    pos=vec(0, 0, 0),
    axis=vec(0, 0, 3),
    radius=0.8,
    color=vec(1, 0.84, 0),
    shininess=0.8,
    opacity=0.9
)

rotating_parts = [cansat_body]

angle_x = 0
angle_y = 0
angle_z = 0

warning_label = label(
    pos=vec(0, 2, 0),
    text="",
    color=color.red,
    height=18,
    box=True,
    background=color.white * 0.1,
    opacity=0.6
)


def update_rotation():
    Rz = np.array([
        [np.cos(angle_z), -np.sin(angle_z), 0],
        [np.sin(angle_z), np.cos(angle_z), 0],
        [0, 0, 1]
    ])

    Ry = np.array([
        [np.cos(angle_y), 0, np.sin(angle_y)],
        [0, 1, 0],
        [-np.sin(angle_y), 0, np.cos(angle_y)]
    ])

    Rx = np.array([
        [1, 0, 0],
        [0, np.cos(angle_x), -np.sin(angle_x)],
        [0, np.sin(angle_x), np.cos(angle_x)]
    ])

    new_axis = np.dot(
        Rz,
        np.dot(Ry, np.dot(Rx, [0, 0, 3]))
    )

    for part in rotating_parts:
        part.axis = vec(
            new_axis[0],
            new_axis[1],
            new_axis[2]
        )


def smooth_angle(current, target, dt):
    # Suaviza solo el dibujo del modelo 3D.
    delta = (target - current + np.pi) % (2.0 * np.pi) - np.pi
    alpha = 1.0 - np.exp(-VISUAL_SMOOTHING_HZ * dt)

    return current + alpha * delta


atmospheric_pressure_graph = graph(
    title="<b>Atmospheric Pressure</b>",
    xtitle="<b>Time (s)</b>",
    ytitle="<b>Pressure (Pa)</b>",
    xmin=0,
    ymin=90000,
    fast=True,
    align="right",
    background=color.black,
    foreground=color.black,
    width=750
)

atmospheric_pressure_curve = gcurve(
    graph=atmospheric_pressure_graph,
    color=color.red,
    width=4
)

temperature_graph = graph(
    title="<b>Temperature</b>",
    xtitle="<b>Time (s)</b>",
    ytitle="<b>Temperature (°C)</b>",
    xmin=0,
    ymin=-10,
    fast=True,
    align="left",
    background=color.black,
    foreground=color.black,
    width=750
)

temperature_curve = gcurve(
    graph=temperature_graph,
    color=color.cyan,
    width=4
)

relative_humidity_graph = graph(
    title="<b>Relative Humidity</b>",
    xtitle="<b>Time (s)</b>",
    ytitle="<b>Humidity (%)</b>",
    xmin=0,
    ymin=0,
    ymax=100,
    fast=True,
    align="right",
    background=color.black,
    foreground=color.black,
    width=750
)

relative_humidity_curve = gcurve(
    graph=relative_humidity_graph,
    color=color.green,
    width=4
)


def reset_graph_curves():
    # Evita acumulación infinita de puntos.

    global atmospheric_pressure_curve
    global temperature_curve
    global relative_humidity_curve

    atmospheric_pressure_curve.delete()
    temperature_curve.delete()
    relative_humidity_curve.delete()

    atmospheric_pressure_curve = gcurve(
        graph=atmospheric_pressure_graph,
        color=color.red,
        width=4
    )

    temperature_curve = gcurve(
        graph=temperature_graph,
        color=color.cyan,
        width=4
    )

    relative_humidity_curve = gcurve(
        graph=relative_humidity_graph,
        color=color.green,
        width=4
    )


# ---------------------------------------------------------------------------
# TELEMETRÍA Y KALMAN
# ---------------------------------------------------------------------------

i = 0

serial_connection = open_serial_port()
serial_buffer = bytearray()

last_packet_time = 0.0
last_filter_time = time.monotonic()

roll_filter = AngleKalmanFilter()
pitch_filter = AngleKalmanFilter()
yaw_filter = AngleKalmanFilter()

display_angle_x = 0.0
display_angle_y = 0.0
display_angle_z = 0.0
display_initialized = False


while True:
    now = time.monotonic()

    # Evita saltos de tiempo si Windows pausa el programa.
    dt = min(now - last_filter_time, 0.25)
    last_filter_time = now

    # Un paquete rechazado no cuenta como medición válida.
    signal_age = (
        now - last_packet_time
        if last_packet_time
        else float("inf")
    )

    telemetry = read_telemetry(
        serial_connection,
        serial_buffer
    )

    # Kalman predice siempre.
    roll_filter.predict(dt, signal_age)
    pitch_filter.predict(dt, signal_age)
    yaw_filter.predict(dt, signal_age)

    accepted_axes = []

    if telemetry is not None:
        accepted_axes = [
            roll_filter.update_if_plausible(
                telemetry["roll"],
                now
            ),
            pitch_filter.update_if_plausible(
                telemetry["pitch"],
                now
            ),
            yaw_filter.update_if_plausible(
                telemetry["yaw"],
                now
            ),
        ]

        if i >= GRAPH_HISTORY_POINTS:
            reset_graph_curves()
            i = 0

        atmospheric_pressure_curve.plot(
            i,
            telemetry["pressure"]
        )

        temperature_curve.plot(
            i,
            telemetry["temperature"]
        )

        relative_humidity_curve.plot(
            i,
            telemetry["humidity"]
        )

        i += 1

        if all(accepted_axes):
            last_packet_time = now

    signal_age = (
        now - last_packet_time
        if last_packet_time
        else float("inf")
    )

    # El modelo 3D usa el ángulo filtrado.
    if roll_filter.initialized:
        target_angle_x = np.radians(roll_filter.angle)
        target_angle_y = np.radians(pitch_filter.angle)
        target_angle_z = np.radians(yaw_filter.angle)
    else:
        target_angle_x = None

    if target_angle_x is not None:
        if not display_initialized:
            display_angle_x = target_angle_x
            display_angle_y = target_angle_y
            display_angle_z = target_angle_z
            display_initialized = True
        else:
            display_angle_x = smooth_angle(
                display_angle_x,
                target_angle_x,
                dt
            )

            display_angle_y = smooth_angle(
                display_angle_y,
                target_angle_y,
                dt
            )

            display_angle_z = smooth_angle(
                display_angle_z,
                target_angle_z,
                dt
            )

        angle_x = display_angle_x
        angle_y = display_angle_y
        angle_z = display_angle_z

        update_rotation()

    if not roll_filter.initialized:
        warning_label.text = "Waiting for telemetry"
        warning_label.color = color.red

    elif signal_age > STALE_AFTER_SECONDS:
        warning_label.text = "Telemetry lost - Kalman estimate only"
        warning_label.color = color.red

    elif telemetry is not None and not all(accepted_axes):
        warning_label.text = "Outlier rejected - using Kalman estimate"
        warning_label.color = color.orange

    elif signal_age > MAX_PREDICTION_SECONDS:
        warning_label.text = "Kalman prediction - no valid measurement"
        warning_label.color = color.orange

    else:
        warning_label.text = ""

    rate(DISPLAY_RATE_HZ)