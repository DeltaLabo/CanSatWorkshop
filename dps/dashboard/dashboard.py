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

SERIAL_PORT = "COM5"
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

# Short bridge used only while byte 49 reports that the MPU sample is stale.
INVALID_SAMPLE_FULL_GYRO_SECONDS = 0.25
INVALID_SAMPLE_GYRO_DECAY_SECONDS = 0.50
INVALID_BRIDGE_RATE_STD_DPS = 60.0
INVALID_BRIDGE_MAX_VARIANCE_DEG2 = 400.0

# After a sensor outage, a trustworthy gravity measurement must rapidly
# re-anchor roll/pitch instead of being mistaken for a large outlier.
REACQUISITION_MIN_GAIN = 0.90

DISPLAY_RATE_HZ = 60
# This affects only the drawing, never the Kalman state. At 10 Hz a large
# re-acquisition correction becomes a smooth transition of roughly 0.3 s.
VISUAL_SMOOTHING_HZ = 10.0
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

    def update(
        self,
        gyro_rate_dps,
        accel_angle_deg,
        dt,
        accel_reliable,
        reacquire=False,
    ):
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
        if reacquire:
            # Force a high, but still Kalman-weighted, correction after an
            # outage. P is chosen so the gain is at least 90 percent.
            minimum_reacquisition_variance = (
                measurement_variance
                * REACQUISITION_MIN_GAIN
                / (1.0 - REACQUISITION_MIN_GAIN)
            )
            predicted_variance = max(
                predicted_variance,
                minimum_reacquisition_variance,
            )
        elif abs(innovation) > ACCEL_SOFT_INNOVATION_DEG:
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
        """Advance with stale gyro data without accepting a measurement."""
        self.last_correction_used = False
        self.last_correction_softened = False
        self.last_gain = 0.0

        if not self.initialized:
            return

        self.angle += gyro_rate_dps * dt
        self.variance = min(
            self.variance + (dt * INVALID_BRIDGE_RATE_STD_DPS) ** 2,
            INVALID_BRIDGE_MAX_VARIANCE_DEG2,
        )


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
      48     parachute status
      49     IMU validity: 0 = fresh sample, 255 = stale values after I2C
             failure (the serial heartbeat is still healthy)
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
            "imu_valid": packet[49] == 0x00,
        }

    return newest, saw_legacy_m1


# ---------------------------------------------------------------------------
# VPYTHON VIEW
# ---------------------------------------------------------------------------
# ---------------------------------------------------------------------------
# INTERFAZ VPYTHON
# ---------------------------------------------------------------------------

from collections import deque
from pathlib import Path
import base64


def smooth_visual_angle(current, target, dt):
    """Move a displayed angle smoothly along the shortest circular path."""
    difference = (target - current + np.pi) % (2.0 * np.pi) - np.pi
    blend = 1.0 - np.exp(-VISUAL_SMOOTHING_HZ * dt)
    return current + blend * difference


# El logo es opcional. Si existe junto a dashboard.py se incrusta como base64,
# evitando que el navegador dependa de una ruta local de Windows.
logo_path = Path(__file__).resolve().parent / "logo_delta.png"
logo_html = ""
if logo_path.is_file():
    logo_data = base64.b64encode(logo_path.read_bytes()).decode("ascii")
    logo_html = (
        f'<img src="data:image/png;base64,{logo_data}" '
        'alt="Laboratorio Delta">'
    )


