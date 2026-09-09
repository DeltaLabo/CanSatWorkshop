from vpython import *
import struct
import time
import numpy as np  # Necesario para manejar los ángulos
import serial

# Puerto USB que aparece en Administrador de dispositivos -> Puertos (COM y LPT).
# Cambia COM9 si tu placa usa otro puerto.
SERIAL_PORT = "COM9"
BAUD_RATE = 115200
PACKET_SIZE = 100
# El Arduino transmite cada 200 ms. Permitimos algunas pérdidas antes de avisar.
STALE_AFTER_SECONDS = 1.5
# Después de este intervalo sin mediciones, se congela la actitud estimada.
MAX_PREDICTION_SECONDS = 0.5


class AngleKalmanFilter:
    """Filtro de Kalman de dos estados: ángulo y velocidad angular."""

    def __init__(self, process_noise=0.2, measurement_noise=3.0):
        self.angle = 0.0
        self.angular_velocity = 0.0
        self.process_noise = process_noise
        self.measurement_noise = measurement_noise
        self.p00, self.p01, self.p10, self.p11 = 10.0, 0.0, 0.0, 10.0
        self.initialized = False

    def predict(self, dt, allow_motion=True):
        """Predice el ángulo actual usando la velocidad angular estimada."""
        # Sin una medición reciente la velocidad estimada debe apagarse rápido:
        # de otro modo un pequeño ruido se convierte en un giro continuo.
        damping = 2.5 if allow_motion else 12.0
        self.angular_velocity *= np.exp(-damping * dt)
        if allow_motion:
            self.angle += self.angular_velocity * dt

        # P = F P F^T + Q para el modelo de velocidad constante.
        p00 = self.p00 + dt * (self.p10 + self.p01) + dt * dt * self.p11
        p01 = self.p01 + dt * self.p11
        p10 = self.p10 + dt * self.p11
        p11 = self.p11
        # Ruido de proceso escalado por dt; evita que la incertidumbre crezca
        # artificialmente 60 veces por segundo.
        q = self.process_noise
        self.p00 = p00 + q * dt**4 / 4.0
        self.p01 = p01 + q * dt**3 / 2.0
        self.p10 = p10 + q * dt**3 / 2.0
        self.p11 = p11 + q * dt**2

    def update(self, measurement):
        """Corrige la predicción con el ángulo medido por el MPU-6500."""
        if not self.initialized:
            self.angle = measurement
            self.initialized = True
            return

        residual = measurement - self.angle
        # Evita un salto grande al cruzar -180 / 180 grados (especialmente yaw).
        residual = (residual + 180.0) % 360.0 - 180.0
        innovation = self.p00 + self.measurement_noise
        gain_angle = self.p00 / innovation
        gain_velocity = self.p10 / innovation

        self.angle += gain_angle * residual
        self.angular_velocity += gain_velocity * residual

        p00, p01 = self.p00, self.p01
        self.p00 -= gain_angle * p00
        self.p01 -= gain_angle * p01
        self.p10 -= gain_velocity * p00
        self.p11 -= gain_velocity * p01


def open_serial_port():
    """Abre el puerto del Arduino. El sketch usa 115200 baud."""
    try:
        connection = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0)
        # Al abrir el puerto muchas placas se reinician; descartamos bytes incompletos.
        connection.reset_input_buffer()
        print(f"Leyendo telemetría desde {SERIAL_PORT} a {BAUD_RATE} baud.")
        return connection
    except serial.SerialException as error:
        raise SystemExit(
            f"No se pudo abrir {SERIAL_PORT}: {error}\n"
            "Cierra el Monitor Serie y verifica SERIAL_PORT en dashboard.py."
        )


def read_telemetry(connection, buffer):
    """Devuelve el último paquete CSWS completo o None si aún no llegó uno."""
    available = connection.in_waiting
    if available:
        buffer.extend(connection.read(available))

    latest_packet = None
    while len(buffer) >= PACKET_SIZE:
        header_index = buffer.find(b"CSWS")
        if header_index == -1:
            # Conserva tres bytes: podrían ser el comienzo del siguiente encabezado.
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

        # El sketch escribe 10 float de 32 bits, little-endian, desde el byte 8.
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

# Layout container that the 3D model is placed inside of
cansat_canvas = canvas(align="left",background=vec(0.15, 0.15, 0.15), width = 750)

cansat_canvas.forward = vec(0, 1, 0)  # Mira el CanSat desde el eje Y negativo

#cansat_canvas.camera.pos = vec(0, -8, 2)  # Coloca la cámara más lejos
#cansat_canvas.camera.axis = vec(0, 8, -2)  # Ajusta la dirección en que mira

cansat_body = cylinder(
    canvas=cansat_canvas,
    pos=vec(0, 0, 0),
    axis=vec(0, 0, 3),
    radius=0.8,
    color=vec(1, 0.84, 0),  # Amarillo dorado
    shininess=0.8,          # Efecto metálico
    opacity=0.9             # Un poco de transparencia
)

