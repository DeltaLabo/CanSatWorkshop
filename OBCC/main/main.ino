#include <HardwareSerial.h>
#include <Arduino.h>
#include <string.h>
#include <TinyGPS++.h>
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_INA219.h"
#include "Adafruit_BME280.h"
#include <ICM20948_WE.h>
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

// deployment_status occupies byte 48: the first byte that was previously
// reserved after the ten 4-byte telemetry floats (payload bytes 8..47).
// This preserves LORA_PAYLOAD_SIZE == 100 and the existing footer at 96..99.
const uint8_t DEPLOYMENT_STATUS_PAYLOAD_OFFSET = 48;

enum DeploymentStatus : uint8_t {
  DEPLOYMENT_NOT_COMMANDED = 0,
  DEPLOYMENT_INHIBITED_STANDBY = 1,
  DEPLOYMENT_COMMAND_SENT = 2,
  DEPLOYMENT_OPEN_IN_PROGRESS = 3,
  DEPLOYMENT_OPEN_CONFIRMED = 4,
  DEPLOYMENT_NO_OPEN_CONFIRMED = 5,
  DEPLOYMENT_TIMEOUT = 6,
  DEPLOYMENT_JAM_DETECTED = 7,
  DEPLOYMENT_PDM_FAULT = 8,
  DEPLOYMENT_UNKNOWN = 9
};

// Current firmware has no accepted PDM open-command path or PDM/observer
// confirmation API wired into OBCC. Keep the telemetry safe by defaulting to
// NOT_COMMANDED until such a command is accepted; if a future command path is
// added without confirmation evidence, report UNKNOWN/fault instead of success.
bool deploymentCommandAccepted = false;
/******* End Comms Global Variables *******/

/******* Begin Sensor Global Variables *******/
Adafruit_INA219 ina219;
Adafruit_BME280 bme;
/******* End Sensor Global Variables *******/

