/***************************************************************************
* ICM20948_WE – Calibración + Orientación en grados (roll, pitch, yaw)
* - roll/pitch: filtro complementario (acel + giro)
* - yaw: integración de giro Z (deriva si no usas magnetómetro)
* - Correcciones: dt estable, tasa de muestreo real (~100 Hz), wrap de yaw,
*   opción de auto‑offset de giroscopio, alpha dependiente de dt.
***************************************************************************/
#include <Wire.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x68

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

// --- Parámetros del filtro ---
const float TAU = 0.5f;   // constante de tiempo del filtro (s): 0.3–1.0 típico

// --- Variables de orientación (grados) ---
float roll_deg  = 0.0f;      // X
float pitch_deg = 0.0f;      // Y
float yaw_deg   = 0.0f;      // Z (solo giro -> deriva)

// Timing
unsigned long lastMicros = 0;
unsigned long lastPrint  = 0;

// --- Si TRUE, mide offsets de giro al inicio (sensor quieto) ---
const bool AUTO_GYR_OFFSET = true;
const uint16_t GYR_OFFSET_SAMPLES = 200; // ~2 s si corremos a ~100 Hz

void setup() {
  Wire.begin();
  Wire.setClock(400000);      // I2C rápido y estable
  Serial.begin(115200);
  while(!Serial) {}

  if(!myIMU.init()){
    Serial.println("ICM20948 does not respond");
  } else {
    Serial.println("ICM20948 is connected");
  }

  // --- Calibración/ajustes (acelerómetro según tus valores) ---
  myIMU.setAccOffsets(-16330.0, 16450.0, -16600.0, 16180.0, -16520.0, 16690.0);

  // Puedes dejar 0 y usar auto‑offset de giro abajo
  myIMU.setGyrOffsets(0.0f, 0.0f, 0.0f);

  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);   // menos ruido

  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);
  myIMU.setGyrDLPF(ICM20948_DLPF_6);   // menos ruido

  myIMU.setTempDLPF(ICM20948_DLPF_6);

  delay(50);

  // --- Auto-offset del giroscopio: sensor QUIETO en esta fase ---
  if (AUTO_GYR_OFFSET) {
    double sx=0, sy=0, sz=0;
    for (uint16_t i=0; i<GYR_OFFSET_SAMPLES; i++) {
      myIMU.readSensor();
      xyzFloat g;
      // Si tu versión no tiene getGyrValues(), usa getGyrRawValues()+factor (ver más abajo)
      myIMU.getGyrValues(&g); // °/s
      sx += g.x;
      sy += g.y;
      sz += g.z;
      delay(10);
    }
    float ox = - (float)(sx / GYR_OFFSET_SAMPLES);
    float oy = - (float)(sy / GYR_OFFSET_SAMPLES);
    float oz = - (float)(sz / GYR_OFFSET_SAMPLES);
    myIMU.setGyrOffsets(ox, oy, oz);
  }

  // --- Inicializar ángulos con el acelerómetro ---
  myIMU.readSensor();
  xyzFloat gVal;
  myIMU.getGValues(&gVal); // en g
  float accRoll  = atan2f(gVal.y, gVal.z) * 180.0f / PI;
  float accPitch = atan2f(-gVal.x, sqrtf(gVal.y*gVal.y + gVal.z*gVal.z)) * 180.0f / PI;

  roll_deg  = accRoll;
  pitch_deg = accPitch;
  yaw_deg   = 0.0f; // sin magnetómetro, arranca en 0

  lastMicros = micros();
  lastPrint  = millis();
}

void loop() {
  // --- dt en segundos, con límites para robustez ---
  unsigned long now = micros();
  float dt = (now - lastMicros) * 1e-6f;
  lastMicros = now;
  if (dt <= 0.0f) dt = 1e-3f;
  if (dt > 0.05f) dt = 0.05f;   // cap para evitar saltos si hay bloqueos

  // --- Lectura de sensores ---
  myIMU.readSensor();

  // Acelerómetro en 'g'
  xyzFloat gVal;
  myIMU.getGValues(&gVal);

  // Giroscopio en °/s
  xyzFloat gyrDPS;
  myIMU.getGyrValues(&gyrDPS); // °/s
  // Si tu versión de librería no tiene getGyrValues(&):
  // xyzFloat gyrRaw; myIMU.getGyrRawValues(&gyrRaw);
  // const float SENS_250DPS = 131.072f; // ICM-20948 @ ±250 dps
  // gyrDPS.x = gyrRaw.x / SENS_250DPS;
  // gyrDPS.y = gyrRaw.y / SENS_250DPS;
  // gyrDPS.z = gyrRaw.z / SENS_250DPS;

  // --- Ángulos por acelerómetro (referencia lenta y estable) ---
  float accRoll  = atan2f(gVal.y, gVal.z) * 180.0f / PI;
  float accPitch = atan2f(-gVal.x, sqrtf(gVal.y*gVal.y + gVal.z*gVal.z)) * 180.0f / PI;

  // --- Integración giroscopio ---
  float roll_gyro  = roll_deg  + gyrDPS.x * dt;
  float pitch_gyro = pitch_deg + gyrDPS.y * dt;
  float yaw_gyro   = yaw_deg   + gyrDPS.z * dt; // deriva con el tiempo

  // --- Filtro complementario: alpha dependiente de dt ---
  float alpha = TAU / (TAU + dt);  // ~0.95–0.99 para dt≈0.01 s y TAU=0.5 s
  roll_deg  = alpha * roll_gyro  + (1.0f - alpha) * accRoll;
  pitch_deg = alpha * pitch_gyro + (1.0f - alpha) * accPitch;
  yaw_deg   = yaw_gyro;

  // --- Mantener yaw acotado [-180, 180] ---
  if (yaw_deg > 180.0f)  yaw_deg -= 360.0f;
  if (yaw_deg < -180.0f) yaw_deg += 360.0f;

  // --- Salida ~100 Hz de filtro, ~20 Hz de impresión ---
  if (millis() - lastPrint >= 50) { // 20 Hz
    lastPrint = millis();
    Serial.print("ROLL (°): ");  Serial.print(roll_deg, 2);
    Serial.print("  | PITCH (°): "); Serial.print(pitch_deg, 2);
    Serial.print("  | YAW (°): ");   Serial.println(yaw_deg, 2);
  }

  // Pequeña pausa para carga de CPU estable; el dt real viene de micros()
  delay(5); // objetivo de ~100–150 Hz de bucle
}

