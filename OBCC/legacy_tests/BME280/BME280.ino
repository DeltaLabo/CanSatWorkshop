#include "Adafruit_Sensor.h"
#include "Adafruit_INA219.h"
#include "Adafruit_BME280.h"

Adafruit_BME280 bme;

// BME280 Functions
float readTemperature(){
  // Read Temperature
  float temperature = 0;
  temperature = bme.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  return temperature;
}
float readPressure(){
  // Read pressure
  float pressure = 0;
  pressure = bme.readPressure() / 1000;
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" MPa");

  return pressure;
}
float readAltitude(){
  // Calculate altitude
  float altitude = 0;
  altitude = bme.readAltitude(1013.25);
  Serial.print("Approx altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  return altitude;
}

void setup() {
  // Initialize BME280 (temperature and pressure sensor)
  bme.begin(0x76);
  Serial.begin(9600);
}

void loop() {
  readAltitude();
  readPressure();
  readTemperature();
  delay(500); 
}