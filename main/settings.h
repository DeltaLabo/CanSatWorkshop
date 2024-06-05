#ifndef SETTINGS
#define SETTINGS

/******* Begin Comms Settings *******/
// Header to identify LoRa packages out of all possible LoRa comms in the area
#define LORA_HEADER "CSWS" // [C]an[S]at [W]ork[s]hop

// Footer to check message integrity
#define LORA_FOOTER "DTLB" // [D]el[t]a [L]a[b]

// Unique ID of the CanSat (2 alphanumeric characters)
#define CANSAT_LORA_ID "M1"

// Unique ID of the ground station
#define GS_LORA_ID "GS"

// LoRa frequency band
// 915 MHz for Costa Rica and Panama
#define LORA_BAND "915" // MHz

// Spreading Factors 5 to 11 are supported
#define LORA_SF "5"

// 7: 125 kHz (SF7 to SF9)
// 8: 250 kHz (SF7 to SF10)
// 9: 500 kHz (SF7 to DF11)
#define LORA_BANDWIDTH "7"

// Coding rates 1 to 4 are supported
#define LORA_CODING_RATE "1"

#define PAYLOAD_LENGTH "240"
/******* End Comms Settings *******/

/******* Begin Sensors Settings *******/
/******* End Sensors Settings *******/

/******* Begin Position and Orientation Settings *******/
/******* End Position and Orientation Settings *******/

#endif