dashboard_title = """
<style>
    @import url('https://fonts.googleapis.com/css2?family=Montserrat:wght@400;600;700&display=swap');

    :root {
        --panel-scale: min(
            tan(atan2(max(320px, calc(100vw - 32px)), 1216px)),
            tan(atan2(max(420px, calc(100dvh - 140px)), 532px))
        );
        --panel-left: max(
            16px,
            calc((100vw - 1216px * var(--panel-scale)) / 2)
        );
        --panel-top: 124px;
    }

    html, body {
        margin: 0;
        padding: 0;
        min-width: 0;
        min-height: 100dvh;
    }

    body {
        background: white;
        color: #415563;
        font-family: 'Montserrat', sans-serif;
        overflow-x: hidden;
    }

    .header-bar {
        position: absolute;
        top: 0;
        left: 0;
        right: 0;
        box-sizing: border-box;
        display: flex;
        align-items: center;
        height: 104px;
        margin: 0;
        padding: 15px clamp(16px, 2vw, 38px);
        background: #034365;
    }

    .header-bar img {
        height: clamp(44px, 5vw, 64px);
        margin-right: 20px;
    }

    .header-text {
        display: flex;
        flex-direction: column;
    }

    .header-sub {
        color: #66b3ff;
        font-size: 11px;
        font-weight: 700;
        letter-spacing: 2px;
        text-transform: uppercase;
    }

    .header-title {
        margin: 0;
        color: white;
        font-size: clamp(24px, 3.2vw, 48px);
        font-weight: 700;
        line-height: 1.1;
    }

    canvas {
        border-radius: 0;
        box-shadow: none;
    }

    div {
        font-family: 'Montserrat', sans-serif;
    }

    .glowscript-canvas-wrapper,
    .model-heading {
        transform: scale(var(--panel-scale));
        transform-origin: top left;
    }

    .glowscript-canvas-wrapper {
        position: absolute !important;
        left: var(--panel-left);
        top: calc(var(--panel-top) + 44px * var(--panel-scale));
        overflow: hidden;
        border: 1px solid #4a929e;
        border-radius: 8px;
    }

    .model-heading,
    .glowscript-graph::before {
        height: 32px;
        border-radius: 6px;
        background: #034365;
        color: white;
        font-size: 14px;
        font-weight: 700;
        line-height: 32px;
        text-align: center;
    }

    .model-heading {
        position: absolute;
        left: var(--panel-left);
        top: var(--panel-top);
        width: 362px;
    }

    .glowscript-graph {
        position: absolute !important;
        float: none !important;
        overflow: visible;
        width: calc(350px * var(--panel-scale)) !important;
        height: calc(198px * var(--panel-scale)) !important;
        border: 0;
        border-radius: 0;
        background: white;
        box-shadow: none;
    }

    .glowscript-graph::before {
        position: absolute;
        left: calc(-12px * var(--panel-scale));
        top: calc(-56px * var(--panel-scale));
        width: calc(398px * var(--panel-scale));
        height: calc(32px * var(--panel-scale));
        line-height: calc(32px * var(--panel-scale));
    }

    #graph0, #graph2 {
        left: calc(var(--panel-left) + 400px * var(--panel-scale));
    }

    #graph1, #graph3 {
        left: calc(var(--panel-left) + 826px * var(--panel-scale));
    }

    #graph0, #graph1 {
        top: calc(var(--panel-top) + 56px * var(--panel-scale));
    }

    #graph2, #graph3 {
        top: calc(var(--panel-top) + 334px * var(--panel-scale));
    }

    #graph0::before { content: "Temperatura"; }
    #graph1::before { content: "Presión atmosférica"; }
    #graph2::before { content: "Humedad relativa"; }
    #graph3::before { content: "Altitud estimada"; }

    .current-reading {
        position: absolute;
        width: calc(398px * var(--panel-scale));
        height: calc(20px * var(--panel-scale));
        color: #415563;
        font-size: clamp(11px, calc(12px * var(--panel-scale)), 18px);
        line-height: calc(20px * var(--panel-scale));
        text-align: center;
        white-space: nowrap;
        pointer-events: none;
    }

    .current-temperature {
        left: calc(var(--panel-left) + 388px * var(--panel-scale));
        top: calc(var(--panel-top) + 34px * var(--panel-scale));
    }

    .current-pressure {
        left: calc(var(--panel-left) + 814px * var(--panel-scale));
        top: calc(var(--panel-top) + 34px * var(--panel-scale));
    }

    .current-humidity {
        left: calc(var(--panel-left) + 388px * var(--panel-scale));
        top: calc(var(--panel-top) + 312px * var(--panel-scale));
    }

    .current-altitude {
        left: calc(var(--panel-left) + 814px * var(--panel-scale));
        top: calc(var(--panel-top) + 312px * var(--panel-scale));
    }
</style>

<script>
(function () {
    if (window.cansatGraphResize) return;
    window.cansatGraphResize = true;

    const observed = new WeakSet();
    const dimensions = new WeakMap();

    // VPython crea Plotly sin configuración. Interceptamos la creación para
    // quitar solo las acciones externas; zoom, pan, reset y PNG permanecen.
    const securePlotly = () => {
        if (!window.Plotly || window.cansatPlotlySecured) return;
        window.cansatPlotlySecured = true;

        const originalNewPlot = Plotly.newPlot;
        Plotly.newPlot = function (graph, data, layout, config) {
            const safeConfig = Object.assign({}, config || {});
            const removed = new Set(
                safeConfig.modeBarButtonsToRemove || []
            );
            removed.add('sendDataToCloud');
            removed.add('editInChartStudio');
            safeConfig.modeBarButtonsToRemove = Array.from(removed);
            safeConfig.displaylogo = false;
            safeConfig.showLink = false;
            safeConfig.showSendToCloud = false;
            return originalNewPlot.call(
                this,
                graph,
                data,
                layout,
                safeConfig
            );
        };

        // VPython mantiene un bloqueo interno mientras extendTraces() esta
        // pendiente. Si Plotly cancela esa promesa durante zoom, pan o una
        // exportacion, la version original de VPython nunca libera el bloqueo
        // y la curva parece congelada para siempre. Convertimos ese rechazo en
        // una finalizacion normal; el siguiente refresco repone todos los datos.
        const originalExtendTraces = Plotly.extendTraces;
        Plotly.extendTraces = function (...args) {
            try {
                const result = originalExtendTraces.apply(this, args);
                if (result && typeof result.catch === 'function') {
                    return result.catch(() => args[0]);
                }
                return result;
            } catch (error) {
                return Promise.resolve(args[0]);
            }
        };
    };

    // También limpia gráficas creadas antes de instalar la configuración.
    const removeExternalPlotOptions = () => {
        document.querySelectorAll('.modebar-btn').forEach(button => {
            const description = (
                button.getAttribute('data-title')
                || button.getAttribute('title')
                || button.getAttribute('aria-label')
                || ''
            ).toLowerCase();
            if (
                description.includes('chart studio')
                || description.includes('send data to cloud')
                || description.includes('produced with plotly')
            ) {
                button.remove();
            }
        });
    };

    const resize = element => {
        if (window.Plotly && element._fullLayout) {
            const width = Math.round(element.clientWidth);
            const height = Math.round(element.clientHeight);
            const previous = dimensions.get(element);
            if (width <= 0 || height <= 0) return;
            if (
                previous
                && previous.width === width
                && previous.height === height
            ) return;

            dimensions.set(element, {width: width, height: height});
            const operation = Plotly.relayout(element, {
                width: width,
                height: height,
                'margin.l': 55,
                'margin.r': 24,
                'margin.t': 34,
                'margin.b': 45,
                hovermode: 'closest'
            });
            if (operation && typeof operation.catch === 'function') {
                operation.catch(() => dimensions.delete(element));
            }
        }
    };

    const observer = new ResizeObserver(entries => {
        entries.forEach(entry => resize(entry.target));
    });

    setInterval(() => {
        securePlotly();
        removeExternalPlotOptions();
        document.querySelectorAll('.glowscript-graph').forEach(element => {
            if (!observed.has(element)) {
                observed.add(element);
                observer.observe(element);
            }
            // Permite inicializar una grafica creada despues del observador.
            // El WeakMap evita relayout si el tamano real no ha cambiado.
            resize(element);
        });
    }, 250);
})();
</script>

<div class="header-bar">
    __LOGO__
    <div class="header-text">
        <span class="header-sub">Laboratorio Delta</span>
        <span class="header-title">CanSat Workshop</span>
    </div>
</div>
"""

