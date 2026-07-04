#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "pins.h"
#include "Servo.h"

static const char* BLE_DEVICE_NAME = "PDM-Servo";
static const char* PDM_SERVICE_UUID = "8d0f0e4a-2a9d-4e4f-a24d-4d5f3f4c0a01";
static const char* SERVO_ANGLE_CHARACTERISTIC_UUID = "8d0f0e4a-2a9d-4e4f-a24d-4d5f3f4c0a02";
static const char* STATUS_CHARACTERISTIC_UUID = "8d0f0e4a-2a9d-4e4f-a24d-4d5f3f4c0a03";

Servo PDMServo;
BLEServer* bleServer = nullptr;
BLECharacteristic* servoAngleCharacteristic = nullptr;
BLECharacteristic* statusCharacteristic = nullptr;

int currentServoAngle = 0;
bool deviceConnected = false;
bool oldDeviceConnected = false;

bool isAllowedServoAngle(long angle) {
    return angle == 0 || angle == 90 || angle == 180;
}

bool parseServoAngleCommand(String command, int& angle) {
    command.trim();
    if (command.length() == 0) {
        return false;
    }

    char* end = nullptr;
    long parsedAngle = strtol(command.c_str(), &end, 10);
    if (end == command.c_str() || *end != '\0' || !isAllowedServoAngle(parsedAngle)) {
        return false;
    }

    angle = static_cast<int>(parsedAngle);
    return true;
}

String buildStatus(const char* state) {
    return String("angle=") + String(currentServoAngle) + ";state=" + state;
}

void updateBleStatus(const char* state) {
    if (servoAngleCharacteristic != nullptr) {
        servoAngleCharacteristic->setValue(String(currentServoAngle));
    }

    if (statusCharacteristic != nullptr) {
        statusCharacteristic->setValue(buildStatus(state));
        if (deviceConnected) {
            statusCharacteristic->notify();
        }
    }
}

// This PDM demo accepts open-loop servo angle commands over BLE. The BLE status
// characteristic reports the requested angle/command state only; it is not
// independent deployment confirmation, so OBCC telemetry must not report
// OPEN_CONFIRMED unless real PDM feedback or observer evidence is integrated.
void setServoAngle(int angle, const char* state = "COMMAND_SENT") {
    currentServoAngle = angle;
    PDMServo.write(angle);
    updateBleStatus(state);
}

class PDMServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* server) override {
        (void)server;
        deviceConnected = true;
        Serial.println("BLE client connected");
    }

    void onDisconnect(BLEServer* server) override {
        (void)server;
        deviceConnected = false;
        Serial.println("BLE client disconnected");
    }
};

class ServoAngleCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) override {
        String command(characteristic->getValue().c_str());
        int requestedAngle = 0;

        if (parseServoAngleCommand(command, requestedAngle)) {
            setServoAngle(requestedAngle);
            Serial.print("Servo angle set over BLE: ");
            Serial.println(currentServoAngle);
        } else {
            updateBleStatus("INVALID_COMMAND");
            Serial.print("Rejected BLE servo command: ");
            Serial.println(command);
        }
    }
};

void setupBle() {
    BLEDevice::init(BLE_DEVICE_NAME);

    bleServer = BLEDevice::createServer();
    bleServer->setCallbacks(new PDMServerCallbacks());

    BLEService* service = bleServer->createService(PDM_SERVICE_UUID);

    servoAngleCharacteristic = service->createCharacteristic(
        SERVO_ANGLE_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
    );
    servoAngleCharacteristic->setCallbacks(new ServoAngleCallbacks());

    statusCharacteristic = service->createCharacteristic(
        STATUS_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    statusCharacteristic->addDescriptor(new BLE2902());

    updateBleStatus("READY");
    service->start();

    BLEAdvertising* advertising = bleServer->getAdvertising();
    advertising->addServiceUUID(PDM_SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06);
    advertising->setMinPreferred(0x12);
    advertising->start();
}

void setup() {
    Serial.begin(115200);

    PDMServo.attach(PDM_Servo_Pin);
    setServoAngle(0, "BOOT");

    setupBle();

    Serial.println("PDM servo BLE peripheral started");
    Serial.print("Device name: ");
    Serial.println(BLE_DEVICE_NAME);
    Serial.print("Service UUID: ");
    Serial.println(PDM_SERVICE_UUID);
    Serial.println("Write ASCII 0, 90, or 180 to the servo angle characteristic.");
}

void loop() {
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // Give the BLE stack time to finish the disconnect.
        bleServer->startAdvertising();
        Serial.println("BLE advertising restarted");
        oldDeviceConnected = false;
    }

    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = true;
    }

    delay(20);
}
