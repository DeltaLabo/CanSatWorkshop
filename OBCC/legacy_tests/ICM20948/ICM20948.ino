// Basic demo for accelerometer readings from the project ICM20948 IMU

#include <ICM20948_WE.h>
#include <Wire.h>
#include <math.h>

#define ICM20948_ADDR 0x68
#define STANDARD_GRAVITY_MPS2 9.80665f
#define DEG_TO_RAD_FACTOR (PI / 180.0f)

ICM20948_WE imu = ICM20948_WE(ICM20948_ADDR);
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

void readIMU(xyzFloat& accelerationG, xyzFloat& gyroDps) {
  imu.readSensor();
  imu.getGValues(&accelerationG);
  imu.getGyrValues(&gyroDps);
}

// ICM20948 Functions
float readRotx(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  return gyroDps.x * DEG_TO_RAD_FACTOR;
}

float readRoty(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  return gyroDps.y * DEG_TO_RAD_FACTOR;
}

float readRotz(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  return gyroDps.z * DEG_TO_RAD_FACTOR;
}

float readAx(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  return accelerationG.x * STANDARD_GRAVITY_MPS2;
}

float readAy(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  return accelerationG.y * STANDARD_GRAVITY_MPS2;
}

float readAz(){
  xyzFloat accelerationG, gyroDps;
  readIMU(accelerationG, gyroDps);
  return accelerationG.z * STANDARD_GRAVITY_MPS2;
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

void setup(void) {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  // Initialize ICM20948 (orientation sensor)
  if (!imu.init()) {
    Serial.println("ICM20948 does not respond");
  } else {
    imu.setAccRange(ICM20948_ACC_RANGE_2G);
    imu.setAccDLPF(ICM20948_DLPF_6);
    imu.setGyrRange(ICM20948_GYRO_RANGE_250);
    imu.setGyrDLPF(ICM20948_DLPF_6);
    imu.setTempDLPF(ICM20948_DLPF_6);
  }

  Serial.println("ICM20948 test!");

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
