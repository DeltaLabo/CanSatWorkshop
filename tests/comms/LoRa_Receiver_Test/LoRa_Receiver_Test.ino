#include <SPI.h>
#include <LoRa.h>

#define RST D1
#define DIO0 D2
#define NSS D3

void setup() {
  Serial.begin(115200);

  LoRa.setPins(NSS, RST, DIO0);

  if (!LoRa.begin(915E6)) {
    Serial.println("Error iniciando LoRa!");
    while (1);
  }

  // Configuración de radio
  LoRa.setSpreadingFactor(12);   // SF7–12
  LoRa.setSignalBandwidth(125E3); // 125E3, 250E3, 500E3
  LoRa.setCodingRate4(5);        // 5 = 4/5, 8 = 4/8
  LoRa.setTxPower(17);           // potencia en dBm

  Serial.println("LoRa Rx listo!");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Paquete recibido: ");

    // Read byte per byte
    while (LoRa.available()) {
      char c = (char)LoRa.read();
      Serial.print(c);
    }

    // RSSI = power in dBm
    Serial.print("  | RSSI: ");
    Serial.println(LoRa.packetRssi());
  }
}
