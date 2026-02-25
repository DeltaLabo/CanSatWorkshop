#ifndef SETTINGS
#define SETTINGS

#include <string.h>

/******* Begin Comms Settings *******/
// Header to identify LoRa packages out of all possible LoRa comms in the area
#define LORA_HEADER String("CSWS") // [C]an[S]at [W]ork[s]hop

// Footer to check message integrity
#define LORA_FOOTER String("DTLB") // [D]el[t]a [L]a[b]

// Unique ID of the CanSat (2 alphanumeric characters)
String CANSAT_LORA_IDS[] = {String("M1"), String("M2"), String("M3")};

// Unique ID of the ground station                               
#define GS_LORA_ID String("GS")

// Ground station TX request command
#define LORA_TX_COMMAND String("DATA")

// LoRa frequency band
// 915 MHz for Costa Rica and Panama
#define LORA_BAND String("915") // MHz

// Spreading Factors 5 to 11 are supported
#define LORA_SF String("7")

// 7: 125 kHz (SF7 to SF9)
// 8: 250 kHz (SF7 to SF10)
// 9: 500 kHz (SF7 to DF11)
#define LORA_BANDWIDTH String("7")

// Coding rates 1 to 4 are supported
#define LORA_CODING_RATE String("1")

// Period between ground station TX requests
#define GS_TX_REQUEST_PERIOD 1000 // ms

// Time that the ground station waits for a response after a TX Request
#define GS_LISTEN_PERIOD 500 // ms

#define LORA_PAYLOAD_SIZE 100 // bytes
// Total amount of bytes expected to be received
#define LORA_RX_BUFFER_SIZE LORA_PAYLOAD_SIZE + sizeof("0,100,,RSS,SNR")
/******* End Comms Settings *******/

/******* Begin Sensor Settings *******/
/******* End Sensor Settings *******/

/******* Begin Position and Orientation Settings *******/
/******* End Position and Orientation Settings *******/

#endif