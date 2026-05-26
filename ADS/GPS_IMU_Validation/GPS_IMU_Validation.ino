#include <Wire.h>
#include <ICM20948_WE.h>
#include <TinyGPSPlus.h>
#include <math.h>


// ── GPS (UART) ──
#define GPS_RX_PIN      16      // ESP32 RX ← TX del GPS
#define GPS_TX_PIN      17      // ESP32 TX → RX del GPS
#define GPS_BAUD        9600
#define GPS_UART_TIMEOUT_MS 5   // [C] Timeout máx. UART = 5 ms

// ── IMU (I2C) ──
#define ICM20948_ADDR   0x68    // AD0 → GND
#define I2C_SDA_PIN     5       // Pin SDA XIAO ESP32S3
#define I2C_SCL_PIN     6       // Pin SCL XIAO ESP32S3

// ── Loop ──
#define LOOP_PERIOD_MS  200     // [C] 5 Hz = 200 ms por ciclo
#define PRINT_PERIOD_MS 1000    // Imprimir resumen cada 1 s

const float MADGWICK_BETA     = 0.1f;
const uint16_t GYR_CALIB_SAMPLES = 100;  // Reducido: ~1 s de calibración

TinyGPSPlus gps;
ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

// ── Datos GPS ──
struct GPSData {
  bool    valid;
  float   lat;
  float   lon;
  float   altitude_m;
  float   speed_kmh;
  uint8_t satellites;
  float   hdop;
  bool    hasTime;
  uint8_t hour, minute, second;
  uint16_t year;
  uint8_t month, day;
};

// ── Datos IMU ──
struct IMUData {
  bool  valid;
  float ax, ay, az;         // Aceleración (g)
  float gx, gy, gz;         // Velocidad angular (dps)
  float mx, my, mz;         // Campo magnético (µT)
  float roll, pitch, yaw;   // Ángulos de Euler (grados)
};

// ── Cuaternión de orientación (estado global del filtro Madgwick) ──
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;

// ── Calibración magnetómetro ──
float mag_offset_x = 0.0f, mag_offset_y = 0.0f, mag_offset_z = 0.0f;
float mag_scale_x  = 1.0f, mag_scale_y  = 1.0f, mag_scale_z  = 1.0f;

// ── Instancias globales de datos ──
GPSData gpsData = {false};
IMUData imuData = {false};

// ── Control de tiempo ──
unsigned long lastLoopMs  = 0;
unsigned long lastPrintMs = 0;
unsigned long lastMicros  = 0;


struct ValidationReport {
  // GPS
  uint32_t gps_reads_total;
  uint32_t gps_reads_valid;
  uint32_t gps_uart_timeout_violations;   // Lecturas que tardaron > 5 ms

  // IMU
  uint32_t imu_reads_total;
  uint32_t imu_reads_valid;
  uint32_t imu_process_time_violations;   // Process/Calculate > 5 ms

  // Loop timing
  uint32_t loop_cycles;
  uint32_t loop_timing_violations;        // Ciclos que se pasaron de 200 ms
  float    loop_max_dt_ms;

  // Madgwick timing
  float    madgwick_max_ms;
} val;


// Fast inverse square root (Quake trick) — usado por Madgwick
static inline float invSqrt(float x) {
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  return y;
}

void print2(uint8_t v) { if (v < 10) Serial.print('0'); Serial.print(v); }


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


void calibrateGyroAtStart() {
  Serial.println(F("----------------------------------------------"));
  Serial.println(F("[CAL] Mantén el sensor QUIETO (~1 s)..."));
  delay(500);

  double sx = 0, sy = 0, sz = 0;
  xyzFloat g;

  for (uint16_t i = 0; i < GYR_CALIB_SAMPLES; i++) {
    myIMU.readSensor();
    myIMU.getGyrValues(&g);
    sx += g.x; sy += g.y; sz += g.z;
    delay(6);  // 100 muestras × 6 ms ≈ 600 ms
    if (i % 20 == 0) Serial.print('.');
  }
  Serial.println();

  float ox = (float)(sx / GYR_CALIB_SAMPLES);
  float oy = (float)(sy / GYR_CALIB_SAMPLES);
  float oz = (float)(sz / GYR_CALIB_SAMPLES);
  myIMU.setGyrOffsets(-ox, -oy, -oz);

  Serial.print(F("[CAL] Offsets gyro (dps): "));
  Serial.print(ox, 4); Serial.print(F(", "));
  Serial.print(oy, 4); Serial.print(F(", "));
  Serial.println(oz, 4);
  Serial.println(F("[CAL] Calibración completada.\n"));
}


