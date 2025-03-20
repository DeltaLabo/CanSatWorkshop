from raspi_lora import LoRa, ModemConfig

# This is our callback function that runs when a message is received
def on_recv(payload):
    print("From:", payload.header_from)
    print("Received:", payload.message)
    print("RSSI: {}; SNR: {}".format(payload.rssi, payload.snr))

lora = LoRa(
    1, # SPI Channel
    26, # Interrupt pin, in BOARD numbering
    2, # Device address
    modem_config=ModemConfig.Bw125Cr45Sf128,
    tx_power=14,
    acks=True
)
lora.on_recv = on_recv

lora.set_mode_rx()

# Send a message to a recipient device with address 10
# Retry sending the message twice if we don't get an  acknowledgment from the recipient
message = "Hello there!"
status = lora.send_to_wait(message, 10, retries=2)
if status is True:
    print("Message sent!")
else:
    print("No acknowledgment from recipient")
    
# And remember to call this as your program exits...
lora.close()