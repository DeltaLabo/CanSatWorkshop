#include <Wire.h>
#include <math.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// M2 version of the sketch supplied with the dashboard.
// It keeps the same MPU6050 acquisition, gyro calibration and Madgwick code.
// The only protocol change is that the dashboard receives raw calibrated gyro
// rates, allowing it to execute the Kalman prediction from the paper.

const int MPU_ADDR = 0x68;

// BME280: comparte el bus I2C con el MPU sin modificar su configuración.
constexpr uint8_t BME_ADDRESS_PRIMARY = 0x76;
constexpr uint8_t BME_ADDRESS_SECONDARY = 0x77;
constexpr uint32_t BME_PERIOD_MS = 100;
constexpr uint32_t BME_TIMEOUT_US = 5000;

Adafruit_BME280 bme;
bool bmeReady = false;
uint32_t lastBmeUpdate = 0;
float bmeTemperatureC = 0.0f;
float bmePressurePa = 0.0f;
float bmeHumidityPercent = 0.0f;

constexpr uint32_t IMU_PERIOD_US = 2500;       // 400 Hz sensor readout.
constexpr uint32_t TELEMETRY_PERIOD_MS = 50;   // 20 Hz to the dashboard.
constexpr uint32_t I2C_CLOCK_HZ = 100000;      // More tolerant of cable noise.
constexpr uint8_t I2C_READ_ATTEMPTS = 3;
constexpr uint8_t I2C_FAILURES_BEFORE_RECOVERY = 5;
uint32_t lastUpdate = 0;
uint32_t lastTelemetry = 0;

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float gyroBiasX = 0.0f, gyroBiasY = 0.0f, gyroBiasZ = 0.0f;
uint8_t consecutiveI2cFailures = 0;
bool freshSampleSinceTelemetry = false;

// Madgwick is retained from the original sketch. It is not used by the Python
// Kalman roll/pitch filter, but can be kept for future local attitude use.
const float MADGWICK_BETA = 0.1f;
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;


static inline float invSqrt(float x) {
  float halfX = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  return y * (1.5f - halfX * y * y);
}


void madgwick6DOF(float gx, float gy, float gz, float ax, float ay, float az, float dt) {
  float reciprocalNorm;
  float s0, s1, s2, s3;
  float qDot1, qDot2, qDot3, qDot4;
  float twoQ0, twoQ1, twoQ2, twoQ3, fourQ0, fourQ1, fourQ2, eightQ1, eightQ2;
  float q0q0, q1q1, q2q2, q3q3;

  qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
  qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
  qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
  qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

  if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
    reciprocalNorm = invSqrt(ax * ax + ay * ay + az * az);
    ax *= reciprocalNorm;
    ay *= reciprocalNorm;
    az *= reciprocalNorm;

    twoQ0 = 2.0f * q0; twoQ1 = 2.0f * q1;
    twoQ2 = 2.0f * q2; twoQ3 = 2.0f * q3;
    fourQ0 = 4.0f * q0; fourQ1 = 4.0f * q1; fourQ2 = 4.0f * q2;
    eightQ1 = 8.0f * q1; eightQ2 = 8.0f * q2;
    q0q0 = q0 * q0; q1q1 = q1 * q1; q2q2 = q2 * q2; q3q3 = q3 * q3;

    s0 = fourQ0 * q2q2 + twoQ2 * ax + fourQ0 * q1q1 - twoQ1 * ay;
    s1 = fourQ1 * q3q3 - twoQ3 * ax + 4.0f * q0q0 * q1 - twoQ0 * ay
       - fourQ1 + eightQ1 * q1q1 + eightQ1 * q2q2 + fourQ1 * az;
    s2 = 4.0f * q0q0 * q2 + twoQ0 * ax + fourQ2 * q3q3 - twoQ3 * ay
       - fourQ2 + eightQ2 * q1q1 + eightQ2 * q2q2 + fourQ2 * az;
    s3 = 4.0f * q1q1 * q3 - twoQ1 * ax + 4.0f * q2q2 * q3 - twoQ2 * ay;

    reciprocalNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);
    s0 *= reciprocalNorm; s1 *= reciprocalNorm;
    s2 *= reciprocalNorm; s3 *= reciprocalNorm;

    qDot1 -= MADGWICK_BETA * s0;
    qDot2 -= MADGWICK_BETA * s1;
    qDot3 -= MADGWICK_BETA * s2;
    qDot4 -= MADGWICK_BETA * s3;
  }

  q0 += qDot1 * dt; q1 += qDot2 * dt;
  q2 += qDot3 * dt; q3 += qDot4 * dt;

  reciprocalNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
  q0 *= reciprocalNorm; q1 *= reciprocalNorm;
  q2 *= reciprocalNorm; q3 *= reciprocalNorm;
}


