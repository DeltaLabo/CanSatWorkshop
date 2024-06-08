#include <HardwareSerial.h>
#include <String.h>
#include "settings.h"
#include "pins.h"

/******* Begin Comms Global Variables *******/
HardwareSerial LoRa(1);
/******* End Comms Global Variables *******/

/******* Begin Sensors Global Variables *******/
/******* End Sensors Global Variables *******/

/******* Begin Position and Orientation Global Variables *******/
/******* End Position and Orientation Global Variables *******/

void setup() {
  /******* Begin Comms Setup *******/
  // 8 bits, no parity, 1 stop bit
  LoRa.begin(115200, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);

  // Set LoRa frequency band
  LoRa.println("AT+BAND=" + LORA_BAND + "000000" + ",M");

  // Set Spreading Factor, Bandwidth, and Coding Rate
  Lora.println("AT+PARAMETER=" + LORA_SF + "," + LORA_BANDWIDTH + "," + LORA_CODING_RATE + ",0");
  /******* End Comms Setup *******/

  /******* Begin Sensors Setup *******/
  /******* End Sensors Setup *******/

  /******* Begin Position and Orientation Setup *******/
  /******* End Position and Orientation Setup *******/
}

void loop() {
  if(LoRa.available()) {
    String RX_Message = LoRa.readString();
    // Request expected from the ground station
    String TX_Request = LORA_HEADER + "," + GS_LORA_ID + "," + CANSAT_LORA_ID + "," + "DATA" + LORA_FOOTER;

    if (RX_Message == TX_Request) {
      // Read sensors

      // Package data

      // Send payload via LoRa
      LoRa.println("AT+SEND=0," + LENGTH + "," + PAYLOAD);
    }
  }
}