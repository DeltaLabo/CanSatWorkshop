/***************************************************************************
* ICM20948_WE – Orientación en grados con recovery (port a XIAO ESP32-S3)
* - Mantiene filtro complementario, LPF, validaciones y recuperación I2C.
* - Imprime roll/pitch/yaw cada 500 ms (sin esperar estado estático).
* - Cambios de portabilidad:
*   - Serial USB-CDC (ESP32).
*   - I2C con pines configurables y timeout en ESP32.
*   - #if de plataforma sin alterar la lógica del estimador.
***************************************************************************/

#include <Wire.h>
#include <ICM20948_WE.h>
#include <math.h>

#define ICM20948_ADDR 0x69

// ====== AJUSTA ESTOS PINES SEGÚN TU XIAO ESP32-S3 ======
#ifndef XIAO_SDA
  #define XIAO_SDA 6    
#endif
#ifndef XIAO_SCL
  #define XIAO_SCL 7    
#endif
// =======================================================

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

// --------- Parámetros del filtro ----------
// TAU: constante de tiempo del filtro complementario (balance gyro/accel)
// ACC_LPF_TAU: constante de tiempo del LPF aplicado a la aceleración
// G_NORM_TOL: tolerancia sobre |g| para considerar "confiable" el acelerómetro
// ACC_CORR_RATE_LIM_DPS: límite de tasa de corrección (°/s) inyectada por accel
const float TAU = 0.5f;                 // filtro complementario
const float ACC_LPF_TAU = 0.10f;        // s
const float G_NORM_TOL  = 0.15f;        // ±15% en |g| (para fusión)
const float ACC_CORR_RATE_LIM_DPS = 180.0f;

// --------- Robustez y recuperación ----------
// SENSOR_TIMEOUT_MS: tiempo máximo sin lecturas válidas antes de forzar recovery
// MAX_RECOVERY_TRIES: límite para bajar el clock I2C a 100 kHz como fallback
// AUTO_GYR_OFFSET: si true, calibra automáticamente el offset del giroscopio al inicio
// GYR_OFFSET_SAMPLES: muestras usadas para promediar el offset de gyro
// RECOVERY_DELAY_MS: retraso antes de ejecutar recovery programado (debounce)
const uint32_t SENSOR_TIMEOUT_MS   = 250;
const uint8_t  MAX_RECOVERY_TRIES  = 3;
const bool     AUTO_GYR_OFFSET     = true;
const uint16_t GYR_OFFSET_SAMPLES  = 200;
const uint32_t RECOVERY_DELAY_MS   = 500;

// ---------- Estado del estimador ----------
// Variables de ángulo (en grados) en convención roll (x), pitch (y), yaw (z).
float roll_deg  = 0.0f;
float pitch_deg = 0.0f;
float yaw_deg   = 0.0f;

unsigned long lastMicros = 0;
unsigned long lastPrint  = 0;
unsigned long lastGoodReadMs = 0;
uint8_t  recoveryTries = 0;

// Estado freeze
xyzFloat prevG  = {NAN,NAN,NAN};
xyzFloat prevGy = {NAN,NAN,NAN};
uint8_t sameCount = 0;

// LPF de aceleración (estado interno) y flag de inicialización
bool accLPFInit = false;
xyzFloat gLP = {0,0,0};

// Recovery programado
bool recoveryScheduled = false;
uint32_t recoveryAtMs  = 0;

// --------- Utils ----------
// Funciones auxiliares inlinadas: clamp, wrap de ángulos y checks numéricos
static inline float clampf(float x,float lo,float hi){ return x<lo?lo:(x>hi?hi:x); }
static inline float wrap180(float a){ while(a>180)a-=360; while(a<-180)a+=360; return a; }
static inline bool finite3(const xyzFloat& v){ return isfinite(v.x)&&isfinite(v.y)&&isfinite(v.z); }
static inline bool approxSame(const xyzFloat& a,const xyzFloat& b,float eps){
  return fabsf(a.x-b.x)<eps && fabsf(a.y-b.y)<eps && fabsf(a.z-b.z)<eps;
}

// Configuración homogénea del IMU: rangos, DLPFs y offsets base.
// Nota: setAccOffsets utiliza factory-cal o valores medidos externamente.
void applyIMUConfig(){
  // === Mismas configuraciones que tu sketch original ===
  myIMU.setAccOffsets(-16330.0, 16450.0, -16600.0, 16180.0, -16520.0, 16690.0);
  myIMU.setGyrOffsets(0.0f, 0.0f, 0.0f);
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);
  myIMU.setGyrDLPF(ICM20948_DLPF_6);
  myIMU.setTempDLPF(ICM20948_DLPF_6);
}

