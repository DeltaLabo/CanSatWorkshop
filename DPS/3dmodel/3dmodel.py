import serial
import struct
import asyncio
from flask import Flask, jsonify, send_from_directory, request

app = Flask(__name__)

# Serial port configuration
ser = serial.Serial('COM36', 115200, timeout=1)  # Adjust the port and speed as necessary

# Sensor data
variable_values = {
    'gyroX': 0.0,
    'gyroY': 0.0,
    'gyroZ': 0.0,
    'accX': 0.0,
    'accY': 0.0,
    'accZ': 0.0,
    'speed': 0.0
}

gyroXerror = 0.07
gyroYerror = 0.03
gyroZerror = 0.01

# Event handling and server initialization
@app.route('/')
def index():
    return send_from_directory('.', '3dmodel.html')

@app.route('/reset', methods=['GET'])
def reset_all():
    variable_values['gyroX'] = 0.0
    variable_values['gyroY'] = 0.0
    variable_values['gyroZ'] = 0.0
    return "OK"

@app.route('/resetX', methods=['GET'])
def reset_x():
    variable_values['gyroX'] = 0.0
    return "OK"

@app.route('/resetY', methods=['GET'])
def reset_y():
    variable_values['gyroY'] = 0.0
    return "OK"

@app.route('/resetZ', methods=['GET'])
def reset_z():
    variable_values['gyroZ'] = 0.0
    return "OK"

@app.route('/gyro_readings', methods=['GET'])
def get_gyro_readings():
    return jsonify({
        'gyroX': variable_values['gyroX'],
        'gyroY': variable_values['gyroY'],
        'gyroZ': variable_values['gyroZ']
    })

@app.route('/accelerometer_readings', methods=['GET'])
def get_acc_readings():
    return jsonify({
        'accX': variable_values['accX'],
        'accY': variable_values['accY'],
        'accZ': variable_values['accZ']
    })

@app.route('/speed_reading', methods=['GET'])
def get_speed_reading():
    return jsonify({
        'speed': variable_values['speed']
    })

async def read_serial_data():
    while True:
        if ser.in_waiting >= 100:  # Check if there's enough data for a full packet
            packet = ser.read_all()
            process_serial_data(packet)
        await asyncio.sleep(0.01)

def process_serial_data(packet):
    values = struct.unpack('10f', packet[8:48])
    
    # Process gyroscope data with error correction
    gyroX_temp = values[3]
    if abs(gyroX_temp) > gyroXerror:
        variable_values['gyroX'] += gyroX_temp / 50.0

    gyroY_temp = values[4]
    if abs(gyroY_temp) > gyroYerror:
        variable_values['gyroY'] += gyroY_temp / 70.0

    gyroZ_temp = values[5]
    if abs(gyroZ_temp) > gyroZerror:
        variable_values['gyroZ'] += gyroZ_temp / 90.0

    # Update accelerometer and speed data
    variable_values['accX'] = values[0]
    variable_values['accY'] = values[1]
    variable_values['accZ'] = values[2]
    variable_values['speed'] = values[9]

async def main():
    await read_serial_data()

if __name__ == "__main__":
    # Start the web server
    loop = asyncio.get_event_loop()
    loop.create_task(main())
    
    # Run Flask in a separate thread to allow asyncio tasks to run concurrently
    from threading import Thread
    server_thread = Thread(target=lambda: app.run(host='0.0.0.0', port=80, debug=False, use_reloader=False))
    server_thread.start()

    # Run the event loop
    loop.run_forever()