/******* Begin Position and Orientation Global Variables *******/
#define ICM20948_ADDR 0x68
const float STANDARD_GRAVITY_MPS2 = 9.80665f;
const float DEG_TO_RAD_FACTOR = PI / 180.0f;
ICM20948_WE imu = ICM20948_WE(ICM20948_ADDR);
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
DeploymentStatus readDeploymentStatusFromPolicyOrFeedback() {
  // No-false-success rule: COMMAND_SENT is never deployed/success. Only a
  // future PDM feedback or independent actuator/current/position observer may
  // return DEPLOYMENT_OPEN_CONFIRMED.
  if (!deploymentCommandAccepted) {
    return DEPLOYMENT_NOT_COMMANDED;
  }

  return DEPLOYMENT_UNKNOWN;
}

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

  // Parachute deployment status is a one-byte enum at payload byte 48.
  // It uses previously reserved space and does not alter the 100-byte frame.
  // Only DEPLOYMENT_OPEN_CONFIRMED is deployed/success; command sent is not.
  payload[DEPLOYMENT_STATUS_PAYLOAD_OFFSET] = (byte)readDeploymentStatusFromPolicyOrFeedback();
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
// BME280 Functions
float readTemperature(){
  // Read Temperature
  float temperature = 0;
  temperature = bme.readTemperature();
  Serial.print("[DATA]: Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  return temperature;
}
float readPressure(){
  // Read pressure
  float pressure = 0;
  pressure = bme.readPressure() / 1000;
  Serial.print("[DATA]: Pressure = ");
  Serial.print(pressure);
  Serial.println(" MPa");

  return pressure;
}
float readAltitude(){
  // Calculate altitude
  float altitude = 0;
  altitude = bme.readAltitude(1013.25);
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
// ICM20948 Functions
void readIMU(xyzFloat& accelerationG, xyzFloat& gyroDps) {
  imu.readSensor();
  imu.getGValues(&accelerationG);
  imu.getGyrValues(&gyroDps);
}

float readRotx(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  float rotation = gyroDps.x * DEG_TO_RAD_FACTOR;

  Serial.print("[DATA]: Rotation (x): ");
  Serial.print(rotation);
  Serial.println(" rad/s");
  // Return gyro reading for x axis
  return rotation;
}

float readRoty(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  float rotation = gyroDps.y * DEG_TO_RAD_FACTOR;

  Serial.print("[DATA]: Rotation (y): ");
  Serial.print(rotation);
  Serial.println(" rad/s");
  // Return gyro reading for y axis
  return rotation;
}

float readRotz(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  float rotation = gyroDps.z * DEG_TO_RAD_FACTOR;

  Serial.print("[DATA]: Rotation (z): ");
  Serial.print(rotation);
  Serial.println(" rad/s");
  // Return gyro reading for z axis
  return rotation;
}

float readAx(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  float acceleration = accelerationG.x * STANDARD_GRAVITY_MPS2;

  Serial.print("[DATA]: Acceleration (x): ");
  Serial.print(acceleration);
  Serial.println(" m/s2");
  // Return accel reading for x axis
  return acceleration;
}

float readAy(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  float acceleration = accelerationG.y * STANDARD_GRAVITY_MPS2;

  Serial.print("[DATA]: Acceleration (y): ");
  Serial.print(acceleration);
  Serial.println(" m/s2");
  // Return accel reading for y axis
  return acceleration;
}

float readAz(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  float acceleration = accelerationG.z * STANDARD_GRAVITY_MPS2;

  Serial.print("[DATA]: Acceleration (z): ");
  Serial.print(acceleration);
  Serial.println(" m/s2");
  // Return accel reading for z axis
  return acceleration;
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
  // Get a new sensor sample
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);

  // Calculate the time difference
  unsigned long currentTime = millis();
  deltaTime = (currentTime - lastOrientationUPdateTime) / 1000.0;
  lastOrientationUPdateTime = currentTime;

  // Calculate roll and pitch from accelerometer data
  roll = atan2(accelerationG.y, accelerationG.z) * 180 / PI;
  pitch = atan2(-accelerationG.x, sqrt(accelerationG.y * accelerationG.y + accelerationG.z * accelerationG.z)) * 180 / PI;

  // Integrate gyroscope data to estimate yaw in degrees
  yaw += gyroDps.z * deltaTime;
}

// GPS Functions
float readLat(){
  // Initialize to example value
  float latitude = -1.0;
  // If the GPS has updated its data via GPS, get the latitude
  if (gps.location.isUpdated()) latitude = gps.location.lat();

  Serial.print("[DATA]: Latitude: ");
  Serial.print(latitude);
  Serial.println(" deg");
  return latitude;
}

float readLong(){
  // Initialize to example value
  float longitude = -1.0;
  // If the GPS has updated its data via GPS, get the latitude
  if (gps.location.isUpdated()) longitude = gps.location.lng();

  Serial.print("[DATA]: Longitude: ");
  Serial.print(longitude);
  Serial.println(" deg");
  return longitude;
}

float readSpeed(){
  // Initialize to example value
  float speed = -1.0;
  // If the GPS has updated its data via GPS, get the latitude
  if (gps.location.isUpdated()) speed = gps.speed.kmph();

  Serial.print("[DATA]: Speed: ");
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
  memset(payload, 0, sizeof(payload));
  // Header
  for (int i=0;i<4;i++) payload[i] = LORA_HEADER[i];
  // Sender ID
  for (int i=0;i<2;i++) payload[i+4] = CANSAT_LORA_ID[i];
  // Receiver ID
  for (int i=0;i<2;i++) payload[i+6] = GS_LORA_ID[i];
  // Byte 48 is deployment_status; bytes 49..95 remain reserved.
  payload[DEPLOYMENT_STATUS_PAYLOAD_OFFSET] = (byte)DEPLOYMENT_NOT_COMMANDED;
  for (int i=0;i<47;i++) payload[i+49] = 0;
  // Footer
  for (int i=0;i<4;i++) payload[i+96] = LORA_FOOTER[i];

  // Serial port for logging
  Serial.begin(115200);
  /******* End Comms Setup *******/

  /******* Begin Sensor Setup *******/
  Wire.begin();

  // Initialize BME280 (temperature and pressure sensor)
  if (!bme.begin(0x76)) {
    Serial.println("[ERROR]: Could not find a valid BME280 sensor, check wiring");
  }
  // Initialize INA219 sensor (voltage and current sensor)
  if (!ina219.begin()) {
    Serial.println("[ERROR]: Could not find a valid INA219 sensor, check wiring");
  }
  /******* End Sensor Setup *******/

  /******* Begin Position and Orientation Setup *******/
  // Initialize ICM20948 (orientation sensor)
  if(!imu.init()) {
    Serial.println("[ERROR]: Could not find a valid ICM20948 sensor, check wiring");
  } else {
    // Use the same ICM20948_WE configuration pattern used by ADS sketches.
    imu.setAccRange(ICM20948_ACC_RANGE_2G);
    imu.setAccDLPF(ICM20948_DLPF_6);
    imu.setGyrRange(ICM20948_GYRO_RANGE_250);
    imu.setGyrDLPF(ICM20948_DLPF_6);
    imu.setTempDLPF(ICM20948_DLPF_6);
  }

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
