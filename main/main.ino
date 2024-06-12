#include <HardwareSerial.h>
#include <Arduino.h>
#include <string.h>
#include <TinyGPS++.h>
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_INA219.h"
#include "Adafruit_BMP280.h"
#include "Adafruit_MPU6050.h"
#include <math.h>
#include "settings.h"
#include "pins.h"

/******* Begin Comms Global Variables *******/
// Serial port to communicate with the LoRa radio
HardwareSerial LoRa(0);

// Used to convert a float as a 4-byte array
union {
  float value;
  byte bytes[4];
} floatUnion;

// LoRa payload with a size of 100 bytes
byte payload[LORA_PAYLOAD_SIZE];
/******* End Comms Global Variables *******/

/******* Begin Sensor Global Variables *******/
Adafruit_INA219 ina219;
Adafruit_BMP280 bmp;
/******* End Sensor Global Variables *******/

/******* Begin Position and Orientation Global Variables *******/
Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
HardwareSerial GPS_Serial(1);
// Variables for Orientation calculations
float pitch = 0.0;
float roll = 0.0;
float yaw = 0.0;
// Used to calculate time difference between IMU readings
uint32_t lastOrientationUPdateTime = 0;
float deltaTime;
// Used to time IMU updates
uint32_t lastIMUUPdateTime = 0;
/******* End Position and Orientation Global Variables *******/

/******* Begin Comms Functions *******/
// Read all variables and package them into a LoRa payload
void PackagePayload() {
  /*******
   * Example:
   * // Read the variable
   * floatUnion.value = readVariable(); // The function must return a float
   * // Insert the variable into the payload, byte by byte
   * // Note that the ESP32 is little-endian
   * // varSizeinBytes == 4 for a float variable
   * for (int i=0;i<varSizeinBytes;i++) payload[i+startByte] = floatUnion.bytes[i];
  *******/ 
  // Only using z-axis values
  floatUnion.value = readSpeed();
  for (int i=0;i<4;i++) payload[i+8] = floatUnion.bytes[i];

  floatUnion.value = readRotz(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+12] = floatUnion.bytes[i];

  floatUnion.value = readAz(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+16] = floatUnion.bytes[i];

  floatUnion.value = readLat(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+20] = floatUnion.bytes[i];

  floatUnion.value = readYaw(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+24] = floatUnion.bytes[i];

  floatUnion.value = readAltitude(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+28] = floatUnion.bytes[i];

  floatUnion.value = readPressure(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+32] = floatUnion.bytes[i];

  floatUnion.value = readTemperature(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+36] = floatUnion.bytes[i];

  floatUnion.value = readVoltage(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+40] = floatUnion.bytes[i];

  floatUnion.value = readCurrent(); // Replace with actual function, which must return a float
  for (int i=0;i<4;i++) payload[i+44] = floatUnion.bytes[i];
}

// Sends the populated payload via LoRa
void SendPayload() {
  // Write AT command for LoRa send, targeting all radio addresses (0), with
  // a payload size of 100 bytes
  // Note that radio addresses are not a LoRa standard but specific to the
  // transceiver being used, thus they're not implemented
  LoRa.print("AT+SEND=0,100,");
  // Write payload as a byte array
  LoRa.write(payload, LORA_PAYLOAD_SIZE);
  // Write CRLF to terminate the command, as required by the transceiver
  LoRa.println();
}
/******* End Comms Functions *******/