dashboard_title = dashboard_title.replace("__LOGO__", logo_html)
dashboard_title += '<div class="model-heading">Modelo 3D CanSat</div>'

cansat_canvas = canvas(
    title=dashboard_title,
    align="left",
    background=vec(0.12, 0.16, 0.22),
    width=360,
    height=488,
    userzoom=False,
    userspin=False,
)

# Ejes del modelo vertical en caída libre.
cansat_canvas.up = vec(0, 0, 1)
cansat_canvas.forward = vec(0, 1, 0)
cansat_canvas.center = vec(0, 0, 1.5)
cansat_canvas.range = 3.5
cansat_canvas.autoscale = False

# Modelo 3D asimétrico para hacer visibles roll, pitch y yaw.
dark_color = vec(0.12, 0.12, 0.14)
cansat_core = box(
    canvas=cansat_canvas,
    pos=vec(0, 0, 1.5),
    size=vec(0.65, 0.65, 1.4),
    color=vec(0.6, 0.35, 0.1),
)
cansat_top = cylinder(
    canvas=cansat_canvas,
    pos=vec(0, 0, 2.85),
    axis=vec(0, 0, 0.15),
    radius=0.8,
    color=dark_color,
)
cansat_bottom = cylinder(
    canvas=cansat_canvas,
    pos=vec(0, 0, 0),
    axis=vec(0, 0, 0.15),
    radius=0.8,
    color=dark_color,
)
side_p1 = box(
    canvas=cansat_canvas,
    pos=vec(0.72, 0, 1.5),
    size=vec(0.15, 0.4, 2.7),
    color=dark_color,
)
side_p2 = box(
    canvas=cansat_canvas,
    pos=vec(-0.72, 0, 1.5),
    size=vec(0.15, 0.4, 2.7),
    color=dark_color,
)
side_p3 = box(
    canvas=cansat_canvas,
    pos=vec(0, 0.72, 1.5),
    size=vec(0.4, 0.15, 2.7),
    color=dark_color,
)
side_p4 = box(
    canvas=cansat_canvas,
    pos=vec(0, -0.72, 1.5),
    size=vec(0.4, 0.15, 2.7),
    color=dark_color,
)
band1 = cylinder(
    canvas=cansat_canvas,
    pos=vec(0, 0, 2.2),
    axis=vec(0, 0, 0.15),
    radius=0.82,
    color=vec(0.0, 0.4, 0.7),
)
band2 = cylinder(
    canvas=cansat_canvas,
    pos=vec(0, 0, 0.65),
    axis=vec(0, 0, 0.15),
    radius=0.82,
    color=vec(0.0, 0.4, 0.7),
)

