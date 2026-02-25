// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>

Adafruit_MPU6050 mpu;
// Variables for Orientation calculations
float pitch = 0.0;
float roll = 0.0;
float yaw = 0.0;
// Used to calculate time difference between IMU readings
uint32_t lastOrientationUPdateTime = 0;
// Used to time IMU updates
uint32_t lastIMUUPdateTime = 0;
float deltaTime;
uint32_t lastTime = 0;

// MPU Functions
float readRotx(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Return gyro reading for x axis
  return g.gyro.x;
}

float readRoty(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Return gyro reading for y axis
  return g.gyro.y;
}

float readRotz(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Return gyro reading for z axis
  return g.gyro.z;
}

float readAx(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Return accel reading for x axis
  return a.acceleration.x;
}

float readAy(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Return accel reading for y axis
  return a.acceleration.y;
}

float readAz(){
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Return accel reading for z axis
  return a.acceleration.z;
}

float readPitch() {
  return pitch;
}

float readRoll() {
  return roll;
}

float readYaw() {
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

void setup(void) {
  Serial.begin(115200);

  // Initialize MPU6050 (Orientation sensor)
  mpu.begin();
  // Set the MPU to measure up to 8 times gravity
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // Set the gyro range to 500 degrees
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // Set the digital low-pass filter bandwidth to 21 Hz
  // for the accelerometer and gyro to reduce high-frequency noise
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("Adafruit MPU6050 test!");

  // Used to calculate time difference between IMU readings
  lastOrientationUPdateTime = millis();
  // Used to time IMU updates
  lastIMUUPdateTime = millis();
  lastTime = millis();

  delay(100);
}

void loop() {
  if ((millis() - lastIMUUPdateTime) >= 100) {
    updateOrientation();
    lastIMUUPdateTime = millis();
  }

  if ((millis() - lastTime) >= 500) {
    /* Print out the values */
    Serial.print("Acceleration X: ");
    Serial.print(readAx());
    Serial.print(", Y: ");
    Serial.print(readAy());
    Serial.print(", Z: ");
    Serial.print(readAz());
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(readRotx());
    Serial.print(", Y: ");
    Serial.print(readRoty());
    Serial.print(", Z: ");
    Serial.print(readRotz());
    Serial.println(" rad/s");

    Serial.print("Yaw: ");
    Serial.print(readYaw());
    Serial.print(", Pitch: ");
    Serial.print(readPitch());
    Serial.print(", Roll: ");
    Serial.print(readRoll());
    Serial.println(" deg");

    lastTime = millis();
  }
}