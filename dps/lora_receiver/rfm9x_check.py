# SPDX-FileCopyrightText: 2018 Brent Rubell for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""
Wiring Check, Orange Pi w/RFM9x

Learn Guide: Modified from https://learn.adafruit.com/lora-and-lorawan-for-raspberry-pi
Adapted for Orange Pi
"""
import time
import spidev
import OPi.GPIO as GPIO

# Configure GPIO settings
GPIO.setboard(GPIO.ORANGEPI_3)
GPIO.setmode(GPIO.BOARD)

# Configure RFM9x LoRa Radio
CS_PIN = 15
RESET_PIN = 14

# Setup GPIO
GPIO.setup(CS_PIN, GPIO.OUT)
GPIO.setup(RESET_PIN, GPIO.OUT)

# Initialize SPI
spi = spidev.SpiDev()
spi.open(0, 0)  # SPI bus 0, device 0
spi.max_speed_hz = 5000000  # 5MHz

# Create digital IO objects for the CS and RESET pins
class DigitalInOut:
    def __init__(self, pin):
        self.pin = pin
        self.switch_to_output(True)
    
    def switch_to_output(self, value=False):
        GPIO.output(self.pin, GPIO.HIGH if value else GPIO.LOW)
        self.value = value

cs = DigitalInOut(CS_PIN)
reset = DigitalInOut(RESET_PIN)

# Import the RFM9x radio module - do this after GPIO setup
import orangepi_rfm9x

try:
    # Initialize the RFM9x module
    rfm9x = orangepi_rfm9x.RFM9x(spi, cs, reset, 915.0)
    print("RFM9x: Detected")
    
    # Basic test of sending and receiving
    print("Sending test packet...")
    rfm9x.send(bytes("Hello Orange Pi!", "utf-8"))
    print("Waiting for packets...")

    # Wait for a packet
    packet = rfm9x.receive(timeout=5.0)
    if packet is not None:
        print("Received: ", packet)
        print("RSSI: ", rfm9x.last_rssi)
    else:
        print("No packet received")
        
except RuntimeError as error:
    # Thrown on version mismatch
    print(f"RFM9x Error: {error}")

# Clean up
spi.close()
GPIO.cleanup()