rotating_parts = [
    cansat_core,
    cansat_top,
    cansat_bottom,
    side_p1,
    side_p2,
    side_p3,
    side_p4,
    band1,
    band2,
]

orientation_label = label(
    canvas=cansat_canvas,
    pixel_pos=True,
    pos=vec(105, 425, 0),
    text="Roll X: 0.00°\nPitch Y: 0.00°\nYaw Z: 0.00°",
    color=color.white,
    height=18,
    box=False,
    line=False,
    font="sans",
)
sensor_status_label = label(
    canvas=cansat_canvas,
    pixel_pos=True,
    pos=vec(180, 70, 0),
    text="Esperando conexión...",
    color=color.gray(0.6),
    height=13,
    box=False,
    line=False,
    font="sans",
)
warning_label = label(
    canvas=cansat_canvas,
    pixel_pos=True,
    pos=vec(180, 25, 0),
    text="Waiting for M2 IMU telemetry",
    color=color.red,
    height=11,
    box=False,
    line=False,
    font="sans",
)

angle_x = 0.0
angle_y = 0.0
angle_z = 0.0
model_origin = np.array([0.0, 0.0, 1.5])


def vector_array(vector):
    return np.array([vector.x, vector.y, vector.z])


original_geometry = [
    (
        part,
        vector_array(part.pos) - model_origin,
        vector_array(part.axis),
        vector_array(part.up),
    )
    for part in rotating_parts
]


def update_rotation():
    """Rotate every CanSat component around the common model origin."""
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

    orientation = rotation_z @ rotation_y @ rotation_x
    for part, position, axis, up in original_geometry:
        rotated_position = model_origin + orientation @ position
        part.pos = vec(*rotated_position)
        part.axis = vec(*(orientation @ axis))
        part.up = vec(*(orientation @ up))


GRAPH_WIDTH = 350
GRAPH_HEIGHT = 198
BG_COLOR = color.white
FG_COLOR = vec(0.45, 0.51, 0.55)
LINE_COLOR = vec(0.0, 0.45, 0.75)
LINE_COLOR_ALT = vec(0.2, 0.6, 0.7)

