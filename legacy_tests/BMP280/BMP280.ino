#include "Adafruit_Sensor.h"
#include "Adafruit_INA219.h"
#include "Adafruit_BMP280.h"

Adafruit_BMP280 bmp;

// BMP280 Functions
float readTemperature(){
  // Read Temperature
  float temperature = 0;
  temperature = bmp.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  return temperature;
}
float readPressure(){
  // Read pressure
  float pressure = 0;
  pressure = bmp.readPressure() / 1000;
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" MPa");

  return pressure;
}
float readAltitude(){
  // Calculate altitude
  float altitude = 0;
  altitude = bmp.readAltitude(1013.25);
  Serial.print("Approx altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  return altitude;
}

void setup() {
  // Initialize BMP280 (temperature and pressure sensor)
  bmp.begin(0x76);
  Serial.begin(9600);
}

void loop() {
  readAltitude();
  readPressure();
  readTemperature();
  delay(500); 
}