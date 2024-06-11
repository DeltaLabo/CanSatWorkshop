import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import struct

# Configure the serial port (make sure to replace 'COM3' with your actual serial port)
ser = serial.Serial('COM37', 115200, timeout=1)

# Initialize lists to store the data
velocity = []
rotation = []
acceleration = []
position = []
orientation = []
altitude = []
pressure = []
temperature = []
voltage = []
current = []

# Set up the figures and axes
velocity_fig, ax1 = plt.subplots()
rotation_fig, ax2 = plt.subplots()
acceleration_fig, ax3 = plt.subplots()
position_fig, ax4 = plt.subplots()
orientation_fig, ax5 = plt.subplots()
altitude_fig, ax6 = plt.subplots()
pressure_fig, ax7 = plt.subplots()
temperature_fig, ax8 = plt.subplots()
voltage_fig, ax9 = plt.subplots()
current_fig, ax10 = plt.subplots()

# Initialize line objects
line1, = ax1.plot([], [], 'r-')
line2, = ax2.plot([], [], 'b-')
line3, = ax3.plot([], [], 'g-')
line4, = ax4.plot([], [], 'c-')
line5, = ax5.plot([], [], 'm-')
line6, = ax6.plot([], [], 'y-')
line7, = ax7.plot([], [], 'k-')
line8, = ax8.plot([], [], 'r:')
line9, = ax9.plot([], [], 'b:')
line10, = ax10.plot([], [], 'g:')

def init():
    ax1.set_xlim(0, 100)
    ax1.set_ylim(0, 1023)
    ax2.set_xlim(0, 100)
    ax2.set_ylim(0, 1023)
    ax3.set_xlim(0, 100)
    ax3.set_ylim(0, 1023)
    ax4.set_xlim(0, 100)
    ax4.set_ylim(0, 1023)
    ax5.set_xlim(0, 100)
    ax5.set_ylim(0, 1023)
    ax6.set_xlim(0, 100)
    ax6.set_ylim(0, 1023)
    ax7.set_xlim(0, 100)
    ax7.set_ylim(0, 1023)
    ax8.set_xlim(0, 100)
    ax8.set_ylim(0, 1023)
    ax9.set_xlim(0, 100)
    ax9.set_ylim(0, 1023)
    ax10.set_xlim(0, 100)
    ax10.set_ylim(0, 1023)
    return line1, line2, line3, line4, line5, line6, line7, line8, line9, line10

def update(frame):
    try:
        line = ser.readline().decode('utf-8').strip()  # Read a line from the serial port
        print("serial string received")
        print(line)
        if line.startswith("+RCV"):
            print("string contains payload")
            velocity.append(struct.unpack('<f', line[11+8:11+8+4])[0])
            rotation.append(struct.unpack('<f', line[11+12:11+12+4])[0])
            acceleration.append(struct.unpack('<f', line[11+16:11+16+4])[0])
            position.append(struct.unpack('<f', line[11+20:11+20+4])[0])
            orientation.append(struct.unpack('<f', line[11+24:11+24+4])[0])
            altitude.append(struct.unpack('<f', line[11+28:11+28+4])[0])
            pressure.append(struct.unpack('<f', line[11+32:11+32+4])[0])
            temperature.append(struct.unpack('<f', line[11+36:11+36+4])[0])
            voltage.append(struct.unpack('<f', line[11+40:11+40+4])[0])
            current.append(struct.unpack('<f', line[11+44:11+44+4])[0])

            # Update the x-axis limit if necessary
            if len(velocity) > 100:
                ax1.set_xlim(len(velocity) - 100, len(velocity))
                ax2.set_xlim(len(rotation) - 100, len(rotation))
                ax3.set_xlim(len(acceleration) - 100, len(acceleration))
                ax4.set_xlim(len(position) - 100, len(position))
                ax5.set_xlim(len(orientation) - 100, len(orientation))
                ax6.set_xlim(len(altitude) - 100, len(altitude))
                ax7.set_xlim(len(pressure) - 100, len(pressure))
                ax8.set_xlim(len(temperature) - 100, len(temperature))
                ax9.set_xlim(len(voltage) - 100, len(voltage))
                ax10.set_xlim(len(current) - 100, len(current))

            # Update data for plotting
            line1.set_data(np.arange(len(velocity)), velocity)
            line2.set_data(np.arange(len(rotation)), rotation)
            line3.set_data(np.arange(len(acceleration)), acceleration)
            line4.set_data(np.arange(len(position)), position)
            line5.set_data(np.arange(len(orientation)), orientation)
            line6.set_data(np.arange(len(altitude)), altitude)
            line7.set_data(np.arange(len(pressure)), pressure)
            line8.set_data(np.arange(len(temperature)), temperature)
            line9.set_data(np.arange(len(voltage)), voltage)
            line10.set_data(np.arange(len(current)), current)
    except:
        pass
    return line1, line2, line3, line4, line5, line6, line7, line8, line9, line10

# Set up the animation
ani1 = animation.FuncAnimation(velocity_fig, update, init_func=init, blit=True, interval=50)
ani2 = animation.FuncAnimation(rotation_fig, update, init_func=init, blit=True, interval=50)
ani3 = animation.FuncAnimation(acceleration_fig, update, init_func=init, blit=True, interval=50)
ani4 = animation.FuncAnimation(position_fig, update, init_func=init, blit=True, interval=50)
ani5 = animation.FuncAnimation(orientation_fig, update, init_func=init, blit=True, interval=50)
ani6 = animation.FuncAnimation(altitude_fig, update, init_func=init, blit=True, interval=50)
ani7 = animation.FuncAnimation(pressure_fig, update, init_func=init, blit=True, interval=50)
ani8 = animation.FuncAnimation(temperature_fig, update, init_func=init, blit=True, interval=50)
ani9 = animation.FuncAnimation(voltage_fig, update, init_func=init, blit=True, interval=50)
ani10 = animation.FuncAnimation(current_fig, update, init_func=init, blit=True, interval=50)

# Show the plots
plt.show()

# Close the serial port when done
ser.close()
