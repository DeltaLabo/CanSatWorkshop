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

// LoRa payload with a size of 100 bytes
byte payload[100];

// Data request expected from ground station
byte TXRequest[16];

// Flag to detect incoming LoRa data
volatile bool LoRaDataAvailable = false;
// 16 byte buffer for incoming LoRa data
// Its size is the same as TXRequest, since that's the only data expected to be received
byte RXBuffer[16];
/******* End Comms Global Variables *******/

/******* Begin Sensor Global Variables *******/
/******* End Sensor Global Variables *******/

/******* Begin Position and Orientation Global Variables *******/
/******* End Position and Orientation Global Variables *******/

/******* Begin Comms Functions *******/
// Read all variables and package them into a LoRa payload
void PackagePayload() {
  /*******
   * Example:
   * // Read the variable
   * floatUnion.value = readVariable(); // The function must return a float
   * // Insert the variable into the payload, byte by byte
   * // Note that the ESP32 is little-endian
   * // varSizeinBytes == 4 for a float variable
   * for (int i=0;i<varSizeinBytes;i++) payload[i+startByte] = floatUnion.bytes[i];
  *******/ 

  floatUnion.value = readVelocity(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+8] = floatUnion.bytes[i];

  floatUnion.value = readRotation(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+12] = floatUnion.bytes[i];

  floatUnion.value = readAcceleration(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+16] = floatUnion.bytes[i];

  floatUnion.value = readPosition(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+20] = floatUnion.bytes[i];

  floatUnion.value = readOrientation(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+24] = floatUnion.bytes[i];

  floatUnion.value = readAltitude(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+28] = floatUnion.bytes[i];

  floatUnion.value = readPressure(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+32] = floatUnion.bytes[i];

  floatUnion.value = readTemperature(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+36] = floatUnion.bytes[i];

  floatUnion.value = readVoltage(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+40] = floatUnion.bytes[i];

  floatUnion.value = readCurrent(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+44] = floatUnion.bytes[i];
}

// Sends the populated payload via LoRa
void SendPayload() {
  // Write AT command for LoRa send, targeting all radio addresses (0), with
  // a payload size of 100 bytes
  // Note that radio addresses are not a LoRa standard but specific to the
  // transceiver being used, thus they're not implemented
  LoRa.print("AT+SEND=0,100,");
  // Write payload as a byte array of size 100
  LoRa.write(payload, 100);
  // Write CRLF to terminate the command, as required by the transceiver
  LoRa.println();
}

// Interrupt Service Routine (ISR) for UART
void IRAM_ATTR uartISR() {
  // Read from LoRa serial port
  // Only 16 bytes are read since that's the ground station request size
  LoRa.readBytes(RXBuffer, 16);
  // Signal that there's incoming data available to check for ground station requests
  LoRaDataAvailable = true;
}
/******* End Comms Functions *******/

/******* Begin Sensor Functions *******/
/******* End Sensor Functions *******/

/******* Begin Position and Orientation Functions *******/
/******* End Position and Orientation Functions *******/

void setup() {
  /******* Begin Comms Setup *******/
  // 8 bits, no parity, 1 stop bit
  LoRa.begin(115200, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
  // Enable an interrupt whenever any data is received
  LoRa.enableRxInterrupt();
  // Attach ISR to RX interrupt to read the incoming data
  LoRa.attachRxInterrupt(uartISR);

  // Construct the expected request from the ground station
  strcpy((char*)TXRequest, LORA_HEADER);
  strcat((char*)TXRequest, GS_LORA_ID);
  strcat((char*)TXRequest, CANSAT_LORA_ID);
  strcat((char*)TXRequest, "DATA");
  strcat((char*)TXRequest, LORA_FOOTER);

  // Set LoRa frequency band
  // The LORA_BAND variable is in MHz
  LoRa.print("AT+BAND=");
  LoRa.print(LORA_BAND);
  LoRa.println("000000");

  // Set Spreading Factor, Bandwidth, and Coding Rate
  // The ",0" at the end sets the radio to not send any network ID data as a preamble,
  // since sender and receiver identification will be implemented within the payload
  Lora.print("AT+PARAMETER=");
  Lora.print(LORA_SF);
  Lora.print(",");
  Lora.print(LORA_BANDWIDTH);
  Lora.print(",");
  Lora.print(LORA_CODING_RATE)
  Lora.println(",0");

  // Populate payload with its default values
  // Header
  for (int i=0;i<4;i++) payload[i] = LORA_HEADER[i];
  // Sender ID
  for (int i=0;i<2;i++) payload[i+4] = CANSAT_LORA_ID[i];
  // Receiver ID
  for (int i=0;i<2;i++) payload[i+6] = GS_LORA_ID[i];
  // Space reserved for future development
  for (int i=0;i<48;i++) payload[i+48] = 0;
  // Footer
  for (int i=0;i<4;i++) payload[i+96] = LORA_FOOTER[i];
  /******* End Comms Setup *******/

  /******* Begin Sensor Setup *******/
  /******* End Sensor Setup *******/

  /******* Begin Position and Orientation Setup *******/
  /******* End Position and Orientation Setup *******/
}

// The loop function should only be used for LoRa comms
void loop() {
  // If any data was received via LoRa
  if (LoRaDataAvailable == true) {
    // If the incoming data is a valid request from the ground station
    if (memcmp(RXBuffer, TXRequest, 16) == 0) {
      // Respond to the request
      PackagePayload();
      SendPayload();
    }

    // Signal that the incoming data was checked
    LoRaDataAvailable = false;
  }
}