// Re-inicialización robusta del IMU y del bus I2C.
// Se usa en caso de timeouts, freeze o lecturas inválidas persistentes.
bool reinitIMU(const char* reason){
  Serial.print("[RECOVERY] "); Serial.print(reason); Serial.println(" -> reinit desde cero");
  delay(5);

  // En ESP32: usa begin con pines designados + timeout; en otras, begin() simple.
#if defined(ARDUINO_ARCH_ESP32)
  Wire.begin(XIAO_SDA, XIAO_SCL);
  Wire.setClock(recoveryTries>=MAX_RECOVERY_TRIES ? 100000 : 400000);
  Wire.setTimeOut(50);
#else
  Wire.begin();
  Wire.setClock(recoveryTries>=MAX_RECOVERY_TRIES ? 100000 : 400000);
#endif
  // init() del IMU; si no responde, se avisa (caller decide reintentar)
  if(!myIMU.init()){
    Serial.println("[RECOVERY] ICM20948 no responde tras init()");
    return false;
  }
  applyIMUConfig();

  // Calibración opcional del offset del giroscopio en reposo
  if (AUTO_GYR_OFFSET){
    double sx=0,sy=0,sz=0;
    for(uint16_t i=0;i<GYR_OFFSET_SAMPLES;i++){
      myIMU.readSensor();
      xyzFloat g; myIMU.getGyrValues(&g);
      sx+=g.x; sy+=g.y; sz+=g.z;
      delay(10);
    }
    myIMU.setGyrOffsets(-(float)(sx/GYR_OFFSET_SAMPLES),
                        -(float)(sy/GYR_OFFSET_SAMPLES),
                        -(float)(sz/GYR_OFFSET_SAMPLES));
  }

  // Reinicio básico de variables desde acelerómetro
  myIMU.readSensor();
  xyzFloat gv; myIMU.getGValues(&gv);
  float n = sqrtf(gv.x*gv.x+gv.y*gv.y+gv.z*gv.z); if(n<1e-6f) n=1e-6f;
  float ax=gv.x/n, ay=gv.y/n, az=gv.z/n;
  roll_deg  = atan2f(ay, az) * 180.0f/PI;
  pitch_deg = atan2f(-ax, sqrtf(ay*ay+az*az)+1e-6f) * 180.0f/PI;
  yaw_deg   = 0.0f;

  accLPFInit=false; gLP = {0,0,0};
  sameCount=0; prevG = {NAN,NAN,NAN}; prevGy = {NAN,NAN,NAN};
  lastGoodReadMs = millis();

  recoveryScheduled = false;
  return true;
}

// Lectura "segura" del IMU con validaciones:
// - Finite check
// - Magnitud mínima
// - Detección de freeze por igualdad persistente
bool readIMUSafe(xyzFloat& gVal, xyzFloat& gyrDPS){
  myIMU.readSensor();
  myIMU.getGValues(&gVal);
  myIMU.getGyrValues(&gyrDPS);

  if(!finite3(gVal) || !finite3(gyrDPS)) return false;

  float mag = fabsf(gVal.x)+fabsf(gVal.y)+fabsf(gVal.z);
  if(mag < 1e-6f) return false;

  if(!isnan(prevG.x) && approxSame(gVal, prevG, 1e-4f) && approxSame(gyrDPS, prevGy, 1e-3f)){
    sameCount++;
    if(sameCount >= 30) return false;
  } else {
    sameCount = 0;
  }

  prevG = gVal; prevGy = gyrDPS;
  return true;
}

void setup(){
  // ====== I2C ======
#if defined(ARDUINO_ARCH_ESP32)
  Wire.begin(XIAO_SDA, XIAO_SCL);   // ESP32: define pines explícitos
  Wire.setClock(400000);
  Wire.setTimeOut(50);
#else
  Wire.begin();
  Wire.setClock(400000);
#endif

  // ====== Serial USB-CDC ======
  Serial.begin(115200);
  delay(300);                       // en S3 da tiempo a montar el USB

  // Inicialización del IMU + configuración de rangos/filtros
  if(!myIMU.init()){ Serial.println("ICM20948 does not respond"); }
  else             { Serial.println("ICM20948 is connected"); }
  applyIMUConfig();
  delay(50);

  // Calibración opcional del offset de giroscopio en reposo inicial
  if(AUTO_GYR_OFFSET){
    double sx=0,sy=0,sz=0;
    for(uint16_t i=0;i<GYR_OFFSET_SAMPLES;i++){
      myIMU.readSensor(); xyzFloat g; myIMU.getGyrValues(&g);
      sx+=g.x; sy+=g.y; sz+=g.z; delay(10);
    }
    myIMU.setGyrOffsets(-(float)(sx/GYR_OFFSET_SAMPLES),
                        -(float)(sy/GYR_OFFSET_SAMPLES),
                        -(float)(sz/GYR_OFFSET_SAMPLES));
  }

  // Inicialización de ángulos desde acelerómetro (suponiendo yaw=0)
  myIMU.readSensor();
  xyzFloat gv; myIMU.getGValues(&gv);
  float n = sqrtf(gv.x*gv.x+gv.y*gv.y+gv.z*gv.z); if(n<1e-6f) n=1e-6f;
  float ax=gv.x/n, ay=gv.y/n, az=gv.z/n;
  roll_deg  = atan2f(ay, az) * 180.0f/PI;
  pitch_deg = atan2f(-ax, sqrtf(ay*ay+az*az)+1e-6f) * 180.0f/PI;
  yaw_deg   = 0.0f;

  accLPFInit=false;
  lastMicros = micros();
  lastPrint  = millis();
  lastGoodReadMs = millis();
}