void initQuaternionFromSensors() {
  Serial.println(F("[IMU] Calculando orientación inicial..."));
  delay(200);

  xyzFloat a, m;
  float ax_s=0, ay_s=0, az_s=0, mx_s=0, my_s=0, mz_s=0;
  const int N = 50;

  for (int i = 0; i < N; i++) {
    myIMU.readSensor();
    myIMU.getGValues(&a);
    myIMU.getMagValues(&m);
    ax_s += a.x; ay_s += a.y; az_s += a.z;
    mx_s += m.x; my_s += m.y; mz_s += m.z;
    delay(10);
  }

  float ax = ax_s/N, ay = ay_s/N, az = az_s/N;
  float mx = (mx_s/N - mag_offset_x) * mag_scale_x;
  float my = (my_s/N - mag_offset_y) * mag_scale_y;
  float mz = (mz_s/N - mag_offset_z) * mag_scale_z;

  float mx_a =  my, my_a = mx, mz_a = -mz;

  float roll0  = atan2f(ay, az);
  float pitch0 = atan2f(-ax, sqrtf(ay*ay + az*az));

  float cosR = cosf(roll0), sinR = sinf(roll0);
  float cosP = cosf(pitch0), sinP = sinf(pitch0);

  float mxh = mx_a*cosP + my_a*sinR*sinP + mz_a*cosR*sinP;
  float myh = my_a*cosR - mz_a*sinR;
  float yaw0 = atan2f(-myh, mxh);

  float cy=cosf(yaw0*0.5f), sy=sinf(yaw0*0.5f);
  float cp=cosf(pitch0*0.5f), sp=sinf(pitch0*0.5f);
  float cr=cosf(roll0*0.5f), sr=sinf(roll0*0.5f);

  q0 = cr*cp*cy + sr*sp*sy;
  q1 = sr*cp*cy - cr*sp*sy;
  q2 = cr*sp*cy + sr*cp*sy;
  q3 = cr*cp*sy - sr*sp*cy;

  Serial.print(F("[IMU] Orientación inicial: Roll="));
  Serial.print(roll0*180.0f/PI, 2);
  Serial.print(F("  Pitch="));
  Serial.print(pitch0*180.0f/PI, 2);
  Serial.print(F("  Yaw="));
  Serial.println(yaw0*180.0f/PI, 2);
  Serial.println();
}


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
  float _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3;
  float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;

  qDot1 = 0.5f * (-q1*gx - q2*gy - q3*gz);
  qDot2 = 0.5f * ( q0*gx + q2*gz - q3*gy);
  qDot3 = 0.5f * ( q0*gy - q1*gz + q3*gx);
  qDot4 = 0.5f * ( q0*gz + q1*gy - q2*gx);

  if (!((ax==0.0f)&&(ay==0.0f)&&(az==0.0f)) &&
      !((mx==0.0f)&&(my==0.0f)&&(mz==0.0f))) {

    recipNorm = invSqrt(ax*ax + ay*ay + az*az);
    ax *= recipNorm; ay *= recipNorm; az *= recipNorm;

    recipNorm = invSqrt(mx*mx + my*my + mz*mz);
    mx *= recipNorm; my *= recipNorm; mz *= recipNorm;

    _2q0mx=2.0f*q0*mx; _2q0my=2.0f*q0*my; _2q0mz=2.0f*q0*mz;
    _2q1mx=2.0f*q1*mx;
    _2q0=2.0f*q0; _2q1=2.0f*q1; _2q2=2.0f*q2; _2q3=2.0f*q3;
    _2q0q2=2.0f*q0*q2; _2q2q3=2.0f*q2*q3;
    q0q0=q0*q0; q0q1=q0*q1; q0q2=q0*q2; q0q3=q0*q3;
    q1q1=q1*q1; q1q2=q1*q2; q1q3=q1*q3;
    q2q2=q2*q2; q2q3=q2*q3; q3q3=q3*q3;

    hx = mx*q0q0 - _2q0my*q3 + _2q0mz*q2 + mx*q1q1
       + _2q1*my*q2 + _2q1*mz*q3 - mx*q2q2 - mx*q3q3;
    hy = _2q0mx*q3 + my*q0q0 - _2q0mz*q1 + _2q1mx*q2
       - my*q1q1 + my*q2q2 + _2q2*mz*q3 - my*q3q3;
    _2bx = sqrtf(hx*hx + hy*hy);
    _2bz = -_2q0mx*q2 + _2q0my*q1 + mz*q0q0 + _2q1mx*q3
          - mz*q1q1 + _2q2*my*q3 - mz*q2q2 + mz*q3q3;
    _4bx = 2.0f*_2bx; _4bz = 2.0f*_2bz;

    s0 = -_2q2*(2.0f*q1q3-_2q0q2-ax) + _2q1*(2.0f*q0q1+_2q2q3-ay)
       - _2bz*q2*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
       + (-_2bx*q3+_2bz*q1)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
       + _2bx*q2*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);
    s1 = _2q3*(2.0f*q1q3-_2q0q2-ax) + _2q0*(2.0f*q0q1+_2q2q3-ay)
       - 4.0f*q1*(1.0f-2.0f*q1q1-2.0f*q2q2-az)
       + _2bz*q3*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
       + (_2bx*q2+_2bz*q0)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
       + (_2bx*q3-_4bz*q1)*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);
    s2 = -_2q0*(2.0f*q1q3-_2q0q2-ax) + _2q3*(2.0f*q0q1+_2q2q3-ay)
       - 4.0f*q2*(1.0f-2.0f*q1q1-2.0f*q2q2-az)
       + (-_4bx*q2-_2bz*q0)*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
       + (_2bx*q1+_2bz*q3)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
       + (_2bx*q0-_4bz*q2)*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);
    s3 = _2q1*(2.0f*q1q3-_2q0q2-ax) + _2q2*(2.0f*q0q1+_2q2q3-ay)
       + (-_4bx*q3+_2bz*q1)*(_2bx*(0.5f-q2q2-q3q3)+_2bz*(q1q3-q0q2)-mx)
       + (-_2bx*q0+_2bz*q2)*(_2bx*(q1q2-q0q3)+_2bz*(q0q1+q2q3)-my)
       + _2bx*q1*(_2bx*(q0q2+q1q3)+_2bz*(0.5f-q1q1-q2q2)-mz);

    recipNorm = invSqrt(s0*s0 + s1*s1 + s2*s2 + s3*s3);
    s0*=recipNorm; s1*=recipNorm; s2*=recipNorm; s3*=recipNorm;

    qDot1 -= MADGWICK_BETA*s0;
    qDot2 -= MADGWICK_BETA*s1;
    qDot3 -= MADGWICK_BETA*s2;
    qDot4 -= MADGWICK_BETA*s3;
  }

  q0 += qDot1*dt; q1 += qDot2*dt;
  q2 += qDot3*dt; q3 += qDot4*dt;

  recipNorm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  q0*=recipNorm; q1*=recipNorm; q2*=recipNorm; q3*=recipNorm;
}