# Partes que deben girar con el cuerpo
rotating_parts = [cansat_body]

# Ángulos iniciales de rotación (en radianes)
angle_x = 0
angle_y = 0
angle_z = 0

# Flag de datos desactualizados
out_of_date = False  # Cambia esto a True para ver la advertencia

warning_label = label(
    pos=vec(0, 2, 0),
    text="",
    color=color.red,
    height=18,
    box=True,
    background=color.white * 0.1,  # Fondo gris claro
    opacity=0.6
)

# Función para actualizar la orientación del cuerpo en función de los ángulos
def update_rotation():
    global angle_x, angle_y, angle_z

    # Matrices de rotación
    Rz = np.array([[np.cos(angle_z), -np.sin(angle_z), 0],
                   [np.sin(angle_z),  np.cos(angle_z), 0],
                   [0, 0, 1]])

    Ry = np.array([[np.cos(angle_y), 0, np.sin(angle_y)],
                   [0, 1, 0],
                   [-np.sin(angle_y), 0, np.cos(angle_y)]])

    Rx = np.array([[1, 0, 0],
                   [0, np.cos(angle_x), -np.sin(angle_x)],
                   [0, np.sin(angle_x),  np.cos(angle_x)]])

    # Transformar la orientación del eje del cilindro
    new_axis = np.dot(Rz, np.dot(Ry, np.dot(Rx, [0, 0, 3])))

    for part in rotating_parts:
        part.axis = vec(new_axis[0], new_axis[1], new_axis[2])

atmospheric_pressure_graph = graph(
    title="<b>Atmospheric Pressure</b>",
    xtitle="<b>Time (s)</b>",
    ytitle="<b>Pressure (Pa)</b>",
    xmin=0,
    ymin=90000,
    fast=True,
    align="right",
    background=color.black,  # Fondo negro
    foreground=color.black,  # Letras blancas
    width=750
)
atmospheric_pressure_curve = gcurve(graph=atmospheric_pressure_graph, color=color.red, width=4)

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
temperature_curve = gcurve(graph=temperature_graph, color=color.cyan, width=4)

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
relative_humidity_curve = gcurve(graph=relative_humidity_graph, color=color.green, width=4)


# Data point index
i = 0

"""
# Simulated data update loop
while True:
    # Generar nuevos valores de ángulos
    angle_x += random.uniform(-0.05, 0.05)
    angle_y += random.uniform(-0.05, 0.05)
    angle_z += random.uniform(-0.05, 0.05)

    # Aplicar la nueva orientación
    update_rotation()
    
    if out_of_date:
        warning_label.text = "⚠ Out of Date!"
    else:
        warning_label.text = ""

    # Generar valores de sensores simulados
    pressure = random.uniform(98000, 102000)
    temperature = random.uniform(15, 30)
    humidity = random.uniform(30, 80)

    # Agregar valores a las gráficas
    atmospheric_pressure_curve.plot(i, pressure)
    temperature_curve.plot(i, temperature)
    relative_humidity_curve.plot(i, humidity)

    # Increment index
    i += 1

    # Update frequency in Hz
    rate(10)
"""

# Actualiza la interfaz con los paquetes binarios enviados por el MPU-6500.
serial_connection = open_serial_port()
serial_buffer = bytearray()
last_packet_time = 0.0
last_filter_time = time.monotonic()
roll_filter = AngleKalmanFilter()
pitch_filter = AngleKalmanFilter()
yaw_filter = AngleKalmanFilter()

while True:
    now = time.monotonic()
    # Limitar dt evita una predicción enorme si el equipo se suspende o se pausa.
    dt = min(now - last_filter_time, 0.25)
    last_filter_time = now

    roll_filter.predict(dt)
    pitch_filter.predict(dt)
    yaw_filter.predict(dt)
    telemetry = read_telemetry(serial_connection, serial_buffer)

    if telemetry is not None:
        roll_filter.update(telemetry["roll"])
        pitch_filter.update(telemetry["pitch"])
        yaw_filter.update(telemetry["yaw"])

        atmospheric_pressure_curve.plot(i, telemetry["pressure"])
        temperature_curve.plot(i, telemetry["temperature"])
        relative_humidity_curve.plot(i, telemetry["humidity"])
        i += 1
        last_packet_time = now

    if roll_filter.initialized:
        # Durante una pérdida de señal el modelo sigue moviéndose con Kalman.
        angle_x = np.radians(roll_filter.angle)
        angle_y = np.radians(pitch_filter.angle)
        angle_z = np.radians(yaw_filter.angle)
        update_rotation()

    if not roll_filter.initialized:
        warning_label.text = "Waiting for telemetry"
    elif now - last_packet_time > STALE_AFTER_SECONDS:
        warning_label.text = "Kalman prediction (no signal)"
    else:
        warning_label.text = ""

    # Lee el puerto con frecuencia, aunque el Arduino envía telemetría a 5 Hz.
    rate(60)
