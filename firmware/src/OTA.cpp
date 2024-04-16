
#include "OTA.h"

void activateWifiBootloader()
{
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
}

void ota_loop(){
    ArduinoOTA.handle();
}