void configureWire() {
  Wire.begin();
  Wire.setClock(I2C_CLOCK_HZ);

  // Avoid waiting indefinitely when the I2C bus gets stuck. The conditionals
  // keep the sketch compatible with common AVR and ESP32 Arduino cores.
#if defined(ARDUINO_ARCH_AVR)
  Wire.setWireTimeout(3000, true);
#elif defined(ARDUINO_ARCH_ESP32)
  Wire.setTimeOut(3);
#endif
}


bool configureMpu() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);  // Wake MPU6050.
  if (Wire.endTransmission(true) != 0) return false;

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C);
  Wire.write(0x00);  // Accelerometer: +-2 g.
  if (Wire.endTransmission(true) != 0) return false;

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1B);
  Wire.write(0x00);  // Gyroscope: +-250 degrees/s.
  return Wire.endTransmission(true) == 0;
}


bool readSensorData() {
  // A transient NACK used to skip all telemetry. Retry the read a few times;
  // only report a failed sample after every retry has failed.
  for (uint8_t attempt = 0; attempt < I2C_READ_ATTEMPTS; ++attempt) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    if (Wire.endTransmission(false) != 0) continue;
    if (Wire.requestFrom(MPU_ADDR, 14, true) != 14) continue;

    int16_t rawAccX = Wire.read() << 8 | Wire.read();
    int16_t rawAccY = Wire.read() << 8 | Wire.read();
    int16_t rawAccZ = Wire.read() << 8 | Wire.read();
    Wire.read() << 8 | Wire.read();  // Temperature register; unused here.
    int16_t rawGyroX = Wire.read() << 8 | Wire.read();
    int16_t rawGyroY = Wire.read() << 8 | Wire.read();
    int16_t rawGyroZ = Wire.read() << 8 | Wire.read();

    // Matches +-2g accel and +-250 degrees/s gyro configuration below.
    accX = rawAccX / 16384.0f;
    accY = rawAccY / 16384.0f;
    accZ = rawAccZ / 16384.0f;
    gyroX = rawGyroX / 131.0f;
    gyroY = rawGyroY / 131.0f;
    gyroZ = rawGyroZ / 131.0f;
    return true;
  }
  return false;
}


bool calibrateGyro() {
  const int samples = 500;
  const uint32_t calibrationTimeoutMs = 5000;
  float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
  int count = 0;
  uint32_t calibrationStart = millis();

  // Do not remain in setup forever if the MPU is not connected. If a few
  // samples are available, their average is still a better bias than zero.
  while (count < samples && millis() - calibrationStart < calibrationTimeoutMs) {
    if (readSensorData()) {
      sumX += gyroX;
      sumY += gyroY;
      sumZ += gyroZ;
      count++;
      delay(3);
    }
  }

  if (count == 0) return false;

  gyroBiasX = sumX / count;
  gyroBiasY = sumY / count;
  gyroBiasZ = sumZ / count;
  return count == samples;
}


bool configureBme() {
  bmeReady = bme.begin(BME_ADDRESS_PRIMARY, &Wire);
  if (!bmeReady) {
    bmeReady = bme.begin(BME_ADDRESS_SECONDARY, &Wire);
  }
  if (!bmeReady) return false;

  bme.setSampling(
    Adafruit_BME280::MODE_NORMAL,
    Adafruit_BME280::SAMPLING_X1,
    Adafruit_BME280::SAMPLING_X1,
    Adafruit_BME280::SAMPLING_X1,
    Adafruit_BME280::FILTER_OFF,
    Adafruit_BME280::STANDBY_MS_10
  );
  return true;
}


float truncateToHundredths(float value) {
  return ((long)(value * 100.0f)) / 100.0f;
}


