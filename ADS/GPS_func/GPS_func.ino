#include <TinyGPSPlus.h>   // Si da error, prueba: #include <TinyGPS++.h>

//////////////// CONFIG //////////////////
#define GPS_RX_PIN   16     // ← TX del GPS
#define GPS_TX_PIN   17     // → RX del GPS
#define LED_PIN       2     // LED on-board
#define SHOW_NMEA     0     // 1 = mostrar tramas NMEA crudas ($GPRMC, etc.)
//////////////////////////////////////////

TinyGPSPlus gps;
uint32_t gpsBaud = 9600;    // se ajusta automáticamente

// Detecta si hay NMEA a cierto baud
bool detectBaud(uint32_t baud, uint32_t ms = 2000) {
  Serial2.begin(baud, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  uint32_t start = millis();
  bool seen = false;
  while (millis() - start < ms) {
    if (Serial2.available()) {
      char c = Serial2.read();
#if SHOW_NMEA
      Serial.write(c);
#endif
      if (c == '$') seen = true;            // inicio de trama NMEA
      gps.encode(c);
    }
  }
  return seen;
}

void print2(uint8_t v){ if(v<10) Serial.print('0'); Serial.print(v); }

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(300);
  Serial.println(F("\n[BOOT] ESP32 + GPS"));
  Serial.println(F("[INFO] Probando baud 9600 y 4800 automaticamente..."));

  // Autodetección 9600 -> 4800
  if (detectBaud(9600)) { gpsBaud = 9600; Serial.println(F("[GPS] Detectado 9600.")); }
  else if (detectBaud(4800)) { gpsBaud = 4800; Serial.println(F("[GPS] Detectado 4800.")); }
  else {
    // Si no detectó, deja 9600 por defecto
    Serial.println(F("[GPS] No se detectaron tramas; usando 9600 por defecto."));
    Serial2.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  }

  Serial.println(F("[INFO] Esperando fix (prueba cerca de una ventana)."));
}

void loop() {
  // Latido para saber que el loop está vivo
  static uint32_t tBeat=0;
  if (millis() - tBeat > 1000) { tBeat = millis(); digitalWrite(LED_PIN, !digitalRead(LED_PIN)); }

  // Leer y procesar NMEA
  while (Serial2.available()) {
    char c = Serial2.read();
#if SHOW_NMEA
    Serial.write(c);
#endif
    gps.encode(c);
  }

  // Cuando haya nueva localización, mostramos todo
  if (gps.location.isUpdated()) {
    Serial.print(F("Lat: ")); Serial.print(gps.location.lat(), 6);
    Serial.print(F("  Lon: ")); Serial.print(gps.location.lng(), 6);

    Serial.print(F("  Sats: "));
    if (gps.satellites.isValid()) Serial.print(gps.satellites.value()); else Serial.print('-');

    Serial.print(F("  HDOP: "));
    if (gps.hdop.isValid()) Serial.print(gps.hdop.hdop()); else Serial.print('-');

    Serial.print(F("  Alt(m): "));
    if (gps.altitude.isValid()) Serial.print(gps.altitude.meters(), 1); else Serial.print('-');

    Serial.print(F("  Vel(km/h): "));
    if (gps.speed.isValid()) Serial.print(gps.speed.kmph(), 2); else Serial.print('-');

    if (gps.date.isValid() && gps.time.isValid()) {
      Serial.print(F("  UTC "));
      print2(gps.time.hour()); Serial.print(':'); print2(gps.time.minute()); Serial.print(':'); print2(gps.time.second());
      Serial.print(F("  ")); print2(gps.date.day()); Serial.print('/'); print2(gps.date.month()); Serial.print('/'); Serial.print(gps.date.year());
    }
    Serial.println();
  }

  // Diagnóstico sencillo: ¿siguen llegando bytes?
  static uint32_t tDiag=0; static unsigned long lastChars=0;
  if (millis() - tDiag > 4000) {
    tDiag = millis();
    if (gps.charsProcessed() == lastChars) {
      Serial.println(F("[ALERTA] No llegan datos del GPS. Revisa TX->16, RX->17, GND/VCC y el baud."));
    }
    lastChars = gps.charsProcessed();
  }
}
