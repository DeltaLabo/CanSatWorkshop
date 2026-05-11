/***************************************************************************
 * Microcontrolador: XIAO ESP32-S3
 * Librería: ICM20948_WE
 * 
 * Adaptación a getters compatibles con sistemas LoRa.
 * 
 * Variables expuestas como getters:
 *   - getGyroscope(long output[3])    → velocidad angular X, Y, Z en dps × 100
 *   - getAcceleration(long output[3]) → aceleración X, Y, Z en g × 100
 *   - getOrientation(long output[3])  → ángulos Roll, Pitch, Yaw en grados × 100
 * 
 * IMPORTANTE: La función updateIMU() DEBE llamarse en el loop principal
 * de forma continua (idealmente >= 50 Hz) para que el filtro Madgwick
 * mantenga la orientación correcta. Los getters solo leen el estado.
 ***************************************************************************/

#include <Wire.h>           // Librería I2C de Arduino (para comunicarse con el IMU)
#include <ICM20948_WE.h>    // Librería específica del sensor ICM-20948
#include <math.h>           // Funciones matemáticas: sqrt, sin, cos, atan2, etc.


// ====================== CONFIGURACIÓN GENERAL ===========================

#define ICM20948_ADDR     0x68    // Dirección I2C del sensor. 0x68 si el pin AD0 va a GND.
                                  // Si AD0 va a VDDIO sería 0x69.
#define SERIAL_BAUD       115200   // Velocidad del puerto serie (baudios por segundo).
#define PRINT_PERIOD_MS   200      // Cada cuántos milisegundos imprimir los ángulos.


// Ganancia del filtro Madgwick. Controla cuánto "confía" el filtro en accel+mag
// frente al giroscopio.
const float MADGWICK_BETA = 0.1f;

// Número de muestras que tomamos al arrancar para calibrar el giroscopio.
const uint16_t GYR_CALIB_SAMPLES = 500;

// ========================================================================
// ====================== OBJETO DEL SENSOR ===============================
// ========================================================================

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

// ========================================================================
// ====================== VARIABLES DE ESTADO =============================
// ========================================================================

// Cuaternión que mantiene la orientación actual (estado del filtro Madgwick)
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;

// Ángulos de Euler finales (en grados) — los lee getOrientation()
float roll_deg = 0.0f, pitch_deg = 0.0f, yaw_deg = 0.0f;

// Lecturas crudas más recientes — las leen getGyroscope() y getAcceleration()
// Se actualizan en cada llamada a updateIMU()
float gyro_x_dps = 0.0f, gyro_y_dps = 0.0f, gyro_z_dps = 0.0f;
float accel_x_g  = 0.0f, accel_y_g  = 0.0f, accel_z_g  = 0.0f;

// Flag que indica si el IMU ya fue inicializado correctamente
bool imu_ready = false;

// Variables de tiempo
unsigned long lastMicros = 0;
unsigned long lastPrintMs = 0;

// Offsets y escalas del magnetómetro (calibración hard/soft-iron)
float mag_offset_x = 0.0f, mag_offset_y = 0.0f, mag_offset_z = 0.0f;
float mag_scale_x  = 1.0f, mag_scale_y  = 1.0f, mag_scale_z  = 1.0f;

// ========================================================================
// ====================== FUNCIONES AUXILIARES ============================
// ========================================================================

static inline float invSqrt(float x) {
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  return y;
}

// ========================================================================
// ====================== CONFIGURACIÓN DEL IMU ===========================
// ========================================================================

void applyIMUConfig() {
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);
  myIMU.setAccSampleRateDivider(10);

  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);
  myIMU.setGyrDLPF(ICM20948_DLPF_6);
  myIMU.setGyrSampleRateDivider(10);

  myIMU.setTempDLPF(ICM20948_DLPF_6);

  myIMU.setMagOpMode(AK09916_CONT_MODE_100HZ);
}

// ========================================================================
// ====================== CALIBRACIÓN DEL GIROSCOPIO ======================
// ========================================================================