/******* Begin Sensor Functions *******/
// BMP280 Functions
float readTemperature(){
  // Read Temperature
  float temperature = 0;
  temperature = bmp.readTemperature();
  Serial.print("[DATA]: Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  return temperature;
}
float readPressure(){
  // Read pressure
  float pressure = 0;
  pressure = bmp.readPressure() / 1000;
  Serial.print("[DATA]: Pressure = ");
  Serial.print(pressure);
  Serial.println(" MPa");

  return pressure;
}
float readAltitude(){
  // Calculate altitude
  float altitude = 0;
  altitude = bmp.readAltitude(1013.25);
  Serial.print("[DATA]: Approx. altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  return altitude;
}
// INA219 Functions
float readVoltage(){
  float busvoltage = 0;
  busvoltage = ina219.getBusVoltage_V();
  Serial.print("[DATA]: Bus Voltage: ");
  Serial.print(busvoltage);
  Serial.println(" V");

  return busvoltage;
}
float readCurrent(){
  float current_mA = 0;
  current_mA = ina219.getCurrent_mA();
  Serial.print("[DATA]: Current: ");
  Serial.print(current_mA);
  Serial.println(" mA");

  return current_mA;
}

/******* End Sensor Functions *******/

/******* Begin Position and Orientation Functions *******/
// MPU Functions
float readRotx(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("[DATA]: Rotation (x): ");
  Serial.print(g.gyro.x);
  Serial.println(" rad/s");
  // Return gyro reading for x axis
  return g.gyro.x;
}

float readRoty(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("[DATA]: Rotation (y): ");
  Serial.print(g.gyro.y);
  Serial.println(" rad/s");
  // Return gyro reading for y axis
  return g.gyro.y;
}

float readRotz(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("[DATA]: Rotation (z): ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
  // Return gyro reading for z axis
  return g.gyro.z;
}

float readAx(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("[DATA]: Acceleration (x): ");
  Serial.print(a.acceleration.x);
  Serial.println(" m/s2");
  // Return accel reading for x axis
  return a.acceleration.x;
}

float readAy(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("[DATA]: Acceleration (y): ");
  Serial.print(a.acceleration.y);
  Serial.println(" m/s2");
  // Return accel reading for y axis
  return a.acceleration.y;
}

float readAz(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("[DATA]: Acceleration (z): ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s2");
  // Return accel reading for z axis
  return a.acceleration.z;
}

float readPitch() {
  Serial.print("[DATA]: Pitch: ");
  Serial.print(pitch);
  Serial.println(" deg");
  return pitch;
}

float readRoll() {
  Serial.print("[DATA]: Roll: ");
  Serial.print(roll);
  Serial.println(" deg");
  return roll;
}

float readYaw() {
  Serial.print("[DATA]: Yaw ");
  Serial.print(yaw);
  Serial.println(" deg");
  return yaw;
}

void updateOrientation() {
  // Get a new sensor event
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate the time difference
  unsigned long currentTime = millis();
  deltaTime = (currentTime - lastOrientationUPdateTime) / 1000.0;
  lastOrientationUPdateTime = currentTime;

  // Calculate roll and pitch from accelerometer data
  roll = atan2(a.acceleration.y, a.acceleration.z) * 180 / PI;
  pitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180 / PI;

  // Integrate gyroscope data to estimate yaw
  yaw += g.gyro.z * deltaTime;
}

// GPS Functions
float readLat(){
  // Initialize to example value
  float latitude = -1.0;
  // If the GPS has updated its data via GPS, get the latitude
  if (gps.location.isUpdated()) latitude = gps.location.lat();

  Serial.print("Latitude: ");
  Serial.print(latitude);
  Serial.println(" deg");
  return latitude;
}

float readLong(){
  // Initialize to example value
  float longitude = -1.0;
  // If the GPS has updated its data via GPS, get the latitude
  if (gps.location.isUpdated()) longitude = gps.location.lng();

  Serial.print("Longitude: ");
  Serial.print(longitude);
  Serial.println(" deg");
  return longitude;
}

float readSpeed(){
  // Initialize to example value
  float speed = -1.0;
  // If the GPS has updated its data via GPS, get the latitude
  if (gps.location.isUpdated()) speed = gps.speed.kmph();

  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.println(" m/s");
  return speed;
}
/******* End Position and Orientation Functions *******/

void setup() {
  /******* Begin Comms Setup *******/
  // 8 bits, no parity, 1 stop bit
  LoRa.begin(115200, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
  // Set buffer size to 100 bytes to transmit payload
  LoRa.setTxBufferSize(LORA_RX_BUFFER_SIZE);
  // Set UART RX timeout to 1 ms
  // Since the baud rate is 115200, more than 1 ms without receiving data
  // means that the transmission has ended 
  LoRa.setTimeout(1);

  // Set LoRa frequency band
  // The LORA_BAND variable is in MHz
  LoRa.println("AT+BAND=" + LORA_BAND + "000000");

  // Set Spreading Factor, Bandwidth, and Coding Rate
  // The ",0" at the end sets the radio to not send any network ID data as a preamble,
  // since sender and receiver identification will be implemented within the payload
  LoRa.println("AT+PARAMETER=" + LORA_SF + "," + LORA_BANDWIDTH + "," + LORA_CODING_RATE + ",0");

  // Populate payload with its default values
  // Header
  for (int i=0;i<4;i++) payload[i] = LORA_HEADER[i];
  // Sender ID
  for (int i=0;i<2;i++) payload[i+4] = CANSAT_LORA_ID[i];
  // Receiver ID
  for (int i=0;i<2;i++) payload[i+6] = GS_LORA_ID[i];
  // Space reserved for future development
  for (int i=0;i<48;i++) payload[i+48] = 0;
  // Footer
  for (int i=0;i<4;i++) payload[i+96] = LORA_FOOTER[i];

  // Serial port for logging
  Serial.begin(115200);
  /******* End Comms Setup *******/

  /******* Begin Sensor Setup *******/
  // Initialize BMP280 (temperature and pressure sensor)
  if (!bmp.begin(0x76)) {
    Serial.println("[ERROR]: Could not find a valid BMP280 sensor, check wiring");
  }
  // Initialize INA219 sensor (voltage and current sensor)
  if (!ina219.begin()) {
    Serial.println("[ERROR]: Could not find a valid INA219 sensor, check wiring");
  }
  /******* End Sensor Setup *******/

  /******* Begin Position and Orientation Setup *******/
  // Initialize MPU6050 (Orientation sensor)
  if(!mpu.begin()) Serial.println("[ERROR]: Could not find a valid MPU6050 sensor, check wiring");
  // Set the MPU to measure up to 8 times gravity
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // Set the gyro range to 500 degrees
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // Set the digital low-pass filter bandwidth to 21 Hz
  // for the accelerometer and gyro to reduce high-frequency noise
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Initialize GPS
  GPS_Serial.begin(38400, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  // Update IMU update time counter
  lastOrientationUPdateTime = millis();
  lastIMUUPdateTime = millis();
  /******* End Position and Orientation Setup *******/
}

void loop() {
  // If any data was received via LoRa
  if (LoRa.available() > 0) {
    // Read from LoRa serial port
    String RXString = LoRa.readString();
    Serial.println("[INFO]: LoRa data received");

    // If the incoming data contains a valid request from the ground station
    if (RXString.indexOf(TXRequest) != -1) {
      Serial.println("[INFO]: Valid LoRa TX request received");
      // Respond to the request
      PackagePayload();
      SendPayload();
      Serial.println("[INFO]: LoRa payload sent");
    }
  }

  // Check if data is available from the GPS module
  while (GPS_Serial.available() > 0) {
    // If data is available, read it and pass it to the TinyGPS++ library for parsing
    gps.encode(GPS_Serial.read());
  }

  // Update IMU every 100 ms
  if (millis() - lastIMUUPdateTime >= 100) {
    updateOrientation();
    // Reset time counter
    lastIMUUPdateTime = millis();
  }
}
