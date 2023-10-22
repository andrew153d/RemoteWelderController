#include <Arduino.h>
#include <AccelStepper.h>
#include <esp_now.h>
#include "WiFi.h"
#include <ArduinoOTA.h>
#include <WebServer.h>
#include "controller.h"
#include "motor_driver.h"
#include "config.h"
void activateWifiBootloader()
{
  const char *ssid = digitalRead(DEVICE_TYPE)?"MotorDriver_BL":"Controller_BL";

  Serial.begin(115200);
  Serial.println("\n[*] Creating AP");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, NULL);
  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());

  pinMode(STATUS_LED, OUTPUT);

  for(int i  = 0; i<10; i++){
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }




  ArduinoOTA.setHostname("Welder_Controller");

  ArduinoOTA
      .onStart([]()
               {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
       })
      .onEnd([]()
             {  })
      .onProgress([](unsigned int progress, unsigned int total)
                  {  })
      .onError([](ota_error_t error)
               {
      Serial.printf("Error[%u]: ", error);
       });

  ArduinoOTA.begin();

  for (;;)
  {
    ArduinoOTA.handle();
  }
}

void setup()
{

  Serial.begin(115200);
  
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(DEVICE_TYPE, INPUT);



  if(!digitalRead(BUTTON))
    activateWifiBootloader();  
  


  if (digitalRead(DEVICE_TYPE))
  {
    // motor driver
    motor_driver_task();
  }
  else
  {
    // controller
    controller_task();
  }
}

void loop()
{
}