void calibrateGyroAtStart() {
  Serial.println(F("==================================================="));
  Serial.println(F("CALIBRACIÓN DE GIROSCOPIO"));
  Serial.println(F("Mantén el sensor COMPLETAMENTE QUIETO..."));
  Serial.println(F("==================================================="));
  delay(2000);

  double sx = 0, sy = 0, sz = 0;
  xyzFloat g;

  for (uint16_t i = 0; i < GYR_CALIB_SAMPLES; i++) {
    myIMU.readSensor();
    myIMU.getGyrValues(&g);
    sx += g.x;
    sy += g.y;
    sz += g.z;
    delay(3);
    if (i % 50 == 0) Serial.print('.');
  }
  Serial.println();

  float ox = (float)(sx / GYR_CALIB_SAMPLES);
  float oy = (float)(sy / GYR_CALIB_SAMPLES);
  float oz = (float)(sz / GYR_CALIB_SAMPLES);

  myIMU.setGyrOffsets(-ox, -oy, -oz);

  Serial.print(F("Offsets gyro (dps): "));
  Serial.print(ox, 4); Serial.print(", ");
  Serial.print(oy, 4); Serial.print(", ");
  Serial.println(oz, 4);
  Serial.println(F("Calibración completada.\n"));
}

// ========================================================================
// ====================== INICIALIZACIÓN DEL CUATERNIÓN ===================
// ========================================================================

void initQuaternionFromSensors() {
  Serial.println(F("Estableciendo orientación inicial..."));
  delay(200);

  xyzFloat a, m;

  float ax_sum = 0, ay_sum = 0, az_sum = 0;
  float mx_sum = 0, my_sum = 0, mz_sum = 0;
  const int N = 50;

  for (int i = 0; i < N; i++) {
    myIMU.readSensor();
    myIMU.getGValues(&a);
    myIMU.getMagValues(&m);
    ax_sum += a.x; ay_sum += a.y; az_sum += a.z;
    mx_sum += m.x; my_sum += m.y; mz_sum += m.z;
    delay(10);
  }

  float ax = ax_sum / N, ay = ay_sum / N, az = az_sum / N;

  float mx = (mx_sum / N - mag_offset_x) * mag_scale_x;
  float my = (my_sum / N - mag_offset_y) * mag_scale_y;
  float mz = (mz_sum / N - mag_offset_z) * mag_scale_z;

  float mx_a =  my;
  float my_a =  mx;
  float mz_a = -mz;

  float roll0  = atan2f(ay, az);
  float pitch0 = atan2f(-ax, sqrtf(ay * ay + az * az));

  float cosR = cosf(roll0),  sinR = sinf(roll0);
  float cosP = cosf(pitch0), sinP = sinf(pitch0);

  float mxh = mx_a * cosP + my_a * sinR * sinP + mz_a * cosR * sinP;
  float myh = my_a * cosR - mz_a * sinR;

  float yaw0 = atan2f(-myh, mxh);

  float cy = cosf(yaw0 * 0.5f);
  float sy = sinf(yaw0 * 0.5f);
  float cp = cosf(pitch0 * 0.5f);
  float sp = sinf(pitch0 * 0.5f);
  float cr = cosf(roll0 * 0.5f);
  float sr = sinf(roll0 * 0.5f);

  q0 = cr * cp * cy + sr * sp * sy;
  q1 = sr * cp * cy - cr * sp * sy;
  q2 = cr * sp * cy + sr * cp * sy;
  q3 = cr * cp * sy - sr * sp * cy;

  Serial.print(F("Orientación inicial (grados): Roll="));
  Serial.print(roll0 * 180.0f / PI, 2);
  Serial.print(F(" Pitch="));
  Serial.print(pitch0 * 180.0f / PI, 2);
  Serial.print(F(" Yaw="));
  Serial.println(yaw0 * 180.0f / PI, 2);
  Serial.println();
}

// ========================================================================
// ====================== FILTRO MADGWICK 9-DOF ===========================
// ========================================================================

