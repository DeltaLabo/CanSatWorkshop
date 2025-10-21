/***************************************************************************
* ICM20948_WE – Orientación en grados con recovery (port a XIAO ESP32-S3)
* - Mantiene filtro complementario, LPF, validaciones y recuperación I2C.
* - Imprime roll/pitch/yaw cada 500 ms (sin esperar estado estático).
***************************************************************************/

#include <Wire.h>
#include <ICM20948_WE.h>
#include <math.h>

#define ICM20948_ADDR 0x68  // Dirección I2C del ICM-20948 con AD0 a GND

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

// --------- Parámetros del filtro ----------
const float TAU = 0.5f;                 // filtro complementario
const float ACC_LPF_TAU = 0.10f;        // s
const float G_NORM_TOL  = 0.15f;        // ±15% en |g| (para fusión)
const float ACC_CORR_RATE_LIM_DPS = 180.0f;

// --------- Robustez y recuperación ----------
const bool     AUTO_GYR_OFFSET     = true;
const uint16_t GYR_OFFSET_SAMPLES  = 200;

// ---------- Estado del estimador ----------
float roll_deg  = 0.0f;
float pitch_deg = 0.0f;
float yaw_deg   = 0.0f;

unsigned long lastMicros = 0;
unsigned long lastPrint  = 0;

// --------- Utils ----------
static inline float clampf(float x,float lo,float hi){ return x<lo?lo:(x>hi?hi:x); }
static inline float wrap180(float a){ while(a>180)a-=360; while(a<-180)a+=360; return a; }
static inline bool finite3(const xyzFloat& v){ return isfinite(v.x)&&isfinite(v.y)&&isfinite(v.z); }
static inline bool approxSame(const xyzFloat& a,const xyzFloat& b,float eps){
  return fabsf(a.x-b.x)<eps && fabsf(a.y-b.y)<eps && fabsf(a.z-b.z)<eps;
}

void applyIMUConfig(){
  myIMU.setAccOffsets(-16330.0, 16450.0, -16600.0, 16180.0, -16520.0, 16690.0);
  myIMU.setGyrOffsets(0.0f, 0.0f, 0.0f);
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_2000);
  myIMU.setGyrDLPF(ICM20948_DLPF_6);
  myIMU.setTempDLPF(ICM20948_DLPF_6);
}

void scanI2C() {
  Serial.println("Escaneando bus I2C...");

  for (byte i = 0; i < 120; i++) {
    Wire.beginTransmission(i);
    byte error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado en la dirección: 0x");
      Serial.println(i, HEX);
    }
  }
}

void setup(){
  // Inicializar I2C sin configurar el reloj explícitamente
  Wire.begin();   // Usando los pines por defecto para ESP32

  // Inicializar Serial
  Serial.begin(115200);
  delay(300);  // Da tiempo a montar el puerto USB

  // Escanear dispositivos I2C
  //scanI2C();

  // Intentar inicializar el ICM-20948
  if(!myIMU.init()){ 
    Serial.println("ICM20948 no responde");
  }
  else {
    Serial.println("ICM20948 conectado");
  }

  applyIMUConfig();
  delay(50);

  if(AUTO_GYR_OFFSET){
    double sx=0, sy=0, sz=0;
    for(uint16_t i = 0; i < GYR_OFFSET_SAMPLES; i++){
      myIMU.readSensor(); 
      xyzFloat g; 
      myIMU.getGyrValues(&g);
      sx += g.x; 
      sy += g.y; 
      sz += g.z; 
      delay(10);
    }
    myIMU.setGyrOffsets(-(float)(sx / GYR_OFFSET_SAMPLES),
                        -(float)(sy / GYR_OFFSET_SAMPLES),
                        -(float)(sz / GYR_OFFSET_SAMPLES));
  }

  // Inicializar ángulos desde acelerómetro
  myIMU.readSensor();
  xyzFloat gv; 
  myIMU.getGValues(&gv);
  float n = sqrtf(gv.x * gv.x + gv.y * gv.y + gv.z * gv.z); 
  if(n < 1e-6f) n = 1e-6f;
  float ax = gv.x / n, ay = gv.y / n, az = gv.z / n;
  roll_deg  = atan2f(ay, az) * 180.0f / PI;
  pitch_deg = atan2f(-ax, sqrtf(ay * ay + az * az) + 1e-6f) * 180.0f / PI;
  yaw_deg   = 0.0f;
}

