#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Instantiate TinyGPS++ object
TinyGPSPlus gps;

// Use Serial1 for GPS on Arduino Mega
HardwareSerial GPS_Serial(1);

void setup() {
  // Start the serial communication for debugging
  Serial.begin(115200);
  
  // Start the serial communication with GPS module
  GPS_Serial.begin(38400, SERIAL_8N1, D3, D2);

  Serial.println("GPS Module Test");
}

void loop() {
  // Check if data is available from the GPS module
  while (GPS_Serial.available() > 0) {
    gps.encode(GPS_Serial.read());
  }

  // If location is updated, print it
  if (gps.location.isUpdated()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    float speed = gps.speed.kmph();
    
    Serial.print("Latitude: ");
    Serial.println(latitude, 6);
    
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" km/h");
    
    Serial.println();
  }
}