bool readAndProcessIMU(IMUData &d) {
  unsigned long t0 = micros();

  myIMU.readSensor();
  xyzFloat a, g, m;
  myIMU.getGValues(&a);
  myIMU.getGyrValues(&g);
  myIMU.getMagValues(&m);

  // Validar que los datos no sean NaN/inf
  if (!isfinite(a.x) || !isfinite(g.x) || !isfinite(m.x)) {
    d.valid = false;
    val.imu_reads_total++;
    return false;
  }

  d.ax = a.x; d.ay = a.y; d.az = a.z;
  d.gx = g.x; d.gy = g.y; d.gz = g.z;

  float cx = (m.x - mag_offset_x) * mag_scale_x;
  float cy = (m.y - mag_offset_y) * mag_scale_y;
  float cz = (m.z - mag_offset_z) * mag_scale_z;
  d.mx = cx; d.my = cy; d.mz = cz;

  // Alineación de ejes AK09916
  float mx_al =  cy;
  float my_al =  cx;
  float mz_al = -cz;

  // dt desde último ciclo (en segundos)
  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicros) * 1e-6f;
  lastMicros = nowUs;
  if (dt <= 0.0f) dt = 1e-3f;
  if (dt > 0.05f) dt = 0.05f;

  // Gyro a rad/s para Madgwick
  float gxR = g.x * PI / 180.0f;
  float gyR = g.y * PI / 180.0f;
  float gzR = g.z * PI / 180.0f;

  madgwickUpdate(gxR, gyR, gzR, a.x, a.y, a.z, mx_al, my_al, mz_al, dt);

  // Cuaternión → Euler
  float sinr_cosp = 2.0f*(q0*q1 + q2*q3);
  float cosr_cosp = 1.0f - 2.0f*(q1*q1 + q2*q2);
  d.roll = atan2f(sinr_cosp, cosr_cosp) * 180.0f / PI;

  float sinp = 2.0f*(q0*q2 - q3*q1);
  if (fabsf(sinp) >= 1.0f)
    d.pitch = copysignf(90.0f, sinp);
  else
    d.pitch = asinf(sinp) * 180.0f / PI;

  float siny_cosp = 2.0f*(q0*q3 + q1*q2);
  float cosy_cosp = 1.0f - 2.0f*(q2*q2 + q3*q3);
  d.yaw = atan2f(siny_cosp, cosy_cosp) * 180.0f / PI;

  d.valid = true;

  // ── Validación de tiempo [C] Process/Calculate < 5 ms ──
  float elapsed_ms = (micros() - t0) / 1000.0f;
  if (elapsed_ms > val.madgwick_max_ms) val.madgwick_max_ms = elapsed_ms;
  if (elapsed_ms > 5.0f) val.imu_process_time_violations++;

  val.imu_reads_total++;
  val.imu_reads_valid++;
  return true;
}