void madgwickUpdate(float gx, float gy, float gz,
                    float ax, float ay, float az,
                    float mx, float my, float mz,
                    float dt) {
  float recipNorm;
  float s0, s1, s2, s3;
  float qDot1, qDot2, qDot3, qDot4;
  float hx, hy;
  float _2q0mx, _2q0my, _2q0mz, _2q1mx;
  float _2bx, _2bz, _4bx, _4bz;
  float _2q0, _2q1, _2q2, _2q3;
  float _2q0q2, _2q2q3;
  float q0q0, q0q1, q0q2, q0q3;
  float q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;

  qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
  qDot2 = 0.5f * ( q0 * gx + q2 * gz - q3 * gy);
  qDot3 = 0.5f * ( q0 * gy - q1 * gz + q3 * gx);
  qDot4 = 0.5f * ( q0 * gz + q1 * gy - q2 * gx);

  if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)) &&
      !((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))) {

    recipNorm = invSqrt(ax * ax + ay * ay + az * az);
    ax *= recipNorm; ay *= recipNorm; az *= recipNorm;

    recipNorm = invSqrt(mx * mx + my * my + mz * mz);
    mx *= recipNorm; my *= recipNorm; mz *= recipNorm;

    _2q0mx = 2.0f * q0 * mx;
    _2q0my = 2.0f * q0 * my;
    _2q0mz = 2.0f * q0 * mz;
    _2q1mx = 2.0f * q1 * mx;
    _2q0 = 2.0f * q0;
    _2q1 = 2.0f * q1;
    _2q2 = 2.0f * q2;
    _2q3 = 2.0f * q3;
    _2q0q2 = 2.0f * q0 * q2;
    _2q2q3 = 2.0f * q2 * q3;
    q0q0 = q0 * q0;
    q0q1 = q0 * q1;
    q0q2 = q0 * q2;
    q0q3 = q0 * q3;
    q1q1 = q1 * q1;
    q1q2 = q1 * q2;
    q1q3 = q1 * q3;
    q2q2 = q2 * q2;
    q2q3 = q2 * q3;
    q3q3 = q3 * q3;

    hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1
       + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
    hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2
       - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
    _2bx = sqrtf(hx * hx + hy * hy);
    _2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3
         - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
    _4bx = 2.0f * _2bx;
    _4bz = 2.0f * _2bz;

    s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax)
       + _2q1 * (2.0f * q0q1 + _2q2q3 - ay)
       - _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
       + (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
       + _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
    s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax)
       + _2q0 * (2.0f * q0q1 + _2q2q3 - ay)
       - 4.0f * q1 * (1.0f - 2.0f * q1q1 - 2.0f * q2q2 - az)
       + _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
       + (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
       + (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
    s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax)
       + _2q3 * (2.0f * q0q1 + _2q2q3 - ay)
       - 4.0f * q2 * (1.0f - 2.0f * q1q1 - 2.0f * q2q2 - az)
       + (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
       + (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
       + (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
    s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax)
       + _2q2 * (2.0f * q0q1 + _2q2q3 - ay)
       + (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx)
       + (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my)
       + _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);

    recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);
    s0 *= recipNorm; s1 *= recipNorm; s2 *= recipNorm; s3 *= recipNorm;

    qDot1 -= MADGWICK_BETA * s0;
    qDot2 -= MADGWICK_BETA * s1;
    qDot3 -= MADGWICK_BETA * s2;
    qDot4 -= MADGWICK_BETA * s3;
  }

  q0 += qDot1 * dt;
  q1 += qDot2 * dt;
  q2 += qDot3 * dt;
  q3 += qDot4 * dt;

  recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
  q0 *= recipNorm; q1 *= recipNorm; q2 *= recipNorm; q3 *= recipNorm;
}

// ========================================================================
// ====================== CUATERNIÓN → ÁNGULOS EULER ======================
// ========================================================================

void quaternionToEuler() {
  float sinr_cosp = 2.0f * (q0 * q1 + q2 * q3);
  float cosr_cosp = 1.0f - 2.0f * (q1 * q1 + q2 * q2);
  roll_deg = atan2f(sinr_cosp, cosr_cosp) * 180.0f / PI;

  float sinp = 2.0f * (q0 * q2 - q3 * q1);
  if (fabsf(sinp) >= 1.0f)
    pitch_deg = copysignf(90.0f, sinp);
  else
    pitch_deg = asinf(sinp) * 180.0f / PI;

  float siny_cosp = 2.0f * (q0 * q3 + q1 * q2);
  float cosy_cosp = 1.0f - 2.0f * (q2 * q2 + q3 * q3);
  yaw_deg = atan2f(siny_cosp, cosy_cosp) * 180.0f / PI;
}

