#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>

Adafruit_MPU6050 mpu;

// Variables de orientación
float pitch = 0.0, roll = 0.0, yaw = 0.0;
float gyroYawBias = 0.0; // Sesgo del giroscopio en Yaw

// Parámetro del Filtro Complementario (ajustable)
const float alpha = 0.98;

// Variables de tiempo
uint32_t lastUpdateTime = 0;
float deltaTime;

// Estructura para almacenar datos del sensor
struct SensorData {
    float ax, ay, az;
    float gx, gy, gz;
};

// ------------------------- SETUP -------------------------
void setup() {
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(400000);
    
    if (!mpu.begin()) {
        Serial.println("Error: No se pudo inicializar el MPU6050");
        while (1);
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    
    calibrateGyro();
    lastUpdateTime = millis();
}

// ------------------------- LOOP PRINCIPAL -------------------------
void loop() {
    SensorData data = readSensorData();
    computeOrientation(data);
    printOrientation();
    delay(20);
}

// ------------------------- CALIBRACIÓN -------------------------
void calibrateGyro() {
    Serial.println("Calibrando giroscopio...");
    float sum = 0.0;
    int numSamples = 500;

    for (int i = 0; i < numSamples; i++) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        sum += g.gyro.z; // Sesgo en Z (Yaw)
        delay(3);
    }
    
    gyroYawBias = sum / numSamples;
    Serial.print("Sesgo del giroscopio en Yaw: ");
    Serial.println(gyroYawBias, 6);
}

// ------------------------- LECTURA DEL SENSOR -------------------------
SensorData readSensorData() {
    sensors_event_t a, g, temp;

    if (!mpu.getEvent(&a, &g, &temp)) {
        Serial.println("⚠️ ERROR: No se pudo leer el sensor.");
        delay(100);
        return {0, 0, 0, 0, 0, 0};
    }

    uint32_t currentTime = millis();
    deltaTime = (currentTime - lastUpdateTime) / 1000.0;
    lastUpdateTime = currentTime;

    return { a.acceleration.x, a.acceleration.y, a.acceleration.z, 
             g.gyro.x, g.gyro.y, g.gyro.z - gyroYawBias };
}

// ------------------------- CÁLCULO DE ORIENTACIÓN -------------------------
void computeOrientation(SensorData data) {
    // 1. Calcular ángulos con el acelerómetro
    float pitchAcc = atan2(-data.ax, sqrt(data.ay * data.ay + data.az * data.az)) * 180 / PI;
    float rollAcc = atan2(data.ay, data.az) * 180 / PI;

    // 2. Integración del giroscopio para estimar ángulos
    float pitchGyro = pitch + data.gy * deltaTime;
    float rollGyro = roll + data.gx * deltaTime;

    // 3. Filtro Complementario
    pitch = alpha * pitchGyro + (1 - alpha) * pitchAcc;
    roll = alpha * rollGyro + (1 - alpha) * rollAcc;

    // 4. Integración para el Yaw
    yaw += data.gz * deltaTime;
    if (yaw > 360) yaw -= 360;
    if (yaw < -360) yaw += 360;
}

// ------------------------- IMPRIMIR ORIENTACIÓN -------------------------
void printOrientation() {
    Serial.print("Yaw: ");
    Serial.print(yaw, 2);
    Serial.print(", Pitch: ");
    Serial.print(pitch, 2);
    Serial.print(", Roll: ");
    Serial.print(roll, 2);
    Serial.println(" deg");
    Serial.println("------------------------------------------------------");
}
