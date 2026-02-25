import serial
import struct
import asyncio

variable_names = ['Acceleration_x', 'Acceleration_y', 'Acceleration_z',
                  'Rotation_x', 'Rotation_y', 'Rotation_z',
                  'Pitch', 'Roll', 'Yaw',
                  'Speed']

variable_values = {name: 0.0 for name in variable_names}
CanSats = ['M1', 'M2', 'M3', 'M4']

data = {CanSat_name: variable_values.copy() for CanSat_name in CanSats}

# Serial port configuration
ser = serial.Serial('COM24', 115200, timeout=1)

async def read_serial_data():
    while True:
        if ser.in_waiting >= 100:
            packet = ser.read_all()
            print(packet)
            header = packet[:4].decode('ascii')
            sender = packet[4:6].decode('ascii')

            if header == "CSWS" and sender in CanSats:
                process_serial_data(packet)

        await asyncio.sleep(0.1)


def process_serial_data(packet):
    header = packet[:4].decode('ascii')
    sender = packet[4:6].decode('ascii')
    receiver = packet[6:8].decode('ascii')
    values = struct.unpack('10f', packet[8:48])
    tail = packet[96:100].decode('ascii')

    # There are 10 variables to unpack
    for i in range(10):
        data[sender][variable_names[i]] = values[i]

async def main():
    await read_serial_data()


asyncio.run(main())