// ========================================================================
// ====================== ACTUALIZACIÓN DEL IMU ===========================
// ========================================================================
/**
 * @brief Actualiza el estado interno del IMU: lee sensores, aplica filtro
 *        Madgwick y calcula ángulos Euler.
 * 
 * DEBE llamarse de forma continua en el loop() principal a alta frecuencia
 * (idealmente >= 50 Hz) para que el filtro de fusión mantenga la orientación
 * correcta. Los getters (getGyroscope, getAcceleration, getOrientation)
 * solo leen las variables que esta función actualiza.
 */
void updateIMU() {
  if (!imu_ready) return;

  // ---- Calcular dt ----
  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicros) * 1e-6f;
  lastMicros = nowUs;

  if (dt <= 0.0f) dt = 1e-3f;
  if (dt > 0.05f) dt = 0.05f;

  // ---- Leer los 3 sensores ----
  myIMU.readSensor();
  xyzFloat a, g, m;
  myIMU.getGValues(&a);
  myIMU.getGyrValues(&g);
  myIMU.getMagValues(&m);

  // Validación: si algún valor es NaN/inf, saltamos esta iteración
  if (!isfinite(a.x) || !isfinite(g.x) || !isfinite(m.x)) return;

  // ---- Guardar lecturas crudas para getGyroscope y getAcceleration ----
  gyro_x_dps = g.x;
  gyro_y_dps = g.y;
  gyro_z_dps = g.z;
  accel_x_g  = a.x;
  accel_y_g  = a.y;
  accel_z_g  = a.z;

  // ---- Calibración del magnetómetro ----
  float mx = (m.x - mag_offset_x) * mag_scale_x;
  float my = (m.y - mag_offset_y) * mag_scale_y;
  float mz = (m.z - mag_offset_z) * mag_scale_z;

  // ---- Convertir gyro de dps a rad/s ----
  float gx = g.x * PI / 180.0f;
  float gy = g.y * PI / 180.0f;
  float gz = g.z * PI / 180.0f;

  // ---- Alinear ejes del magnetómetro ----
  float mx_aligned =  my;
  float my_aligned =  mx;
  float mz_aligned = -mz;

  // ---- Actualizar cuaternión y calcular Euler ----
  madgwickUpdate(gx, gy, gz, a.x, a.y, a.z,
                 mx_aligned, my_aligned, mz_aligned, dt);
  quaternionToEuler();
}

// ========================================================================
// ====================== GETTERS PARA SISTEMAS LoRa ======================
// ========================================================================

/**
 * @brief Returns the current gyroscope values (X, Y, Z) multiplied by 100
 *        to preserve 2 decimal places. Units: degrees per second (dps).
 * @param output Array of 3 32-bit integers to save the measurements to.
 *               output[0] = X axis, output[1] = Y axis, output[2] = Z axis.
 * @return result Byte containing the result of the get operation.
 *                0: Success
 *                1: Overflow
 *                2: Underflow
 *                3: Sensor not ready / invalid reading
 */