bool readAndProcessGPS(GPSData &d) {
  unsigned long t0 = millis();

  // Leer bytes disponibles hasta agotar el timeout de 5 ms [C]
  while (Serial2.available() && (millis() - t0) < GPS_UART_TIMEOUT_MS) {
    gps.encode(Serial2.read());
  }

  // Detectar violación de timeout (si Serial2 aún tiene datos al salir)
  if (Serial2.available() && (millis() - t0) >= GPS_UART_TIMEOUT_MS) {
    val.gps_uart_timeout_violations++;
  }

  val.gps_reads_total++;

  if (!gps.location.isValid()) {
    d.valid = false;
    return false;
  }

  d.valid      = true;
  d.lat        = gps.location.lat();
  d.lon        = gps.location.lng();
  d.satellites = gps.satellites.isValid() ? gps.satellites.value() : 0;
  d.hdop       = gps.hdop.isValid()       ? gps.hdop.hdop()        : 99.9f;
  d.altitude_m = gps.altitude.isValid()   ? gps.altitude.meters()  : 0.0f;
  d.speed_kmh  = gps.speed.isValid()      ? gps.speed.kmph()       : 0.0f;

  d.hasTime = gps.date.isValid() && gps.time.isValid();
  if (d.hasTime) {
    d.hour = gps.time.hour(); d.minute = gps.time.minute();
    d.second = gps.time.second();
    d.day = gps.date.day(); d.month = gps.date.month();
    d.year = gps.date.year();
  }

  val.gps_reads_valid++;
  return true;
}


void printSensorData() {


  // ── GPS ──
  Serial.println(F("── GPS ──"));
  if (gpsData.valid) {
    Serial.print(F("  Lat:      ")); Serial.println(gpsData.lat, 6);
    Serial.print(F("  Lon:      ")); Serial.println(gpsData.lon, 6);
    Serial.print(F("  Alt (m):  ")); Serial.println(gpsData.altitude_m, 1);
    Serial.print(F("  Vel km/h: ")); Serial.println(gpsData.speed_kmh, 2);
    Serial.print(F("  Sats:     ")); Serial.println(gpsData.satellites);
    Serial.print(F("  HDOP:     ")); Serial.println(gpsData.hdop, 2);
    if (gpsData.hasTime) {
      Serial.print(F("  UTC:      "));
      print2(gpsData.hour); Serial.print(':');
      print2(gpsData.minute); Serial.print(':');
      print2(gpsData.second);
      Serial.print(F("  "));
      print2(gpsData.day); Serial.print('/');
      print2(gpsData.month); Serial.print('/');
      Serial.println(gpsData.year);
    }
  } else {
    Serial.println(F("  [SIN FIX] Esperando señal GPS..."));
    Serial.print(F("  Chars procesados: "));
    Serial.println(gps.charsProcessed());
  }

  // ── IMU ──
  Serial.println(F("── IMU ──"));
  if (imuData.valid) {
    Serial.print(F("  Accel (g):   "));
    Serial.print(imuData.ax, 3); Serial.print(F(", "));
    Serial.print(imuData.ay, 3); Serial.print(F(", "));
    Serial.println(imuData.az, 3);

    Serial.print(F("  Gyro (dps):  "));
    Serial.print(imuData.gx, 3); Serial.print(F(", "));
    Serial.print(imuData.gy, 3); Serial.print(F(", "));
    Serial.println(imuData.gz, 3);

    Serial.print(F("  Mag (µT):    "));
    Serial.print(imuData.mx, 2); Serial.print(F(", "));
    Serial.print(imuData.my, 2); Serial.print(F(", "));
    Serial.println(imuData.mz, 2);

    Serial.print(F("  Roll:  ")); Serial.print(imuData.roll, 2);  Serial.println(F(" °"));
    Serial.print(F("  Pitch: ")); Serial.print(imuData.pitch, 2); Serial.println(F(" °"));
    Serial.print(F("  Yaw:   ")); Serial.print(imuData.yaw, 2);   Serial.println(F(" °"));
  } else {
    Serial.println(F("  [ERROR] IMU no respondió."));
  }
}

