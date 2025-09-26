#include <Arduino.h>
#include "FreeRTOS.h"

#include "src/RFM95W/RFM95W.h"

#define MEASUREMENT_PERIOD 2000 // ms
#define QUEUE_SIZE 10

enum class Command {
    STANDBY = 0,
    ON = 1,
    DEPLOY = 2
};

enum class State {
    STANDBY = 0,
    ON = 1,
    DEPLOYED = 2
};

struct MeasurementPayload {
    int pitch;
    int roll;
    int yaw;
    int omega_x;
    int omega_y;
    int omega_z;
    int alpha_x;
    int alpha_y;
    int alpha_z;
    int altitude;
    int temperature;
    int rel_humidity;
    float latitude;
    float longitude;
    int voltage;
    int current;
};

State currentState = State::STANDBY;
QueueHandle_t measurementQueue;
TaskHandle_t communicationTaskHandle;

void IRAM_ATTR lora_dio0_interrupt() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(communicationTaskHandle, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

void StateTransition(Command cmd) {
    switch (cmd) {
        case Command::STANDBY:
            currentState = State::STANDBY;
            break;
        case Command::ON:
            currentState = State::ON;
            break;
        case Command::DEPLOY:
            currentState = State::DEPLOYED;
            break;
    }
}

void MeasurementTask(void *pvParameters) {
    while (true) {
        MeasurementPayload payload;
        // TODO: Leer sensores
        xQueueSend(measurementQueue, &payload, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(MEASUREMENT_PERIOD));
    }
}

void CommunicationTask(void *pvParameters) {
    MeasurementPayload receivedPayload;

    while (true) {
        // Verificar si se recibió un comando
        uint32_t notificationValue = ulTaskNotifyTake(pdTRUE, 0);

        if (notificationValue > 0) {
            int receivedByte = LoRa.read();
            if (receivedByte != -1) {
                Command cmd = static_cast<Command>(receivedByte);
                StateTransition(cmd);
            }
        }

        if (xQueueReceive(measurementQueue, &receivedPayload, pdMS_TO_TICKS(10)) == pdPASS) {
            LoRa.beginPacket();
            // Enviar todo el payload, byte a byte
            LoRa.write((uint8_t *)&receivedPayload, sizeof(MeasurementPayload));
            LoRa.endPacket();
        }
    }
}

byte initPeripherals() {
    byte result = 0;

    if (initRFM95W() != 0) {
        Serial.println("Error iniciando LoRa.");
        result = 1;
    }

    return result;
}

void setup() {
    Serial.begin(115200);

    if (initPeripherals() != 0) {
        while (true) {
            Serial.println("Error iniciando periféricos. El CanSat no iniciará.");
            delay(10000);
        }
    }

    measurementQueue = xQueueCreate(QUEUE_SIZE, sizeof(MeasurementPayload));

    // Tarea de medición de variables, núcleo 0
    xTaskCreatePinnedToCore(
        MeasurementTask,
        "MeasurementTask",
        10000,
        NULL,
        1,
        NULL,
        0
    );

    // Tarea de comunicación, núcleo 1
    xTaskCreatePinnedToCore(
        CommunicationTask,
        "CommunicationTask",
        10000,
        NULL,
        1,
        &communicationTaskHandle,
        1
    );

    // Interrupt de LoRa
    pinMode(LORA_DIO0, INPUT);
    attachInterrupt(digitalPinToInterrupt(LORA_DIO0), lora_dio0_interrupt, RISING);
}

void loop() {}