void loop(){
  // ====== dt seguro ======
  // Cálculo de delta tiempo en segundos con acotación [1 ms, 50 ms]
  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicros) * 1e-6f; lastMicros = nowUs;
  if(dt<=0.0f) dt=1e-3f; if(dt>0.05f) dt=0.05f;

  // ====== Recovery programado (diferido) ======
  // Si se programó un recovery, ejecútalo al cumplirse el tiempo.
  if (recoveryScheduled && (millis() >= recoveryAtMs)) {
    recoveryTries++;
    reinitIMU("Recuperación programada");
    delay(2);
    return;
  }

  // Lectura segura
  xyzFloat gVal, gyrDPS;
  if(!readIMUSafe(gVal, gyrDPS)){
    if (!recoveryScheduled) {
      recoveryScheduled = true;
      recoveryAtMs = millis() + RECOVERY_DELAY_MS;
      Serial.println("[RECOVERY] Fallo de lectura -> recovery programado");
    }


    // Si el fallo persiste por más de SENSOR_TIMEOUT_MS, fuerza recovery inmediato
    if (millis() - lastGoodReadMs > SENSOR_TIMEOUT_MS) {
      recoveryTries++;
      reinitIMU("Timeout sin lecturas válidas");
    }
    delay(2);
    return;
  }
  lastGoodReadMs = millis();

  // LPF + normalización de g
  if(!accLPFInit){ gLP = gVal; accLPFInit=true; }
  float beta = dt / (ACC_LPF_TAU + dt);
  gLP.x += beta*(gVal.x - gLP.x);
  gLP.y += beta*(gVal.y - gLP.y);
  gLP.z += beta*(gVal.z - gLP.z);

  float normRaw = sqrtf(gLP.x*gLP.x + gLP.y*gLP.y + gLP.z*gLP.z);
  if(normRaw < 1e-6f) normRaw = 1e-6f;
  float ax = gLP.x / normRaw, ay = gLP.y / normRaw, az = gLP.z / normRaw;

  // ====== Ángulos desde acelerómetro (solo roll/pitch) ======
  // Convención clásica: roll: rotación en X; pitch: rotación en Y
  float accRoll  = atan2f(ay, az) * 180.0f/PI;
  float accPitch = atan2f(-ax, sqrtf(ay*ay + az*az) + 1e-6f) * 180.0f/PI;
  bool accOK = isfinite(accRoll) && isfinite(accPitch);

  // ====== Integración del giroscopio (predicción) ======
  float roll_gyro  = roll_deg  + gyrDPS.x * dt;
  float pitch_gyro = pitch_deg + gyrDPS.y * dt;
  float yaw_gyro   = yaw_deg   + gyrDPS.z * dt;

  // ====== Filtro complementario con confianza dinámica ======
  // alpha_base: peso "natural" del gyro dado TAU.
  float alpha_base = TAU / (TAU + dt);
  float dev = fabsf(normRaw - 1.0f);
  float accTrust = 1.0f - clampf((dev - G_NORM_TOL)/G_NORM_TOL, 0.0f, 1.0f);
  if(!accOK) accTrust = 0.0f;
  float alpha_eff = 1.0f - (1.0f - alpha_base) * accTrust;

  // Error entre la medición acelerométrica y la predicción del gyro (envuelto a [-180, 180])
  float eRoll  = wrap180(accRoll  - roll_gyro);
  float ePitch = wrap180(accPitch - pitch_gyro);

  // Limita la magnitud de corrección proveniente del acelerómetro
  float corrMax = ACC_CORR_RATE_LIM_DPS * dt;
  float corrRoll  = clampf((1.0f - alpha_eff) * eRoll,  -corrMax, corrMax);
  float corrPitch = clampf((1.0f - alpha_eff) * ePitch, -corrMax, corrMax);

  // Actualización final de estados
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

