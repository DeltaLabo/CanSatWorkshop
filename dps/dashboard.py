from vpython import graph, gcurve, rate, color, canvas, cylinder, vec
import random

# Layout container that the 3D model is placed inside of
cansat_canvas = canvas(
    align="left"
)

# CanSat-ish 3D model
cansat = cylinder(
    canvas=cansat_canvas,
    axis=vec(3, 0, 0)
)

# Layout component for a 2D plot
atmospheric_pressure_graph = graph(
    title="Atmospheric Pressure",
    xtitle="Time (s)",
    ytitle="Pressure (Pa)",
    xmin=0,
    ymin=90000,
    fast=True,
    align="right" # Place right of CanSat model
)

# Actual plot
atmospheric_pressure_curve = gcurve(graph=atmospheric_pressure_graph, color=color.red)

temperature_graph = graph(
    title="Temperature",
    xtitle="Time (s)",
    ytitle="Temperature (°C)",
    xmin=0,
    ymin=-10,
    fast=True,
    align="left"
)
temperature_curve = gcurve(graph=temperature_graph, color=color.blue)

# Relative Humidity Graph
relative_humidity_graph = graph(
    title="Relative Humidity",
    xtitle="Time (s)",
    ytitle="Humidity (%)",
    xmin=0,
    ymin=0,
    ymax=100,
    fast=True,
    align="right"
)
relative_humidity_curve = gcurve(graph=relative_humidity_graph, color=color.green)

# Data point index
i = 0

# Simulated data update loop
while True:
    # Generate random test values
    pressure = random.uniform(98000, 102000)
    temperature = random.uniform(15, 30)
    humidity = random.uniform(30, 80)
    # Should be pitch, roll, yaw, but for now rotation
    cansat_rot_x = random.uniform(0, 0.28)
    cansat_rot_y = random.uniform(0, 0.28)
    cansat_rot_z = random.uniform(0, 0.28)

    # Append to 2D plots
    atmospheric_pressure_curve.plot(i, pressure)
    temperature_curve.plot(i, temperature)
    relative_humidity_curve.plot(i, humidity)
    # Rotate 3D model
    cansat.rotate(axis=vec(1, 0, 0), angle=cansat_rot_x)
    cansat.rotate(axis=vec(0, 1, 0), angle=cansat_rot_y)
    cansat.rotate(axis=vec(0, 0, 1), angle=cansat_rot_z)

    # Increment index
    i += 1

    # Update frequency in Hz
    rate(10)
