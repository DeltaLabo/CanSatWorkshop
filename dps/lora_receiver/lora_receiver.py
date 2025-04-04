from lora import LoRa
import time

# Custom handler for received messages
def on_recv(payload):
    print("Received: ", end="")
    print(payload.message.decode('utf-8'))
    print(f"Got: {payload.message.decode('utf-8')}")
    print(f"RSSI: {payload.rssi}")
    
    # Send a reply back to the sender
    reply_message = "And hello back to you"
    lora.send(reply_message.encode('utf-8'), payload.header_from)
    print("Sent a reply")
    print("-" * 30)

# LoRa module configuration
lora = LoRa(
    freq=915E6,  # Changed from 868MHz to 915MHz to match the Arduino example
    tx_power=23, # Increased from 14 to 23 dBm to match Arduino example
    channel=0,
    interrupt=5,
    this_address=10
)

# Set the callback function
lora.on_recv = on_recv

print("Arduino LoRa RX Test!")
print("LoRa radio init OK!")
print(f"Set Freq to: {int(915)}") # Display frequency like Arduino example

# Set the module in receive mode
lora.set_mode_rx()

try:
    # Keep the program running
    while True:
        time.sleep(0.1)
except KeyboardInterrupt:
    print("\nReceiver stopped")
finally:
    lora.close()