temperature_graph = graph(
    title="",
    xtitle="Tiempo (s)",
    ytitle="°C",
    fast=False,
    align="left",
    background=BG_COLOR,
    foreground=FG_COLOR,
    width=GRAPH_WIDTH,
    height=GRAPH_HEIGHT,
)
temperature_curve = gcurve(
    graph=temperature_graph,
    color=LINE_COLOR,
    width=2,
)

atmospheric_pressure_graph = graph(
    title="",
    xtitle="Tiempo (s)",
    ytitle="kPa",
    fast=False,
    align="left",
    background=BG_COLOR,
    foreground=FG_COLOR,
    width=GRAPH_WIDTH,
    height=GRAPH_HEIGHT,
)
atmospheric_pressure_curve = gcurve(
    graph=atmospheric_pressure_graph,
    color=LINE_COLOR_ALT,
    width=2,
)

relative_humidity_graph = graph(
    title="",
    xtitle="Tiempo (s)",
    ytitle="%",
    fast=False,
    align="left",
    background=BG_COLOR,
    foreground=FG_COLOR,
    width=GRAPH_WIDTH,
    height=GRAPH_HEIGHT,
)
relative_humidity_curve = gcurve(
    graph=relative_humidity_graph,
    color=LINE_COLOR,
    width=2,
)

altitude_graph = graph(
    title="",
    xtitle="Tiempo (s)",
    ytitle="m",
    fast=False,
    align="left",
    background=BG_COLOR,
    foreground=FG_COLOR,
    width=GRAPH_WIDTH,
    height=GRAPH_HEIGHT,
)
altitude_curve = gcurve(
    graph=altitude_graph,
    color=LINE_COLOR_ALT,
    width=2,
)

GRAPH_WINDOW_SECONDS = 60.0
# Reconstruir cuatro series completas cinco veces por segundo competía con las
# operaciones interactivas. Dos refrescos por segundo son suficientes para el
# BME y reducen bastante la carga gráfica en una Raspberry Pi.
GRAPH_REFRESH_SECONDS = 0.5
GRAPH_SMOOTHING_SECONDS = 0.5
SEA_LEVEL_PRESSURE_PA = 101325.0
plot_start_time = None
last_graph_refresh = -float("inf")
last_environment_time = 0.0
last_graph_error_time = -float("inf")

graph_channels = [
    {
        "key": "temperature",
        "unit": "°C",
        "factor": 1.0,
        "graph": temperature_graph,
        "curve": temperature_curve,
        "span": 10.0,
    },
    {
        "key": "pressure",
        "unit": "kPa",
        "factor": 0.001,
        "graph": atmospheric_pressure_graph,
        "curve": atmospheric_pressure_curve,
        "span": 5.0,
    },
    {
        "key": "humidity",
        "unit": "%",
        "factor": 1.0,
        "graph": relative_humidity_graph,
        "curve": relative_humidity_curve,
        "span": 10.0,
    },
    {
        "key": "altitude",
        "unit": "m",
        "factor": 1.0,
        "graph": altitude_graph,
        "curve": altitude_curve,
        "span": 10.0,
    },
]

for channel in graph_channels:
    channel.update(
        history=deque(maxlen=10000),
        smoothed=None,
        last_time=None,
        limits=None,
    )
    channel["curve"].label = "Tendencia suavizada"
    channel["graph"].title = ""
    channel["readout"] = wtext(
        pos=cansat_canvas.caption_anchor,
        text=(
            f'<span class="current-reading current-{channel["key"]}">'
            "Esperando datos</span>"
        ),
    )
    channel["curve"].plot(0, float("nan"))


def altitude_from_pressure(pressure_pa):
    """Estimate barometric altitude from pressure using standard sea level."""
    if not np.isfinite(pressure_pa) or pressure_pa <= 0.0:
        return float("nan")
    return 44330.0 * (
        1.0 - (pressure_pa / SEA_LEVEL_PRESSURE_PA) ** (1.0 / 5.255)
    )


