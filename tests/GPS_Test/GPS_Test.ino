#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// Inicializa las bibliotecas y el puerto serial
TinyGPSPlus gps;
HardwareSerial GPS_Serial(0);

void setup() {
  // Configura el puerto serial para la depuración
  Serial.begin(115200);
  
  // Configura el puerto serial para el GPS
  GPS_Serial.begin(9600, SERIAL_8N1, 7, 6);
}

void loop() {
  // Lee datos del GPS
  while (GPS_Serial.available() > 0) {
    gps.encode(GPS_Serial.read());
  }
  
  // Si se recibe una ubicación válida, la muestra por el puerto serial
  if (gps.location.isUpdated()) {
    Serial.print("Latitud: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitud: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Satélites: ");
    Serial.println(gps.satellites.value());
    Serial.print("Altitud: ");
    Serial.println(gps.altitude.meters());
    Serial.println();
  }
}