void loop(){
  // Tiempo en micros
  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicros) * 1e-6f; 
  lastMicros = nowUs;
  if(dt <= 0.0f) dt = 1e-3f; 
  if(dt > 0.05f) dt = 0.05f;

  // Lectura segura
  xyzFloat gVal, gyrDPS;
  myIMU.readSensor();
  myIMU.getGValues(&gVal);
  myIMU.getGyrValues(&gyrDPS);

  if(!finite3(gVal) || !finite3(gyrDPS)) return;

  // LPF + normalización de g
  static bool accLPFInit = false;
  static xyzFloat gLP = {0, 0, 0};
  if(!accLPFInit){ gLP = gVal; accLPFInit = true; }
  float beta = dt / (ACC_LPF_TAU + dt);
  gLP.x += beta * (gVal.x - gLP.x);
  gLP.y += beta * (gVal.y - gLP.y);
  gLP.z += beta * (gVal.z - gLP.z);

  float normRaw = sqrtf(gLP.x * gLP.x + gLP.y * gLP.y + gLP.z * gLP.z);
  if(normRaw < 1e-6f) normRaw = 1e-6f;
  float ax = gLP.x / normRaw, ay = gLP.y / normRaw, az = gLP.z / normRaw;

  // Ángulos por acelerómetro
  float accRoll  = atan2f(ay, az) * 180.0f / PI;
  float accPitch = atan2f(-ax, sqrtf(ay * ay + az * az) + 1e-6f) * 180.0f / PI;

  // Integración del giro
  float roll_gyro  = roll_deg  + gyrDPS.x * dt;
  float pitch_gyro = pitch_deg + gyrDPS.y * dt;
  float yaw_gyro   = yaw_deg   + gyrDPS.z * dt;

  // Complementario con confianza dinámica
  float alpha_base = TAU / (TAU + dt);
  float dev = fabsf(normRaw - 1.0f);
  float accTrust = 1.0f - clampf((dev - G_NORM_TOL) / G_NORM_TOL, 0.0f, 1.0f);
  if(!isfinite(accRoll) || !isfinite(accPitch)) accTrust = 0.0f;
  float alpha_eff = 1.0f - (1.0f - alpha_base) * accTrust;

  float eRoll  = wrap180(accRoll  - roll_gyro);
  float ePitch = wrap180(accPitch - pitch_gyro);
  float corrMax = ACC_CORR_RATE_LIM_DPS * dt;
  float corrRoll  = clampf((1.0f - alpha_eff) * eRoll,  -corrMax, corrMax);
  float corrPitch = clampf((1.0f - alpha_eff) * ePitch, -corrMax, corrMax);

  roll_deg  = roll_gyro  + corrRoll;
  pitch_deg = pitch_gyro + corrPitch;
  yaw_deg   = wrap180(yaw_gyro);

  // --------- Salida cada 500 ms ---------
  if (millis() - lastPrint >= 500) {
    lastPrint = millis();
    Serial.print("ROLL (°): ");  Serial.print(roll_deg, 2);
    Serial.print("  | PITCH (°): "); Serial.print(pitch_deg, 2);
    Serial.print("  | YAW (°): ");   Serial.println(yaw_deg, 2);
  }

  delay(5); // carga estable; el dt real viene de micros()
}


/******************************************************************************
* FUNCIONES GETTER PARA LORA
* Formato: Valor multiplicado por 100 para preservar 2 decimales
* Códigos de retorno:
*   0: Éxito
*   1: Overflow (valor > INT32_MAX)
*   2: Underflow (valor < INT32_MIN)
*   3: Timeout del sensor (sin lecturas válidas)
******************************************************************************/