def update_environment_graphs(telemetry, now):
    global plot_start_time
    global last_graph_refresh
    global last_environment_time
    global last_graph_error_time

    temperature = telemetry["temperature"]
    pressure = telemetry["pressure"]
    humidity = telemetry["humidity"]
    environment = {
        "temperature": temperature,
        "pressure": pressure,
        "humidity": humidity,
        "altitude": altitude_from_pressure(pressure),
    }

    if (
        np.isfinite(temperature)
        and np.isfinite(pressure)
        and np.isfinite(humidity)
        and pressure > 0.0
        and 0.0 <= humidity <= 100.0
    ):
        last_environment_time = now

    if plot_start_time is None:
        plot_start_time = now
    elapsed = now - plot_start_time

    for channel in graph_channels:
        value = environment[channel["key"]] * channel["factor"]
        if not np.isfinite(value):
            continue

        previous = channel["last_time"]
        gap = (
            previous is not None
            and now - previous > STALE_AFTER_SECONDS
        )
        if previous is None or gap:
            if gap:
                channel["history"].append((elapsed, float("nan")))
            channel["smoothed"] = value
        else:
            alpha = 1.0 - np.exp(
                -(now - previous) / GRAPH_SMOOTHING_SECONDS
            )
            channel["smoothed"] += alpha * (
                value - channel["smoothed"]
            )

        channel["last_time"] = now
        channel["latest"] = value
        channel["history"].append((elapsed, channel["smoothed"]))

        oldest_allowed = elapsed - GRAPH_WINDOW_SECONDS
        while (
            channel["history"]
            and channel["history"][0][0] < oldest_allowed
        ):
            channel["history"].popleft()

    if now - last_graph_refresh < GRAPH_REFRESH_SECONDS:
        return

    last_graph_refresh = now
    for channel in graph_channels:
        if "latest" not in channel:
            continue

        try:
            channel["readout"].text = (
                f'<span class="current-reading current-{channel["key"]}">'
                f'Actual: {channel["latest"]:.2f} '
                f'{channel["unit"]}</span>'
            )
            # El historial ya contiene exclusivamente los ultimos 60 s.
            # Solo sustituimos los datos y dejamos los ejes bajo control de
            # Plotly. Asi zoom, pan y PNG no compiten con relayout de Python.
            channel["curve"].data = list(channel["history"])
        except Exception as error:
            # Zoom y exportación pueden mantener ocupado el objeto Plotly.
            # Se omite solo este refresco; el bucle principal y la telemetría
            # continúan y el siguiente refresco reconstruye la serie completa.
            if now - last_graph_error_time >= 2.0:
                print(f"Plot refresh skipped during interaction: {error}")
                last_graph_error_time = now


# ---------------------------------------------------------------------------
# LIVE TELEMETRY LOOP
# ---------------------------------------------------------------------------

serial_connection = None
serial_buffer = bytearray()
next_serial_attempt = 0.0
last_packet_time = 0.0
last_imu_time = None
last_valid_imu_time = None
legacy_m1_seen = False
last_packet_sensor_valid = False
last_good_gyro = (0.0, 0.0, 0.0)
reacquisition_pending = False

roll_filter = PaperKalmanAngle()
pitch_filter = PaperKalmanAngle()
yaw_angle = 0.0

target_angle_x = 0.0
target_angle_y = 0.0
target_angle_z = 0.0
visual_initialized = False
last_visual_time = time.monotonic()


