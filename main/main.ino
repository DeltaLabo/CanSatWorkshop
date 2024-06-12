#include <HardwareSerial.h>
#include <Arduino.h>
#include <string.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_INA219.h"
#include "Adafruit_BMP280.h"
#include "Adafruit_MPU6050.h"
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
TinyGPS gps;
HardwareSerial GPS_Serial(1);
// Variables for complementary filter
float pitch = 0.0;
float roll = 0.0;
float yaw = 0.0;
unsigned long lastTime = 0;
/******* End Position and Orientation Global Variables *******/

/******* Begin Test Functions *******/
// Only using z-axis functions
float readSpeed() {return 1.0;}
float readRotx() {return 2.0;}
float readAz() {return 3.0;}
float readLat() {return 4.0;}
float readYaw() {return 5.0;}
float readAltitude() {return 6.0;}
float readPressure() {return 7.0;}
float readTemperature() {return 8.0;}
float readVoltage() {return 9.0;}
float readCurrent() {return 10.0;}
/******* End Test Functions *******/

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
  Serial.print(altitude); /* Adjusted to local forecast! */
  Serial.println(" m");

  return altitude;
}
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
/******* End Sensor Functions *******/

/******* Begin Position and Orientation Functions *******/
// MPU Functions
float readRotx(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw gyroscope values to degrees per second
  float gx_deg = gx / 65.5;
  Serial.print("Rotation X: ");
  Serial.print(gx_deg);
  Serial.println(" deg/s");

  return gx_deg
}
float readRoty(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw gyroscope values to degrees per second
  float gy_deg = gy / 65.5;
  Serial.print("Rotation Y: ");
  Serial.print(gy_deg);
  Serial.println(" deg/s");

  return gy_deg
}
float readRotz(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw gyroscope values to degrees per second
  float gz_deg = gz / 65.5;
  Serial.print("Rotation z: ");
  Serial.print(gz_deg);
  Serial.println(" deg/s");

  return gz_deg
}
float readAx(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw values to 'g' and then to 'm/s²'
  float ax_ms2 = (ax / 4096.0) * 9.80665;
  Serial.print("Acceleration X: ");
  Serial.print(ax_ms2);
  Serial.println(" m/s^2");

  return ax_ms2;
}
float readAy(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw values to 'g' and then to 'm/s²'
  float ay_ms2 = (ay / 4096.0) * 9.80665;
  Serial.print("Acceleration Y: ");
  Serial.print(ay_ms2);
  Serial.println(" m/s^2");

  return ay_ms2;
}
float readAz(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw values to 'g' and then to 'm/s²'
  float az_ms2 = (ay / 4096.0) * 9.80665;
  Serial.print("Acceleration Z: ");
  Serial.print(az_ms2);
  Serial.println(" m/s^2");

  return az_ms2;
}
float readPitch(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw accelerometer values to 'g' and then to 'm/s²'
  float ax_ms2 = (ax / 4096.0) * 9.80665;
  float ay_ms2 = (ay / 4096.0) * 9.80665;
  float az_ms2 = (az / 4096.0) * 9.80665;
  // Convert raw gyroscope values to degrees per second
  float gx_deg = gx / 65.5;
  float gy_deg = gy / 65.5;
  float gz_deg = gz / 65.5;

  // Calculate delta time
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  // Calculate pitch from accelerometer data
  float accel_pitch = atan2(ay_ms2, sqrt(ax_ms2 * ax_ms2 + az_ms2 * az_ms2)) * 180 / PI;

  // Complementary filter to combine accelerometer and gyroscope data
  pitch = 0.98 * (pitch + gx_deg * dt) + 0.02 * accel_pitch;  
  Serial.print("Pitch: ");
  Serial.print(pitch);

  return pitch;
}
float readRoll(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw accelerometer values to 'g' and then to 'm/s²'
  float ax_ms2 = (ax / 4096.0) * 9.80665;
  float ay_ms2 = (ay / 4096.0) * 9.80665;
  float az_ms2 = (az / 4096.0) * 9.80665;
  // Convert raw gyroscope values to degrees per second
  float gx_deg = gx / 65.5;
  float gy_deg = gy / 65.5;
  float gz_deg = gz / 65.5;

  // Calculate delta time
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  // Calculate pitch and roll from accelerometer data
  float accel_roll = atan2(-ax_ms2, az_ms2) * 180 / PI;

  // Complementary filter to combine accelerometer and gyroscope data
  roll = 0.98 * (roll + gy_deg * dt) + 0.02 * accel_roll;
  Serial.print(" Roll: ");
  Serial.print(roll);

  return roll;
}
float readYaw(){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw accelerometer values to 'g' and then to 'm/s²'
  float ax_ms2 = (ax / 4096.0) * 9.80665;
  float ay_ms2 = (ay / 4096.0) * 9.80665;
  float az_ms2 = (az / 4096.0) * 9.80665;
  // Convert raw gyroscope values to degrees per second
  float gx_deg = gx / 65.5;
  float gy_deg = gy / 65.5;
  float gz_deg = gz / 65.5;

  // Calculate delta time
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  // Gyroscope integration for yaw (without magnetometer correction)
  yaw += gz_deg * dt;
  Serial.print(" Yaw: ");
  Serial.println(yaw);

  return yaw;
}
// GPS Functions
float readLat(){
  while (GPS_Serial.available() > 0) {
    gps.encode(GPS_Serial.read());
  }

  if (gps.location.isUpdated()) {
    float latitude = gps.location.lat();
    Serial.print("GPS Latitude: ");
    Serial.println(latitude, 6);
  } else {
    Serial.println("Waiting for GPS signal...");
  }
  return latitude;
}
float readLong(){
  while (GPS_Serial.available() > 0) {
    gps.encode(GPS_Serial.read());
  }

  if (gps.location.isUpdated()) {
    float longitude = gps.location.lng();
    Serial.print("GPS Longitude: ");
    Serial.println(longitude, 6);
  } else {
    Serial.println("Waiting for GPS signal...");
  }
  return longitude;
}
float readSpeed(){
  while (GPS_Serial.available() > 0) {
    gps.encode(GPS_Serial.read());
  }

  if (gps.location.isUpdated()) {
    float speed_kmph = gps.speed.kmph();
    Serial.print("GPS Speed: ");
    Serial.print(speed_kmph);
    Serial.println(" km/h");
  } else {
    Serial.println("Waiting for GPS signal...");
  }
  return speed_kmph;
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
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  }
  // Initialize INA219 sensor (voltage and current sensor)
  if (!ina219.begin()) {
    Serial.println("Could not find a valid INA219 sensor, check wiring!");
  }
  /******* End Sensor Setup *******/

  /******* Begin Position and Orientation Setup *******/
  // Initialize MPU6050 (Orientation sensor)
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
  }
  // MPU parameters
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  // Initialize GPS
  GPS_Serial.begin(9600, SERIAL_8N1, 7, 6);
  Serial.println("GPS Serial started");

  lastTime = millis();
  /******* End Position and Orientation Setup *******/
}

// The loop function should only be used for LoRa comms polling
void loop() {
  // If any data was received via LoRa
  if (LoRa.available() > 0) {
    // Read from LoRa serial port
    String RXString = LoRa.readString();
    Serial.println("[INFO]: LoRa data received");
    Serial.print(RXString);

    // If the incoming data contains a valid request from the ground station
    if (RXString.indexOf(TXRequest) != -1) {
      Serial.println("[INFO]: Valid request received");
      // Respond to the request
      PackagePayload();
      SendPayload();
      Serial.println("[INFO]: Payload sent");
    }
  }
}
