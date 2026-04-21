/***************************************************************************
 * Microcontrolador: XIAO ESP32-S3
 * Librería: ICM20948_WE 
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
// - BETA alto (ej: 0.5) → accel+mag corrigen rápido, pero añaden ruido
// - BETA bajo (ej: 0.033) → respuesta suave pero corrige drift lentamente
// - 0.1 es un buen compromiso para uso general
const float MADGWICK_BETA = 0.1f;

// Número de muestras que tomamos al arrancar para calibrar el giroscopio.
// 500 muestras × 3 ms cada una = ~1.5 segundos de calibración.
const uint16_t GYR_CALIB_SAMPLES = 500;

// ========================================================================
// ====================== OBJETO DEL SENSOR ===============================
// ========================================================================

// Creamos un objeto "myIMU" que representa al sensor. La librería se encarga
// de toda la comunicación I2C por debajo.
ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);

// ========================================================================
// ====================== VARIABLES DE ESTADO =============================
// ========================================================================

// CUATERNIÓN: representación matemática de la orientación en 3D.
// Son 4 números (q0, q1, q2, q3) que describen una rotación sin sufrir
// gimbal lock (problema matemático con ángulos de Euler cerca de ±90°).
// Valor inicial (1, 0, 0, 0) = "sin rotación" (orientación de referencia).
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;

// Ángulos de Euler finales, en grados, que es lo que imprimimos al usuario.
// Se calculan a partir del cuaternión.
float roll_deg = 0.0f, pitch_deg = 0.0f, yaw_deg = 0.0f;

// Variables de tiempo:
// - lastMicros: para calcular dt (tiempo transcurrido entre una lectura y la siguiente)
// - lastPrintMs: para saber cuándo toca imprimir de nuevo
unsigned long lastMicros = 0;
unsigned long lastPrintMs = 0;

// Offsets (corrección de cero) del magnetómetro → compensan "hard-iron" (imanes
// cercanos, tornillos metálicos). Por defecto a 0; deberían calcularse con un
// sketch de calibración aparte.
float mag_offset_x = 0.0f, mag_offset_y = 0.0f, mag_offset_z = 0.0f;

// Escalas del magnetómetro → compensan "soft-iron" (distorsiones de metales
// blandos). Por defecto a 1 (sin corrección).
float mag_scale_x  = 1.0f, mag_scale_y  = 1.0f, mag_scale_z  = 1.0f;

// ========================================================================
// ====================== FUNCIONES AUXILIARES ============================
// ========================================================================

// Calcula 1/sqrt(x) muy rápido usando un truco de bits famoso del juego Quake.
// Es menos preciso que 1.0f/sqrtf(x) pero unas 4 veces más rápido.
// El filtro Madgwick lo necesita muchas veces por ciclo, así que vale la pena.
static inline float invSqrt(float x) {
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;              // Interpretar el float como entero
  i = 0x5f3759df - (i >> 1);        // Magia de bits: aproximación inicial
  y = *(float*)&i;                  // Volver a interpretarlo como float
  y = y * (1.5f - (halfx * y * y)); // Una iteración de Newton para refinar
  return y;
}

// ========================================================================
// ====================== CONFIGURACIÓN DEL IMU ===========================
// ========================================================================

void applyIMUConfig() {
  // ----- ACELERÓMETRO -----
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);    // Rango de medición: ±2g
                                                 // (mejor resolución para orientación estática)
  myIMU.setAccDLPF(ICM20948_DLPF_6);             // Filtro digital paso-bajo nivel 6
                                                 // (reduce ruido de alta frecuencia)
  myIMU.setAccSampleRateDivider(10);             // Divisor de tasa de muestreo → ~100 Hz

  // ----- GIROSCOPIO -----
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);    // Rango: ±250 grados/segundo
                                                 // (mejor resolución angular)
  myIMU.setGyrDLPF(ICM20948_DLPF_6);             // Filtro digital paso-bajo
  myIMU.setGyrSampleRateDivider(10);             // ~100 Hz

  // ----- SENSOR DE TEMPERATURA -----
  myIMU.setTempDLPF(ICM20948_DLPF_6);            // (no lo usamos, pero se configura)

  // ----- MAGNETÓMETRO -----
  myIMU.setMagOpMode(AK09916_CONT_MODE_100HZ);   // Modo continuo a 100 Hz
                                                 // (toma muestras automáticamente)
}

// ========================================================================
// ====================== CALIBRACIÓN DEL GIROSCOPIO ======================
// ========================================================================
// El giroscopio, incluso perfectamente quieto, reporta valores muy pequeños
// distintos de cero (sesgo/bias). Si no los restamos, ese error se integra
// con el tiempo y los ángulos derivan solos. Solución: promediar muchas
// lecturas con el sensor quieto y usar ese promedio como "cero real".

void calibrateGyroAtStart() {
  Serial.println(F("==================================================="));
  Serial.println(F("CALIBRACIÓN DE GIROSCOPIO"));
  Serial.println(F("Mantén el sensor COMPLETAMENTE QUIETO..."));
  Serial.println(F("==================================================="));
  delay(2000);  // Damos 2 segundos al usuario para dejar el sensor quieto

  // Acumuladores en double (64 bits) para no perder precisión al sumar muchas lecturas
  double sx = 0, sy = 0, sz = 0;
  xyzFloat g;  // Estructura temporal para una lectura de gyro (x, y, z)

  // Tomamos 500 muestras
  for (uint16_t i = 0; i < GYR_CALIB_SAMPLES; i++) {
    myIMU.readSensor();       // Lee TODOS los sensores del chip
    myIMU.getGyrValues(&g);   // Extrae solo el giroscopio a la variable g
    sx += g.x;                // Acumulamos cada eje
    sy += g.y;
    sz += g.z;
    delay(3);                 // Pequeña pausa entre muestras (total ≈ 1.5 s)
    if (i % 50 == 0) Serial.print('.');  // Visualización de progreso
  }
  Serial.println();

  // Promedio = suma / cantidad → este es el sesgo de cada eje
  float ox = (float)(sx / GYR_CALIB_SAMPLES);
  float oy = (float)(sy / GYR_CALIB_SAMPLES);
  float oz = (float)(sz / GYR_CALIB_SAMPLES);

  // Le decimos a la librería: "a partir de ahora, resta estos valores a cada lectura"
  // Se pasan en negativo porque la librería los SUMA (y queremos restarlos).
  myIMU.setGyrOffsets(-ox, -oy, -oz);

  // Imprimimos los offsets (útil para depurar y para saber si hay un problema)
  Serial.print(F("Offsets gyro (dps): "));
  Serial.print(ox, 4); Serial.print(", ");
  Serial.print(oy, 4); Serial.print(", ");
  Serial.println(oz, 4);
  Serial.println(F("Calibración completada.\n"));
}

// ========================================================================
// ====================== INICIALIZACIÓN DEL CUATERNIÓN ===================
// ========================================================================
// Si arrancáramos con q = (1,0,0,0) (orientación "neutra"), el filtro tardaría
// unos segundos en converger a la orientación real. Para que arranque ya
// reflejando la posición física del sensor, calculamos roll/pitch/yaw iniciales
// a partir de accel+mag y construimos el cuaternión correspondiente.

void initQuaternionFromSensors() {
  Serial.println(F("Estableciendo orientación inicial..."));
  delay(200);

  xyzFloat a, m;  // Estructuras para accel y mag

  // Acumuladores para promediar 50 muestras (reduce ruido puntual)
  float ax_sum = 0, ay_sum = 0, az_sum = 0;
  float mx_sum = 0, my_sum = 0, mz_sum = 0;
  const int N = 50;

  // Tomamos N muestras
  for (int i = 0; i < N; i++) {
    myIMU.readSensor();
    myIMU.getGValues(&a);    // Accel en unidades de "g" (1g = 9.81 m/s²)
    myIMU.getMagValues(&m);  // Mag en microteslas (µT)
    ax_sum += a.x; ay_sum += a.y; az_sum += a.z;
    mx_sum += m.x; my_sum += m.y; mz_sum += m.z;
    delay(10);
  }

  // Promedios
  float ax = ax_sum / N, ay = ay_sum / N, az = az_sum / N;

  // Aplicamos calibración hard-iron y soft-iron al magnetómetro (si existiera)
  float mx = (mx_sum / N - mag_offset_x) * mag_scale_x;
  float my = (my_sum / N - mag_offset_y) * mag_scale_y;
  float mz = (mz_sum / N - mag_offset_z) * mag_scale_z;

  // CORRECCIÓN DE EJES DEL MAGNETÓMETRO:
  // El magnetómetro AK09916 tiene sus ejes rotados respecto al accel/gyro.
  // Según el datasheet (Figure 12 vs 13): Mx(chip) = My(mag), etc.
  float mx_a =  my;
  float my_a =  mx;
  float mz_a = -mz;

  // ---- Calcular Roll y Pitch a partir del vector gravedad ----
  // Cuando el sensor está quieto, el acelerómetro mide g hacia abajo.
  // La inclinación del vector gravedad nos dice cómo está orientado el sensor.
  float roll0  = atan2f(ay, az);                         // Rotación alrededor del eje X
  float pitch0 = atan2f(-ax, sqrtf(ay * ay + az * az));  // Rotación alrededor del eje Y

  // ---- Calcular Yaw a partir del campo magnético, compensando la inclinación ----
  // Si solo usáramos mx, my crudos, el Yaw cambiaría al inclinar el sensor.
  // Hay que "rotar" el campo mag al plano horizontal primero.
  float cosR = cosf(roll0),  sinR = sinf(roll0);
  float cosP = cosf(pitch0), sinP = sinf(pitch0);

  // Proyección del vector magnético al plano horizontal
  float mxh = mx_a * cosP + my_a * sinR * sinP + mz_a * cosR * sinP;
  float myh = my_a * cosR - mz_a * sinR;

  // Yaw = ángulo del vector horizontal respecto al norte magnético
  float yaw0 = atan2f(-myh, mxh);

  // ---- Convertir los 3 ángulos de Euler al cuaternión inicial ----
  // Fórmula estándar: cuaternión como producto de 3 rotaciones (roll, pitch, yaw)
  float cy = cosf(yaw0 * 0.5f);
  float sy = sinf(yaw0 * 0.5f);
  float cp = cosf(pitch0 * 0.5f);
  float sp = sinf(pitch0 * 0.5f);
  float cr = cosf(roll0 * 0.5f);
  float sr = sinf(roll0 * 0.5f);

  q0 = cr * cp * cy + sr * sp * sy;   // componente real
  q1 = sr * cp * cy - cr * sp * sy;   // componente i (eje X)
  q2 = cr * sp * cy + sr * cp * sy;   // componente j (eje Y)
  q3 = cr * cp * sy - sr * sp * cy;   // componente k (eje Z)

  // Imprimimos la orientación inicial detectada
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
// Corazón del algoritmo. Cada llamada:
//  1) Integra el giroscopio en el cuaternión (predicción)
//  2) Calcula el error respecto a accel+mag (corrección)
//  3) Aplica una pequeña corrección al cuaternión (ganancia BETA)
//
// Parámetros:
//  - gx,gy,gz: velocidad angular en rad/s
//  - ax,ay,az: aceleración (cualquier unidad, se normaliza)
//  - mx,my,mz: campo magnético (cualquier unidad, se normaliza)
//  - dt: tiempo transcurrido desde la última llamada (segundos)

void madgwickUpdate(float gx, float gy, float gz,
                    float ax, float ay, float az,
                    float mx, float my, float mz,
                    float dt) {
  // Variables locales para los cálculos
  float recipNorm;
  float s0, s1, s2, s3;               // Gradiente de corrección
  float qDot1, qDot2, qDot3, qDot4;   // Derivada del cuaternión
  float hx, hy;                        // Campo mag proyectado al marco de tierra
  float _2q0mx, _2q0my, _2q0mz, _2q1mx;
  float _2bx, _2bz, _4bx, _4bz;        // Dirección de referencia del campo mag
  float _2q0, _2q1, _2q2, _2q3;
  float _2q0q2, _2q2q3;
  float q0q0, q0q1, q0q2, q0q3;
  float q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;

  // ---- PASO 1: Derivada del cuaternión desde el giroscopio ----
  // Fórmula estándar de cinemática de cuaterniones:
  // q̇ = 0.5 · q ⊗ ω   (donde ω es el vector de velocidad angular)
  qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
  qDot2 = 0.5f * ( q0 * gx + q2 * gz - q3 * gy);
  qDot3 = 0.5f * ( q0 * gy - q1 * gz + q3 * gx);
  qDot4 = 0.5f * ( q0 * gz + q1 * gy - q2 * gx);

  // Solo hacemos corrección si las medidas de accel y mag son válidas (no cero)
  if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)) &&
      !((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))) {

    // ---- PASO 2: Normalizar vectores ----
    // Solo nos importa la DIRECCIÓN del vector gravedad/magnético, no su magnitud.
    recipNorm = invSqrt(ax * ax + ay * ay + az * az);
    ax *= recipNorm; ay *= recipNorm; az *= recipNorm;

    recipNorm = invSqrt(mx * mx + my * my + mz * mz);
    mx *= recipNorm; my *= recipNorm; mz *= recipNorm;

    // ---- PASO 3: Variables auxiliares precalculadas ----
    // Para no repetir multiplicaciones muchas veces (optimización)
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

    // ---- PASO 4: Estimar la dirección de referencia del campo magnético ----
    // Rotamos el vector magnético medido al "marco de tierra" usando el cuaternión actual.
    // Esto nos dice hacia dónde debería apuntar el norte magnético desde donde está
    // el sensor ahora mismo. Usamos solo la componente horizontal (_2bx) y vertical (_2bz).
    hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1
       + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
    hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2
       - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
    _2bx = sqrtf(hx * hx + hy * hy);   // Magnitud horizontal del norte
    _2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3
         - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
    _4bx = 2.0f * _2bx;
    _4bz = 2.0f * _2bz;

    // ---- PASO 5: Calcular el gradiente de la función de error ----
    // Esto es la parte "matemáticamente densa" del filtro Madgwick.
    // En esencia: "¿cuánto hay que ajustar el cuaternión para que la gravedad estimada
    // coincida con la medida, y el norte magnético estimado coincida con el medido?"
    // s0, s1, s2, s3 es la dirección en la que hay que moverse (el gradiente).
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

    // Normalizar el gradiente (queremos solo la DIRECCIÓN de la corrección)
    recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);
    s0 *= recipNorm; s1 *= recipNorm; s2 *= recipNorm; s3 *= recipNorm;

    // ---- PASO 6: Aplicar la corrección con ganancia BETA ----
    // Restamos al giroscopio integrado la corrección proporcional a BETA.
    // BETA alto = más corrección (más peso a accel/mag).
    qDot1 -= MADGWICK_BETA * s0;
    qDot2 -= MADGWICK_BETA * s1;
    qDot3 -= MADGWICK_BETA * s2;
    qDot4 -= MADGWICK_BETA * s3;
  }

  // ---- PASO 7: Integrar la derivada del cuaternión (Euler explícito) ----
  // q(t+dt) = q(t) + q̇ · dt
  q0 += qDot1 * dt;
  q1 += qDot2 * dt;
  q2 += qDot3 * dt;
  q3 += qDot4 * dt;

  // ---- PASO 8: Normalizar el cuaternión ----
  // Los cuaterniones que representan rotaciones deben tener magnitud 1.
  // Por errores numéricos se va alejando de 1, así que lo renormalizamos cada ciclo.
  recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
  q0 *= recipNorm; q1 *= recipNorm; q2 *= recipNorm; q3 *= recipNorm;
}

// ========================================================================
// ====================== CUATERNIÓN → ÁNGULOS EULER ======================
// ========================================================================
// Convierte el cuaternión (q0, q1, q2, q3) a Roll, Pitch y Yaw en grados.
// Fórmulas estándar, se pueden consultar en Wikipedia ("Conversion between
// quaternions and Euler angles").

void quaternionToEuler() {
  // ---- ROLL (rotación alrededor del eje X) → rango ±180° ----
  float sinr_cosp = 2.0f * (q0 * q1 + q2 * q3);
  float cosr_cosp = 1.0f - 2.0f * (q1 * q1 + q2 * q2);
  roll_deg = atan2f(sinr_cosp, cosr_cosp) * 180.0f / PI;

  // ---- PITCH (rotación alrededor del eje Y) → rango ±90° ----
  float sinp = 2.0f * (q0 * q2 - q3 * q1);
  if (fabsf(sinp) >= 1.0f)
    // Si sinp llega a ±1, estamos en gimbal lock → forzar pitch a ±90°
    pitch_deg = copysignf(90.0f, sinp);
  else
    pitch_deg = asinf(sinp) * 180.0f / PI;

  // ---- YAW (rotación alrededor del eje Z) → rango ±180° ----
  float siny_cosp = 2.0f * (q0 * q3 + q1 * q2);
  float cosy_cosp = 1.0f - 2.0f * (q2 * q2 + q3 * q3);
  yaw_deg = atan2f(siny_cosp, cosy_cosp) * 180.0f / PI;
}

// ========================================================================
// ====================== SETUP (se ejecuta una vez) ======================
// ========================================================================

void setup() {
  Serial.begin(SERIAL_BAUD);
  // Esperamos a que el puerto serie esté listo (máx 3 s para no bloquear)
  while (!Serial && millis() < 3000) {}

  // ---- Iniciar bus I2C ----
  Wire.begin();
  Wire.setClock(400000);        // 400 kHz (modo rápido I2C, soportado por el ICM-20948)
#if defined(ARDUINO_ARCH_ESP32)
  Wire.setTimeOut(50);          // Timeout de 50 ms en caso de fallo de bus
#endif

  Serial.println(F("\n=== ICM-20948 9-DOF Madgwick ==="));

  // ---- Inicializar el sensor principal (accel + gyro) ----
  if (!myIMU.init()) {
    Serial.println(F("ERROR: ICM-20948 no responde. Revisa cableado/direccion."));
    while (1) delay(100);   // Quedarse aquí para siempre (error crítico)
  }
  Serial.println(F("ICM-20948 OK"));

  // ---- Inicializar el magnetómetro (AK09916, chip interno del ICM-20948) ----
  if (!myIMU.initMagnetometer()) {
    Serial.println(F("ERROR: AK09916 (magnetometro) no responde."));
    while (1) delay(100);
  }
  Serial.println(F("AK09916 OK"));

  // Aplicar la configuración (rangos, filtros, ODR, etc.)
  applyIMUConfig();
  delay(100);   // Pequeña pausa para que los cambios surtan efecto

  // ---- Calibración del gyro y cuaternión inicial ----
  calibrateGyroAtStart();
  initQuaternionFromSensors();

  // Inicializamos los relojes para el primer dt del loop
  lastMicros = micros();
  lastPrintMs = millis();
}

// ========================================================================
// ====================== LOOP (se ejecuta sin parar) =====================
// ========================================================================

void loop() {
  // ---- PASO 1: Calcular dt (tiempo transcurrido desde la última iteración) ----
  unsigned long nowUs = micros();
  float dt = (nowUs - lastMicros) * 1e-6f;  // Convertir microsegundos a segundos
  lastMicros = nowUs;

  // Protecciones por si dt es demasiado pequeño o grande (bugs, overflow, etc.)
  if (dt <= 0.0f) dt = 1e-3f;
  if (dt > 0.05f) dt = 0.05f;    // Nunca usar más de 50 ms (evita saltos extraños)

  // ---- PASO 2: Leer los 3 sensores ----
  myIMU.readSensor();           // Lee todos los datos crudos del chip
  xyzFloat a, g, m;
  myIMU.getGValues(&a);         // Accel en g
  myIMU.getGyrValues(&g);       // Gyro en grados/segundo (dps)
  myIMU.getMagValues(&m);       // Mag en microteslas

  // Validación: si algún valor es NaN o inf, saltamos esta iteración
  if (!isfinite(a.x) || !isfinite(g.x) || !isfinite(m.x)) return;

  // ---- PASO 3: Aplicar calibración del magnetómetro ----
  // (Ahora mismo los offsets son 0 y escalas 1, así que no cambia nada,
  // pero cuando hagas la calibración del mag, estos valores cobrarán sentido)
  float mx = (m.x - mag_offset_x) * mag_scale_x;
  float my = (m.y - mag_offset_y) * mag_scale_y;
  float mz = (m.z - mag_offset_z) * mag_scale_z;

  // ---- PASO 4: Convertir gyro de grados/s a radianes/s ----
  // El filtro Madgwick trabaja internamente en radianes.
  float gx = g.x * PI / 180.0f;
  float gy = g.y * PI / 180.0f;
  float gz = g.z * PI / 180.0f;

  // ---- PASO 5: Alinear ejes del magnetómetro con accel/gyro ----
  // Porque en el ICM-20948 el chip del magnetómetro (AK09916) tiene sus ejes
  // orientados distinto que el chip principal. Hay que corregirlo.
  float mx_aligned =  my;
  float my_aligned =  mx;
  float mz_aligned = -mz;

  // ---- PASO 6: Llamar al filtro Madgwick para actualizar el cuaternión ----
  madgwickUpdate(gx, gy, gz,
                 a.x, a.y, a.z,
                 mx_aligned, my_aligned, mz_aligned,
                 dt);

  // ---- PASO 7: Convertir el cuaternión a ángulos Euler ----
  quaternionToEuler();

  // ---- PASO 8: Imprimir cada PRINT_PERIOD_MS milisegundos ----
  // No imprimimos en cada iteración del loop (sería demasiado rápido para leer).
  if (millis() - lastPrintMs >= PRINT_PERIOD_MS) {
    lastPrintMs = millis();
    Serial.print(F("ROLL: "));    Serial.print(roll_deg, 2);
    Serial.print(F(" | PITCH: ")); Serial.print(pitch_deg, 2);
    Serial.print(F(" | YAW: "));   Serial.println(yaw_deg, 2);
  }
}