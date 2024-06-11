#include <HardwareSerial.h>

//#define XIAO
//#define SENDER

#ifdef XIAO
#define LORA_TX_PIN D0
#define LORA_RX_PIN D1
#else
#define LORA_TX_PIN 5
#define LORA_RX_PIN 4
#endif

// Header to identify LoRa packages out of all possible LoRa comms in the area
#define LORA_HEADER String("CSWS") // [C]an[S]at [W]ork[s]hop

// Footer to check message integrity
#define LORA_FOOTER String("DTLB") // [D]el[t]a [L]a[b]

// Unique ID of the CanSat (2 alphanumeric characters)
#define CANSAT_LORA_ID String("M1")

// Unique ID of the ground station                               
#define GS_LORA_ID String("GS")

// Ground station TX request command
#define LORA_TX_COMMAND String("DATA")

// LoRa frequency band
// 915 MHz for Costa Rica and Panama
#define LORA_BAND String("915") // MHz

// Spreading Factors 5 to 11 are supported
#define LORA_SF String("5")

// 7: 125 kHz (SF7 to SF9)
// 8: 250 kHz (SF7 to SF10)
// 9: 500 kHz (SF7 to DF11)
#define LORA_BANDWIDTH String("7")

// Coding rates 1 to 4 are supported
#define LORA_CODING_RATE String("1")

// Data request expected from ground station
String TXRequest = LORA_HEADER + GS_LORA_ID + CANSAT_LORA_ID + LORA_TX_COMMAND + LORA_FOOTER;

// Serial port to communicate with the LoRa radio
HardwareSerial LoRa(1);

void setup() {
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

  #ifndef SENDER
  Serial.begin(9600);
  #endif
}

void loop() {
    #ifdef SENDER
    LoRa.println("AT+SEND=0,16," + TXRequest);
    delay(500);
    #else
    // If any data was received via LoRa
    if (LoRa.available() > 0) {
        // Read from LoRa serial port
        // Only 16 bytes are read since that's the ground station request size
        String RXString = LoRa.readString();

        // If the incoming data contains a valid request from the ground station
        if (RXString.indexOf(TXRequest) != -1) {
          Serial.print(RXString);
        }
    }
    #endif
}