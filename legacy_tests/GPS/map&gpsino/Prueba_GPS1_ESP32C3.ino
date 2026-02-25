#include <TinyGPSPlus.h>   // Si te da error, prueba: #include <TinyGPS++.h>

//////////////////// CONFIG ////////////////////
#define GPS_BAUD     9600   // 9600 suele ser lo estándar (cambia a 4800 si es tu caso)
#define LED_PIN       2     // LED on-board
#define PRINT_NMEA    0     // 1 = mostrar tramas NMEA crudas en Serial; 0 = no
////////////////////////////////////////////////

TinyGPSPlus gps;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);  // Comunicación con PC
  delay(300);
  
  // Inicia Serial1 para el GPS (ajusta pines según tu conexión real)
  Serial1.begin(GPS_BAUD, SERIAL_8N1, 5, 4);  // RX en GPIO 5, TX en GPIO 4

  // Encabezado CSV
  Serial.println("lat,lon,alt_m,time_utc,course_deg");
}

void loop() {
  // Leer NMEA desde el GPS y pasarlo al parser
  while (Serial1.available()) {
    char c = (char)Serial1.read();
#if PRINT_NMEA
    Serial.write(c);  // Opcional, ver tramas NMEA crudas
#endif
    gps.encode(c);
  }

  // Si hay nueva localización, mostramos en CSV
  if (gps.location.isUpdated()) {
    double lat = gps.location.lat();
    double lon = gps.location.lng();
    double alt = gps.altitude.isValid() ? gps.altitude.meters() : 0.0;
    double course = gps.course.isValid() ? gps.course.deg() : 0.0;

    // Tiempo UTC en formato hh:mm:ss
    char timeStr[20];
    if (gps.time.isValid()) {
      sprintf(timeStr, "%02d:%02d:%02d",
              gps.time.hour(), gps.time.minute(), gps.time.second());
    } else {
      sprintf(timeStr, "--:--:--");
    }

    // Imprimir datos en CSV
    Serial.print(lat, 6); Serial.print(",");
    Serial.print(lon, 6); Serial.print(",");
    Serial.print(alt, 2); Serial.print(",");
    Serial.print(timeStr); Serial.print(",");
    Serial.println(course, 2);
  }

  // Diagnóstico: ¿llegan bytes del GPS?
  static uint32_t tDiag = 0;
  static unsigned long lastChars = 0;
  if (millis() - tDiag > 3000) {
    tDiag = millis();
    if (gps.charsProcessed() == lastChars) {
      Serial.println(F("[ALERTA] No llegan datos del GPS. Revisa conexiones y BAUD."));
    }
    lastChars = gps.charsProcessed();
  }
}
