#include <HardwareSerial.h>
#include <Arduino.h>
#include <string.h>

#include "settings.h"
#include "pins.h"

/******* Begin Comms Global Variables *******/
// Serial port to communicate with the LoRa radio
HardwareSerial LoRa(1);

// Used to convert a float as a 4-byte array
union {
  float value;
  byte bytes[4];
} floatUnion;

// LoRa comms states
#define NORMAL 0 // Normal operation, idle or transmit states
#define LISTEN 1 // Awaiting response to a TX Request
short LoRaState = NORMAL;

// Time counter for LoRa TX request period
uint32_t lastCheckTime = millis();
/******* End Comms Global Variables *******/

/******* Begin Sensor Global Variables *******/
/******* End Sensor Global Variables *******/

/******* Begin Position and Orientation Global Variables *******/
/******* End Position and Orientation Global Variables *******/

/******* Begin Comms Functions *******/
/******* End Comms Functions *******/

/******* Begin Sensor Functions *******/
/******* End Sensor Functions *******/

/******* Begin Position and Orientation Functions *******/
/******* End Position and Orientation Functions *******/

void setup() {
  /******* Begin Comms Setup *******/
  // 8 bits, no parity, 1 stop bit
  LoRa.begin(115200, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
  // Set buffer size to 100 bytes to transmit payload
  LoRa.setTxBufferSize(100);
  // Set UART RX timeout to 1 ms
  // Since the baud rate is 115200, more than 1 ms without receiving data
  // means that the transmission has ended 
  LoRa.setTimeout(1); 

  // Set LoRa frequency band
  // The LORA_BAND variable is in MHz
  LoRa.println("AT+BAND=" + LORA_BAND + "000000");

  // Set Spreading Factor, Bandwidth, and Coding Rate
  // The ",0" at the end sets the radio to not send any network ID data as a preamble,
  // since sender and receiver identification will be implemented within the payload
  LoRa.println("AT+PARAMETER=" + LORA_SF + "," + LORA_BANDWIDTH + "," + LORA_CODING_RATE + ",0");

  // Serial port for logging
  Serial.begin(115200);
  /******* End Comms Setup *******/

  /******* Begin Sensor Setup *******/
  /******* End Sensor Setup *******/

  /******* Begin Position and Orientation Setup *******/
  /******* End Position and Orientation Setup *******/
}

// The loop function should only be used for LoRa comms polling
void loop() {
  if (millis() - lastCheckTime >= GS_TX_REQUEST_PERIOD && LoRaState == NORMAL) {
    LoRa.print("AT+SEND=0,16,");
    LoRa.println(TXRequest);
    // Transition to LISTEN state
    LoRaState = LISTEN;
    // Reset time counter
    lastCheckTime = millis();
  }
  else if (millis() - lastCheckTime <= GS_LISTEN_PERIOD && LoRaState == LISTEN) {
    // If any data was received via LoRa
    if (LoRa.available() > 0) {
      // Read from LoRa serial port
      String RXString = LoRa.readString();
      if (RXString.indexOf(LORA_HEADER) != -1) {
        RXString.remove(0,16);
        if (RXString.substring(0, 4) == "CSWS") {
          RXString.remove(LORA_PAYLOAD_SIZE, sizeof(RXString));
          Serial.println(RXString);
        }
      }
      // Transition back to NORMAL state
      LoRaState = NORMAL;
      // Reset time counter
      lastCheckTime = millis();
    }
  }
  else if (LoRaState == LISTEN) {
    // Transition back to NORMAL state
    LoRaState = NORMAL;
    // Reset time counter
    lastCheckTime = millis();
  }
}