#ifndef RFM95W_H
#define RFM95W_H

#include <SPI.h>
#include <LoRa.h>

// Pin definitions
const int LORA_NSS = 2;
const int LORA_RESET = 3;
const int LORA_DIO0 = 4;
const int LORA_MOSI = 5;
const int LORA_MISO = 6;
const int LORA_SCK = 7;

void initRFM95W();

#endif // RFM95W_H