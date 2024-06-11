// Turn off built-in OLED display
#define NO_DISPLAY
#include <heltec_unofficial.h>

#include "settings.h"

// Transmit power. 0 dBm = 1 mW, 10 dBm = 10 mW.
#define GS_TRANSMIT_POWER      10 // dBm

// LoRa comms states
#define IDLE 0 // Waiting to send a new TX Request
#define LISTEN 1 // Awaiting a responde to the last TX Request

// Byte array to store the incoming LoRa data
byte RXBuffer[100+17];
// Flag to signal when any data was received via LoRa
volatile bool RXFlag = false;
// LoRa comms initial state is to wait for LORA_PERIOD and then send a TX Request
short LoRaState = IDLE;
// Time counter for TX Request and state change intervals
uint32_t t0;

void setup() {
  // Automatically setup radio
  heltec_setup();
  RADIOLIB_OR_HALT(radio.begin());
  // Set the callback function for received packets
  radio.setDio1Action(LoRaRXISR);
  // Set radio parameters
  RADIOLIB_OR_HALT(radio.setFrequency(LORA_BAND.toFloat()));
  if (LORA_BANDWIDTH.toInt() == 7) {
    RADIOLIB_OR_HALT(radio.setBandwidth(125.0));
  } else if (LORA_BANDWIDTH.toInt() == 8) {
    RADIOLIB_OR_HALT(radio.setBandwidth(250.0));
  } else if (LORA_BANDWIDTH.toInt() == 9) {
    RADIOLIB_OR_HALT(radio.setBandwidth(500.0));
  }
  RADIOLIB_OR_HALT(radio.setSpreadingFactor(LORA_SF.toInt()));
  RADIOLIB_OR_HALT(radio.setOutputPower(GS_TRANSMIT_POWER));
  // Initiallize time counter
  t0 = millis();
}

void loop() {
  // Required by Heltec MCU
  heltec_loop();

  // Wait for the specified period before sending a TX Request
  if (millis() - t0 >= GS_TX_REQUEST_PERIOD && LoRaState == IDLE) {
    // Clear Radio state
    radio.clearDio1Action();
    // Turn on LED at 50% brightness
    heltec_led(40);
    // Send TX Request
    RADIOLIB(radio.transmit("0,16,CSWSGSM1DATADTLB", 16));//TXRequest.c_str()));
    // Enter receive mode
    radio.setDio1Action(LoRaRXISR);
    RADIOLIB_OR_HALT(radio.startReceive(GS_LISTEN_PERIOD*1000.0/15.625));
    LoRaState = LISTEN;
    // Turn off LED
    heltec_led(0);
    // Update time counter
    t0 = millis();
  }
  // Await a response to the TX Request for the specified period
  else if (millis() - t0 >= GS_LISTEN_PERIOD && LoRaState == LISTEN) {
    // Once the wait time expires, return to IDLE mode
    LoRaState = IDLE;
    // Update time counter
    t0 = millis();
  }

  // If a packet was received, display it with the RSSI and SNR
  if (RXFlag) {
    // Signal that the incoming LoRa data will be read
    RXFlag = false;
    // Exit out of LISTEN state
    LoRaState = IDLE;
    radio.readData(RXBuffer, 100 + 17);
    // If there were no errors
    if (_radiolib_status == RADIOLIB_ERR_NONE) {
      // Print the incoming data
      Serial.write(RXBuffer, 100 + 17);
      Serial.printf("  RSSI: %.2f dBm\n", radio.getRSSI());
      Serial.printf("  SNR: %.2f dB\n", radio.getSNR());
    }
    // Update time counter
    t0 = millis();
  }
}

// Interrupt callback on LoRa RX
void LoRaRXISR() {
  // Signal that there is LoRa data pending to read
  RXFlag = true;
}