void printValidationReport() {

  // GPS
  Serial.print(F("  [GPS] Lecturas totales:         ")); Serial.println(val.gps_reads_total);
  Serial.print(F("  [GPS] Lecturas válidas:         ")); Serial.println(val.gps_reads_valid);
  Serial.print(F("  [GPS] Violaciones timeout UART: ")); Serial.println(val.gps_uart_timeout_violations);
  bool gpsOK = (val.gps_uart_timeout_violations == 0);
  Serial.print(F("  [GPS] [C] UART timeout ≤5ms:    ")); 

  // IMU
  Serial.print(F("  [IMU] Lecturas totales:         ")); Serial.println(val.imu_reads_total);
  Serial.print(F("  [IMU] Lecturas válidas:         ")); Serial.println(val.imu_reads_valid);
  Serial.print(F("  [IMU] Violaciones tiempo >5ms:  ")); Serial.println(val.imu_process_time_violations);
  Serial.print(F("  [IMU] Tiempo máx. Madgwick(ms): ")); Serial.println(val.madgwick_max_ms, 3);
  bool imuOK = (val.imu_process_time_violations == 0);
  Serial.print(F("  [IMU] [C] Process < 5ms:        ")); 

  // Loop timing
  Serial.print(F("  [LOOP] Ciclos totales:          ")); Serial.println(val.loop_cycles);
  Serial.print(F("  [LOOP] Violaciones >200ms:      ")); Serial.println(val.loop_timing_violations);
  Serial.print(F("  [LOOP] dt máx. (ms):            ")); Serial.println(val.loop_max_dt_ms, 1);
  bool loopOK = (val.loop_timing_violations == 0);
  Serial.print(F("  [LOOP] [C] Ciclo a 5 Hz:        ")); 

  bool allOK = gpsOK && imuOK && loopOK;
  Serial.print(F("  RESULTADO GENERAL:              "));
  Serial.println(allOK ? F("Sistema conforme al MBSE")
                       : F("Ver violaciones arriba"));
  Serial.println();
}



void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000) {}


  // ── Iniciar GPS ──
  Serial.println(F("[GPS] Iniciando Serial2..."));
  Serial2.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  delay(100);
  Serial.println(F("[GPS] Serial2 listo @ 9600 baud.\n"));

  // ── Iniciar I2C ──
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(400000);
#if defined(ARDUINO_ARCH_ESP32)
  Wire.setTimeOut(50);
#endif

  // ── Iniciar IMU ──
  Serial.println(F("[IMU] Inicializando ICM-20948..."));
  if (!myIMU.init()) {
    Serial.println(F("[ERROR] ICM-20948 no responde. Revisa I2C/dirección."));
    while (1) delay(100);
  }
  Serial.println(F("[IMU] ICM-20948 OK"));

  if (!myIMU.initMagnetometer()) {
    Serial.println(F("[ERROR] AK09916 (magnetómetro) no responde."));
    while (1) delay(100);
  }
  Serial.println(F("[IMU] AK09916 OK\n"));

  applyIMUConfig();
  delay(100);

  calibrateGyroAtStart();
  initQuaternionFromSensors();

  // ── Inicializar contadores de validación ──
  memset(&val, 0, sizeof(val));

  // ── Inicializar relojes ──
  lastMicros  = micros();
  lastLoopMs  = millis();
  lastPrintMs = millis();

}


void loop() {
  unsigned long nowMs = millis();

  // ── Control de frecuencia 5 Hz [C] ──
  unsigned long dt_loop = nowMs - lastLoopMs;
  if (dt_loop < LOOP_PERIOD_MS) return;  // Esperar sin bloquear

  // Medir timing real del ciclo
  if (dt_loop > val.loop_max_dt_ms) val.loop_max_dt_ms = (float)dt_loop;
  if (dt_loop > LOOP_PERIOD_MS + 10) val.loop_timing_violations++;  // Tolerancia 10 ms

  lastLoopMs = nowMs;
  val.loop_cycles++;

  // ── [P] Read GPS + Process GPS ── [Variable Getter Template]
  readAndProcessGPS(gpsData);

  // ── [P] Read IMU + Process IMU + Calculate pitch/roll/yaw ── [Variable Getter Template]
  readAndProcessIMU(imuData);

  // ── Collect measurements: imprimir datos ──
  if (nowMs - lastPrintMs >= PRINT_PERIOD_MS) {
    lastPrintMs = nowMs;
    printSensorData();
    printValidationReport();
  }
}
