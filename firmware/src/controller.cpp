#include "Arduino.h"
#include "controller.h"
#include <esp_now.h>
#include "WiFi.h"
#include "config.h"


void controller_task()
{
  pinMode(STATUS_LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(POT, ANALOG);

  uint8_t broadcastAddress[] = {0x34, 0x98, 0x7A, 0x79, 0x34, 0xD4};

  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }


  int lastPotTime = 0;
  int lastPot = 0;
  bool isActivated = false;
  while (1)
  {
    int value = analogRead(POT);
    ///
    analogWrite(STATUS_LED, map(value, 0, 4095, 255, 0));
    delay(10);

    if (abs(lastPot - value) > 20)
    {
      lastPotTime = millis();
      lastPot = value;
    }

    if (millis() - lastPotTime < 100)
    {

      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&value, sizeof(value));
      Serial.println(value);
      if (result == ESP_OK)
      {
        // Serial.println("Sent with success");
      }
      else
      {
        Serial.print(esp_err_to_name(result));
        Serial.println(" Error sending the data");
      }
    }
  }
}

