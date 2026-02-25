import serial
import time
import threading
from flask import Flask, render_template_string
import folium
from folium.plugins import MarkerCluster

# ---------------- CONFIG ----------------
PUERTO = "COM3"
BAUDRATE = 115200
UPDATE_INTERVAL = 2
# ----------------------------------------

gps_data = []
app = Flask(__name__)

# Leer GPS en hilo separado
def leer_serial():
    global gps_data
    ser = serial.Serial(PUERTO, BAUDRATE, timeout=1)
    time.sleep(2)

    while True:
        linea = ser.readline().decode(errors='ignore').strip()
        if not linea:
            continue
        cols = linea.split(",")
        if len(cols) < 5:
            continue
        try:
            lat = float(cols[0])
            lon = float(cols[1])
            alt = float(cols[2])
            time_utc = cols[3]
            course = float(cols[4])
        except:
            continue
        gps_data.append({
            "lat": lat,
            "lon": lon,
            "alt_m": alt,
            "time_utc": time_utc,
            "course_deg": course
        })
        print(f"Punto recibido: {lat}, {lon}, alt={alt}, time={time_utc}, dir={course}")

# Ruta principal para mostrar mapa
@app.route("/")
def mapa():
    if not gps_data:
        # Mapa vacío inicial
        m = folium.Map(location=[0,0], zoom_start=2)
    else:
        lat0 = gps_data[-1]["lat"]
        lon0 = gps_data[-1]["lon"]
        m = folium.Map(location=[lat0, lon0], zoom_start=18)
        cluster = MarkerCluster().add_to(m)
        for punto in gps_data:
            folium.Marker(
                location=[punto["lat"], punto["lon"]],
                popup=(
                    f"Lat: {punto['lat']:.6f}<br>"
                    f"Lon: {punto['lon']:.6f}<br>"
                    f"Alt Relativa: {punto['alt_m']:.2f} m<br>"
                    f"Hora UTC: {punto['time_utc']}<br>"
                    f"Rumbo: {punto['course_deg']:.2f}°"
                ),
                icon=folium.Icon(color='blue', icon='info-sign')
            ).add_to(cluster)
        folium.PolyLine(
            locations=[[p["lat"], p["lon"]] for p in gps_data],
            color="red",
            weight=2
        ).add_to(m)

    # Renderizamos HTML con meta refresh para recargar cada UPDATE_INTERVAL segundos
    html_str = m.get_root().render()
    html_template = f"""
    <html>
    <head>
        <meta http-equiv="refresh" content="{UPDATE_INTERVAL}">
    </head>
    <body>
        {html_str}
    </body>
    </html>
    """
    return html_template

# ---------------- MAIN ----------------
if __name__ == "__main__":
    hilo_lectura = threading.Thread(target=leer_serial, daemon=True)
    hilo_lectura.start()
    print("Servidor corriendo en http://127.0.0.1:5000/")
    app.run(debug=False)
