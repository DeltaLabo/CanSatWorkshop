#include <ICM20948_WE.h>
#include <Wire.h>
#include <math.h>

#define ICM20948_ADDR 0x68
#define STANDARD_GRAVITY_MPS2 9.80665f
#define DEG_TO_RAD_FACTOR (PI / 180.0f)

ICM20948_WE imu = ICM20948_WE(ICM20948_ADDR);

// Variables de orientación
float pitch = 0.0, roll = 0.0, yaw = 0.0;
float gyroYawBias = 0.0; // Sesgo del giroscopio en Yaw (deg/s)

// Parámetro del Filtro Complementario (ajustable)
const float alpha = 0.98;

// Variables de tiempo
uint32_t lastUpdateTime = 0;
float deltaTime;

// Estructura para almacenar datos del sensor
struct SensorData {
    float ax, ay, az; // m/s^2
    float gx, gy, gz; // deg/s
};

void applyIMUConfig() {
    imu.setAccRange(ICM20948_ACC_RANGE_2G);
    imu.setAccDLPF(ICM20948_DLPF_6);
    imu.setGyrRange(ICM20948_GYRO_RANGE_250);
    imu.setGyrDLPF(ICM20948_DLPF_6);
    imu.setTempDLPF(ICM20948_DLPF_6);
}

// ------------------------- SETUP -------------------------
void setup() {
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(400000);
    
    if (!imu.init()) {
        Serial.println("Error: No se pudo inicializar el ICM20948");
        while (1);
    }

    applyIMUConfig();
    
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
        xyzFloat gyroDps;
        imu.readSensor();
        imu.getGyrValues(&gyroDps);
        sum += gyroDps.z; // Sesgo en Z (Yaw)
        delay(3);
    }
    
    gyroYawBias = sum / numSamples;
    Serial.print("Sesgo del giroscopio en Yaw: ");
    Serial.println(gyroYawBias, 6);
}

// ------------------------- LECTURA DEL SENSOR -------------------------
SensorData readSensorData() {
    xyzFloat accelerationG, gyroDps;

    imu.readSensor();
    imu.getGValues(&accelerationG);
    imu.getGyrValues(&gyroDps);

    uint32_t currentTime = millis();
    deltaTime = (currentTime - lastUpdateTime) / 1000.0;
    lastUpdateTime = currentTime;

    return {
        accelerationG.x * STANDARD_GRAVITY_MPS2,
        accelerationG.y * STANDARD_GRAVITY_MPS2,
        accelerationG.z * STANDARD_GRAVITY_MPS2,
        gyroDps.x,
        gyroDps.y,
        gyroDps.z - gyroYawBias
    };
}

// ------------------------- CÁLCULO DE ORIENTACIÓN -------------------------
void computeOrientation(SensorData data) {
    // 1. Calcular ángulos con el acelerómetro
    float pitchAcc = atan2(-data.ax, sqrt(data.ay * data.ay + data.az * data.az)) * 180 / PI;
    float rollAcc = atan2(data.ay, data.az) * 180 / PI;

    // 2. Integración del giroscopio para estimar ángulos (deg/s -> deg)
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
