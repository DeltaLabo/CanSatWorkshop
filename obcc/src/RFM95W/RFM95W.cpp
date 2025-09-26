#include "RFM95W.h"

byte initRFM95W() {
    LoRa.setPins(LORA_NSS, LORA_RESET, LORA_DIO0);

    // Configuración de radio
    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125E3); // Hz
    LoRa.setCodingRate4(5);
    LoRa.setTxPower(17); // dBm

    if (!LoRa.begin(915E6)) { // Hz
       return 1;
    }

    return 0;
}