while True:
    now = time.monotonic()

    if serial_connection is None and now >= next_serial_attempt:
        serial_connection = open_serial_port()
        next_serial_attempt = now + SERIAL_RETRY_SECONDS
        serial_buffer.clear()

    telemetry = None
    if serial_connection is not None:
        try:
            telemetry, saw_legacy = read_telemetry(
                serial_connection,
                serial_buffer,
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
        packet_gap = (
            now - last_packet_time
            if last_packet_time
            else None
        )
        if (
            packet_gap is not None
            and packet_gap > STALE_AFTER_SECONDS
        ):
            reacquisition_pending = True

        last_packet_time = now
        last_packet_sensor_valid = telemetry["imu_valid"]
        legacy_m1_seen = False

        if last_imu_time is None or (
            packet_gap is not None
            and packet_gap > STALE_AFTER_SECONDS
        ):
            dt = 0.0
        else:
            dt = min(now - last_imu_time, 0.25)
        last_imu_time = now

        if telemetry["imu_valid"]:
            last_valid_imu_time = now
            acc_x, acc_y, acc_z = telemetry["acceleration"]
            gyro_x, gyro_y, gyro_z = telemetry["gyro"]
            last_good_gyro = (gyro_x, gyro_y, gyro_z)
            accel_roll, accel_pitch = accelerometer_angles(
                acc_x,
                acc_y,
                acc_z,
            )
            accel_reliable = gravity_is_reliable(
                acc_x,
                acc_y,
                acc_z,
            )

            reacquire_now = (
                reacquisition_pending
                and accel_reliable
            )
            roll_filter.update(
                gyro_x,
                accel_roll,
                dt,
                accel_reliable,
                reacquire=reacquire_now,
            )
            pitch_filter.update(
                gyro_y,
                accel_pitch,
                dt,
                accel_reliable,
                reacquire=reacquire_now,
            )
            yaw_angle = wrap_degrees(
                yaw_angle + gyro_z * dt
            )

            if reacquire_now:
                reacquisition_pending = False

        elif last_valid_imu_time is not None:
            reacquisition_pending = True
            invalid_age = now - last_valid_imu_time
            excess_age = max(
                0.0,
                invalid_age - INVALID_SAMPLE_FULL_GYRO_SECONDS,
            )
            gyro_weight = np.exp(
                -excess_age / INVALID_SAMPLE_GYRO_DECAY_SECONDS
            )
            gyro_x, gyro_y, gyro_z = last_good_gyro
            roll_filter.predict_only(
                gyro_x * gyro_weight,
                dt,
            )
            pitch_filter.predict_only(
                gyro_y * gyro_weight,
                dt,
            )
            yaw_angle = wrap_degrees(
                yaw_angle + gyro_z * gyro_weight * dt
            )

        if roll_filter.initialized and pitch_filter.initialized:
            target_angle_x = np.radians(roll_filter.angle)
            target_angle_y = np.radians(pitch_filter.angle)
            target_angle_z = np.radians(yaw_angle)

        update_environment_graphs(telemetry, now)

    visual_dt = min(now - last_visual_time, 0.1)
    last_visual_time = now
    if roll_filter.initialized and pitch_filter.initialized:
        if not visual_initialized:
            angle_x = target_angle_x
            angle_y = target_angle_y
            angle_z = target_angle_z
            visual_initialized = True
        else:
            angle_x = smooth_visual_angle(
                angle_x,
                target_angle_x,
                visual_dt,
            )
            angle_y = smooth_visual_angle(
                angle_y,
                target_angle_y,
                visual_dt,
            )
            angle_z = smooth_visual_angle(
                angle_z,
                target_angle_z,
                visual_dt,
            )

        update_rotation()
        orientation_label.text = (
            f"Roll X: {wrap_degrees(np.degrees(angle_x)):.2f}°\n"
            f"Pitch Y: {wrap_degrees(np.degrees(angle_y)):.2f}°\n"
            f"Yaw Z: {wrap_degrees(np.degrees(angle_z)):.2f}°"
        )

    signal_age = (
        now - last_packet_time
        if last_packet_time
        else float("inf")
    )

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
        warning_label.text = "IMU invalid: Kalman prediction active"
        warning_label.color = color.orange
    elif not (roll_filter.initialized and pitch_filter.initialized):
        warning_label.text = "Waiting for a stable gravity sample"
        warning_label.color = color.orange
    elif not roll_filter.last_correction_used:
        warning_label.text = (
            "Accel correction paused: free fall / acceleration"
        )
        warning_label.color = color.orange
    elif (
        roll_filter.last_correction_softened
        or pitch_filter.last_correction_softened
    ):
        warning_label.text = (
            "Large accel reading: Kalman correction softened"
        )
        warning_label.color = color.orange
    else:
        warning_label.text = ""

    if last_packet_time == 0.0:
        imu_status = "esperando M2"
    elif signal_age > STALE_AFTER_SECONDS:
        imu_status = "sin conexión"
    elif not last_packet_sensor_valid:
        imu_status = "lectura inválida"
    else:
        imu_status = "conectado"

    if last_environment_time == 0.0:
        bme_status = "esperando datos"
    elif now - last_environment_time > STALE_AFTER_SECONDS:
        bme_status = "sin datos válidos"
    else:
        bme_status = "conectado"

    sensor_status_label.text = (
        f"MPU6050: {imu_status}\n"
        f"BME280: {bme_status}"
    )

    rate(DISPLAY_RATE_HZ)