bool readBmeEnvironment() {
  if (!bmeReady) return false;

  uint32_t startedAt = micros();
  const float temperature = bme.readTemperature();
  if (micros() - startedAt > BME_TIMEOUT_US || !isfinite(temperature)) {
    return false;
  }

  startedAt = micros();
  const float pressurePa = bme.readPressure();
  if (micros() - startedAt > BME_TIMEOUT_US || !isfinite(pressurePa)) {
    return false;
  }

  startedAt = micros();
  const float humidity = bme.readHumidity();
  if (micros() - startedAt > BME_TIMEOUT_US || !isfinite(humidity)) {
    return false;
  }

  if (temperature < -40.0f || temperature > 85.0f) return false;
  if (pressurePa < 10000.0f || pressurePa > 120000.0f) return false;
  if (humidity < 0.0f || humidity > 100.0f) return false;

  // Misma precisión del documento: dos decimales. Para presión, el documento
  // conserva 0.01 kPa, equivalente a pasos de 10 Pa en el dashboard.
  bmeTemperatureC = truncateToHundredths(temperature);
  bmePressurePa = truncateToHundredths(pressurePa / 1000.0f) * 1000.0f;
  bmeHumidityPercent = truncateToHundredths(humidity);
  return true;
}


void updateBmeWhenDue() {
  const uint32_t nowMs = millis();
  if (nowMs - lastBmeUpdate < BME_PERIOD_MS) return;
  lastBmeUpdate = nowMs;
  readBmeEnvironment();
}


void sendTelemetry(bool imuSampleIsFresh) {
  uint8_t payload[100];
  memset(payload, 0, sizeof(payload));

  memcpy(&payload[0], "CSWS", 4);
  memcpy(&payload[4], "M2", 2);  // M2 tells Python to expect raw gyro data.
  memcpy(&payload[6], "GS", 2);

  // IMPORTANT: floats 3..5 are now gyro rates, not Euler angles.
  // The packet remains 100 bytes and status stays at byte 48.
  float values[10] = {
    accX, accY, accZ,
    gyroX, gyroY, gyroZ,
    bmeTemperatureC, bmePressurePa, bmeHumidityPercent, 12.5f
  };
  memcpy(&payload[8], values, sizeof(values));

  payload[48] = 4;
  // 0 = current sample valid. 255 = I2C failed and values are the last good
  // sample. Serial keeps sending a heartbeat in either case.
  payload[49] = imuSampleIsFresh ? 0x00 : 0xFF;
  memcpy(&payload[96], "DTLB", 4);
  Serial.write(payload, sizeof(payload));
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  configureWire();
  configureMpu();

  calibrateGyro();
  configureBme();
  readBmeEnvironment();
  lastUpdate = micros();
  lastTelemetry = millis();
}


void loop() {
  uint32_t now = micros();
  if (now - lastUpdate < IMU_PERIOD_US) return;

  lastUpdate = now;
  bool imuSampleIsFresh = readSensorData();

  if (imuSampleIsFresh) {
    consecutiveI2cFailures = 0;
    // Telemetry is sent at 20 Hz while the MPU is read at 400 Hz. Remember
    // that at least one good sample arrived in this 50 ms interval, so a
    // single NACK on the final 400 Hz read cannot mark the whole packet bad.
    freshSampleSinceTelemetry = true;
    gyroX -= gyroBiasX;
    gyroY -= gyroBiasY;
    gyroZ -= gyroBiasZ;

    // Madgwick is not called here: the dashboard now performs the intended
    // gyro + accelerometer fusion. Removing this unused calculation also
    // avoids propagating NaN values if its correction gradient is zero.
  } else {
    consecutiveI2cFailures++;

    // After several unsuccessful reads, initialise the I2C hardware and MPU
    // again. The telemetry heartbeat continues during the recovery attempt.
    if (consecutiveI2cFailures >= I2C_FAILURES_BEFORE_RECOVERY) {
      configureWire();
      configureMpu();
      consecutiveI2cFailures = 0;
    }
  }

  updateBmeWhenDue();

  if (millis() - lastTelemetry >= TELEMETRY_PERIOD_MS) {
    lastTelemetry = millis();
    sendTelemetry(freshSampleSinceTelemetry);
    freshSampleSinceTelemetry = false;
  }
}
