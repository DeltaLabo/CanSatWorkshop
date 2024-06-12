#include "Adafruit_Sensor.h"
#include "Adafruit_INA219.h"

Adafruit_INA219 ina219;

// INA219 Functions
float readVoltage(){
  float busvoltage = 0;
  busvoltage = ina219.getBusVoltage_V();
  Serial.print("Bus Voltage: ");
  Serial.print(busvoltage);
  Serial.println(" V");

  return busvoltage;
}
float readCurrent(){
  float current_mA = 0;
  current_mA = ina219.getCurrent_mA();
  Serial.print("Current: ");
  Serial.print(current_mA);
  Serial.println(" mA");

  return current_mA;
}

void setup() {
  ina219.begin();
  Serial.begin(115200);
}

void loop() {
  readVoltage();
  readCurrent();
  delay(500);
}