unsigned short getGyroscope(long output[3]) {
  /*** Raw data acquisition ***/
  // The Madgwick filter runs in updateIMU(); here we just read the latest values
  // already captured into globals. Caller must invoke updateIMU() in the loop.
  
  if (!imu_ready) {
    output[0] = 0; output[1] = 0; output[2] = 0;
    // Error code 3: IMU not initialized
    return 3;
  }
  
  float rawGyro[3] = { gyro_x_dps, gyro_y_dps, gyro_z_dps };
  
  // Validate readings (NaN/inf check)
  if (!isfinite(rawGyro[0]) || !isfinite(rawGyro[1]) || !isfinite(rawGyro[2])) {
    output[0] = 0; output[1] = 0; output[2] = 0;
    // Error code 3: invalid reading
    return 3;
  }
  
  /*** Data processing ***/
  // Use multiplier x100 to preserve 2 decimal places
  // Saved to double to avoid overflow during multiplication
  double multipliedGyro[3];
  multipliedGyro[0] = (double)rawGyro[0] * 100.0;
  multipliedGyro[1] = (double)rawGyro[1] * 100.0;
  multipliedGyro[2] = (double)rawGyro[2] * 100.0;
  
  /*** Error checking ***/
  // Check overflow/underflow for each axis
  // With ±250 dps range × 100 = ±25000, well within long range,
  // but we check anyway in case of sensor anomalies
  for (int i = 0; i < 3; i++) {
    if (multipliedGyro[i] > INT32_MAX) {
      output[i] = INT32_MAX;
      // Error code 1: Overflow
      return 1;
    } else if (multipliedGyro[i] < -(INT32_MAX + 1.0)) {
      output[i] = -(INT32_MAX);
      // Error code 2: Underflow
      return 2;
    } else {
      output[i] = (long)multipliedGyro[i];
    }
  }
  
  // Success
  return 0;
}

/**
 * @brief Returns the current acceleration values (X, Y, Z) multiplied by 100
 *        to preserve 2 decimal places. Units: g (1 g = 9.81 m/s²).
 * @param output Array of 3 32-bit integers to save the measurements to.
 *               output[0] = X axis, output[1] = Y axis, output[2] = Z axis.
 * @return result Byte containing the result of the get operation.
 *                0: Success
 *                1: Overflow
 *                2: Underflow
 *                3: Sensor not ready / invalid reading
 */
unsigned short getAcceleration(long output[3]) {
  /*** Raw data acquisition ***/
  // Read values already captured by updateIMU() in the loop
  
  if (!imu_ready) {
    output[0] = 0; output[1] = 0; output[2] = 0;
    // Error code 3: IMU not initialized
    return 3;
  }
  
  float rawAccel[3] = { accel_x_g, accel_y_g, accel_z_g };
  
  // Validate readings (NaN/inf check)
  if (!isfinite(rawAccel[0]) || !isfinite(rawAccel[1]) || !isfinite(rawAccel[2])) {
    output[0] = 0; output[1] = 0; output[2] = 0;
    // Error code 3: invalid reading
    return 3;
  }
  
  /*** Data processing ***/
  // Use multiplier x100 to preserve 2 decimal places
  double multipliedAccel[3];
  multipliedAccel[0] = (double)rawAccel[0] * 100.0;
  multipliedAccel[1] = (double)rawAccel[1] * 100.0;
  multipliedAccel[2] = (double)rawAccel[2] * 100.0;
  
  /*** Error checking ***/
  // With ±2g range × 100 = ±200, very far from overflow, but check anyway
  for (int i = 0; i < 3; i++) {
    if (multipliedAccel[i] > INT32_MAX) {
      output[i] = INT32_MAX;
      // Error code 1: Overflow
      return 1;
    } else if (multipliedAccel[i] < -(INT32_MAX + 1.0)) {
      output[i] = -(INT32_MAX);
      // Error code 2: Underflow
      return 2;
    } else {
      output[i] = (long)multipliedAccel[i];
    }
  }
  
  // Success
  return 0;
}

/**
 * @brief Returns the current orientation (Roll, Pitch, Yaw) multiplied by 100
 *        to preserve 2 decimal places. Units: degrees.
 *        Roll  range: ±180°
 *        Pitch range: ±90°
 *        Yaw   range: ±180°
 * @param output Array of 3 32-bit integers to save the measurements to.
 *               output[0] = Roll, output[1] = Pitch, output[2] = Yaw.
 * @return result Byte containing the result of the get operation.
 *                0: Success
 *                1: Overflow
 *                2: Underflow
 *                3: Sensor not ready / invalid reading
 */