/**
* @brief Retorna el ángulo de ROLL multiplicado por 100 para preservar 2 decimales.
* @param output Dirección del entero de 32 bits donde guardar la medición.
* @return Byte con el resultado de la operación:
*         0: Éxito
*         1: Overflow
*         2: Underflow
*         3: Timeout del sensor
*/
unsigned short getRoll(long* output) {
  /*** Verificación de timeout ***/
  if (sensorTimeout) {
    *output = 0;
    return 3;  // Error code 3: Timeout
  }
  
  /*** Adquisición de datos ***/
  float rawRoll = roll_deg;
  
  /*** Procesamiento de datos ***/
  // Multiplicar por 100 para preservar 2 decimales
  double multipliedRoll = rawRoll * 100.0;
  
  /*** Verificación de errores ***/
  if (multipliedRoll > INT32_MAX) {
    *output = INT32_MAX;
    return 1;  // Error code 1: Overflow
  } else if (multipliedRoll < INT32_MIN) {
    *output = INT32_MIN;
    return 2;  // Error code 2: Underflow
  } else {
    *output = (long)multipliedRoll;
    return 0;  // Success
  }
}

/**
* @brief Retorna el ángulo de PITCH multiplicado por 100 para preservar 2 decimales.
* @param output Dirección del entero de 32 bits donde guardar la medición.
* @return Byte con el resultado de la operación:
*         0: Éxito
*         1: Overflow
*         2: Underflow
*         3: Timeout del sensor
*/
unsigned short getPitch(long* output) {
  /*** Verificación de timeout ***/
  if (sensorTimeout) {
    *output = 0;
    return 3;  // Error code 3: Timeout
  }
  
  /*** Adquisición de datos ***/
  float rawPitch = pitch_deg;
  
  /*** Procesamiento de datos ***/
  // Multiplicar por 100 para preservar 2 decimales
  double multipliedPitch = rawPitch * 100.0;
  
  /*** Verificación de errores ***/
  if (multipliedPitch > INT32_MAX) {
    *output = INT32_MAX;
    return 1;  // Error code 1: Overflow
  } else if (multipliedPitch < INT32_MIN) {
    *output = INT32_MIN;
    return 2;  // Error code 2: Underflow
  } else {
    *output = (long)multipliedPitch;
    return 0;  // Success
  }
}

/**
* @brief Retorna el ángulo de YAW multiplicado por 100 para preservar 2 decimales.
* @param output Dirección del entero de 32 bits donde guardar la medición.
* @return Byte con el resultado de la operación:
*         0: Éxito
*         1: Overflow
*         2: Underflow
*         3: Timeout del sensor
*/
unsigned short getYaw(long* output) {
  /*** Verificación de timeout ***/
  if (sensorTimeout) {
    *output = 0;
    return 3;  // Error code 3: Timeout
  }
  
  /*** Adquisición de datos ***/
  float rawYaw = yaw_deg;
  
  /*** Procesamiento de datos ***/
  // Multiplicar por 100 para preservar 2 decimales
  double multipliedYaw = rawYaw * 100.0;
  
  /*** Verificación de errores ***/
  if (multipliedYaw > INT32_MAX) {
    *output = INT32_MAX;
    return 1;  // Error code 1: Overflow
  } else if (multipliedYaw < INT32_MIN) {
    *output = INT32_MIN;
    return 2;  // Error code 2: Underflow
  } else {
    *output = (long)multipliedYaw;
    return 0;  // Success
  }
}

/******************************************************************************
* EJEMPLO DE USO CON LORA
* 
* void enviarDatosLoRa() {
*   long rollValue, pitchValue, yawValue;
*   unsigned short rollStatus, pitchStatus, yawStatus;
*   
*   // Obtener valores
*   rollStatus = getRoll(&rollValue);
*   pitchStatus = getPitch(&pitchValue);
*   yawStatus = getYaw(&yawValue);
*   
*   // Verificar estados y enviar
*   if (rollStatus == 0 && pitchStatus == 0 && yawStatus == 0) {
*     // Todos los valores son válidos
*     // Enviar por LoRa: rollValue, pitchValue, yawValue
*     // Para obtener el valor real: dividir entre 100.0
*     // Ejemplo: float roll_real = rollValue / 100.0;
*   } else {
*     // Manejar errores según los códigos de estado
*     if (rollStatus == 3 || pitchStatus == 3 || yawStatus == 3) {
*       Serial.println("Error: Sensor en timeout");
*     }
*   }
* }
******************************************************************************/

