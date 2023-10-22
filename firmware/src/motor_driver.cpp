#include "Arduino.h"
#include "motor_driver.h"
#include "config.h"
#include <AccelStepper.h>
#include <esp_now.h>
#include "WiFi.h"

float motorTarget = -1;
float receivedTarget = -1;
bool isEnabled = false;

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
    // Serial.print("Bytes received: ");
    // Serial.println(len);
    int pot;
    memcpy(&pot, incomingData, len);
    float f_pot = pot;
    f_pot = map(pot, 0, 4096, 0, RANGE);
    receivedTarget = f_pot;
}

void motor_driver_task()
{
    pinMode(STATUS_LED, OUTPUT);

    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);
    pinMode(MS3, OUTPUT);
    pinMode(SLEEP, OUTPUT);
    pinMode(RST, OUTPUT);
    pinMode(ENABLE, OUTPUT);
    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);

    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
    digitalWrite(MS3, LOW);

    digitalWrite(SLEEP, HIGH);
    digitalWrite(RST, HIGH);
    digitalWrite(ENABLE, LOW);

    digitalWrite(DIR, LOW);

    AccelStepper stepper(AccelStepper::DRIVER, STEP, DIR);
    uint8_t controllerAddress[] = {0x34, 0x98, 0x7A, 0x79, 0x34, 0xE8};

    WiFi.mode(WIFI_MODE_STA);
    Serial.println(WiFi.macAddress());

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register peer
    esp_now_peer_info_t peerInfo  = {};
    memcpy(peerInfo.peer_addr, controllerAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    // Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(OnDataRecv);

    stepper.setMaxSpeed(MAX_SPEED);
    stepper.setAcceleration(ACCEL);

    while (motorTarget == -1)
    {
        if (receivedTarget != -1)
        {
            motorTarget = receivedTarget;
            stepper.setCurrentPosition(receivedTarget);
            Serial.println("got first message");
        }
        Serial.println("waitin");
    }

    while (1)
    {
        motorTarget = ALPHA * receivedTarget + (1 - ALPHA) * motorTarget;

        stepper.moveTo(motorTarget);
        if (abs(stepper.currentPosition() - stepper.targetPosition()) > MIN_ERROR_FOR_MOVEMENT)
        {
            if (!isEnabled)
            {
                digitalWrite(ENABLE, LOW);
                isEnabled = true;
            }
            stepper.run();
        }
        else
        {
            if (isEnabled)
            {
                isEnabled = false;
                digitalWrite(ENABLE, HIGH);
            }
        }
    }
}