unsigned short getOrientation(long output[3]) {
  /*** Raw data acquisition ***/
  // The Madgwick filter has already been applied by updateIMU();
  // here we just read the pre-computed Euler angles.
  
  if (!imu_ready) {
    output[0] = 0; output[1] = 0; output[2] = 0;
    // Error code 3: IMU not initialized
    return 3;
  }
  
  float rawOrientation[3] = { roll_deg, pitch_deg, yaw_deg };
  
  // Validate readings (NaN/inf check)
  if (!isfinite(rawOrientation[0]) || !isfinite(rawOrientation[1]) || !isfinite(rawOrientation[2])) {
    output[0] = 0; output[1] = 0; output[2] = 0;
    // Error code 3: invalid reading
    return 3;
  }
  
  /*** Data processing ***/
  // Use multiplier x100 to preserve 2 decimal places
  double multipliedOrientation[3];
  multipliedOrientation[0] = (double)rawOrientation[0] * 100.0;
  multipliedOrientation[1] = (double)rawOrientation[1] * 100.0;
  multipliedOrientation[2] = (double)rawOrientation[2] * 100.0;
  
  /*** Error checking ***/
  // Roll/Yaw range ±180° × 100 = ±18000, Pitch ±90° × 100 = ±9000, all safe
  for (int i = 0; i < 3; i++) {
    if (multipliedOrientation[i] > INT32_MAX) {
      output[i] = INT32_MAX;
      // Error code 1: Overflow
      return 1;
    } else if (multipliedOrientation[i] < -(INT32_MAX + 1.0)) {
      output[i] = -(INT32_MAX);
      // Error code 2: Underflow
      return 2;
    } else {
      output[i] = (long)multipliedOrientation[i];
    }
  }
  
  // Success
  return 0;
}

// ========================================================================
// ====================== SETUP (se ejecuta una vez) ======================
// ========================================================================

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial && millis() < 3000) {}

  Wire.begin();
  Wire.setClock(400000);
#if defined(ARDUINO_ARCH_ESP32)
  Wire.setTimeOut(50);
#endif

  Serial.println(F("\n=== ICM-20948 9-DOF Madgwick (LoRa getters) ==="));

  if (!myIMU.init()) {
    Serial.println(F("ERROR: ICM-20948 no responde. Revisa cableado/direccion."));
    while (1) delay(100);
  }
  Serial.println(F("ICM-20948 OK"));

  if (!myIMU.initMagnetometer()) {
    Serial.println(F("ERROR: AK09916 (magnetometro) no responde."));
    while (1) delay(100);
  }
  Serial.println(F("AK09916 OK"));

  applyIMUConfig();
  delay(100);

  calibrateGyroAtStart();
  initQuaternionFromSensors();

  lastMicros = micros();
  lastPrintMs = millis();
  
  // A partir de aquí los getters devolverán datos válidos
  imu_ready = true;
}

// ========================================================================
// ====================== LOOP (se ejecuta sin parar) =====================
// ========================================================================

void loop() {
  // CRÍTICO: updateIMU() debe llamarse continuamente para que el filtro
  // Madgwick mantenga la orientación correcta. Los getters solo leen
  // el estado que esta función actualiza.
  updateIMU();

  // ---- Demostración: cada PRINT_PERIOD_MS ms, llamamos a los getters ----
  if (millis() - lastPrintMs >= PRINT_PERIOD_MS) {
    lastPrintMs = millis();
    
    long gyro[3], accel[3], orient[3];
    unsigned short rg = getGyroscope(gyro);
    unsigned short ra = getAcceleration(accel);
    unsigned short ro = getOrientation(orient);

    Serial.print(F("GYRO   (dps*100)  [code "));
    Serial.print(rg); Serial.print(F("]: "));
    Serial.print(gyro[0]); Serial.print(F(", "));
    Serial.print(gyro[1]); Serial.print(F(", "));
    Serial.println(gyro[2]);

    Serial.print(F("ACCEL  (g*100)    [code "));
    Serial.print(ra); Serial.print(F("]: "));
    Serial.print(accel[0]); Serial.print(F(", "));
    Serial.print(accel[1]); Serial.print(F(", "));
    Serial.println(accel[2]);

    Serial.print(F("ORIENT (deg*100)  [code "));
    Serial.print(ro); Serial.print(F("]: R="));
    Serial.print(orient[0]); Serial.print(F(", P="));
    Serial.print(orient[1]); Serial.print(F(", Y="));
    Serial.println(orient[2]);
    Serial.println();
  }
}
