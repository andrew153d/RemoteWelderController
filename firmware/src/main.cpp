#include <Arduino.h>
#include "WiFi.h"
#include "ESPmDNS.h"
#include <ArduinoOTA.h>
#include "config.h"
#include <WebServer.h>
#include "web_controller.h"
#include "esp_wifi.h"
#include "wifi_credentials.h"
#include "gpio.h"
#include "WifiDebug.h"

WebServer server(80);

void handle_root();

void setup()
{
  gpio::init_common_gpio();  

  if(MAKE_AP){
    WiFi.mode(WIFI_AP);
    WiFi.softAP("WeldConnect", NULL);
  }else{
    WiFi.begin(ssid, password);
    int32_t start_time = millis();
    
    while(WiFi.status() != WL_CONNECTED){
      delay(100);
      digitalWrite(gpio::STATUS_LED, (int)(millis()/100)%2);
    }
    //Serial.println("Wifi Connected");
  }
  DEBUG_BEGIN(115200);
  esp_wifi_set_max_tx_power(8);
  int8_t tx_power;
  esp_wifi_get_max_tx_power(&tx_power);
  DEBUG_PRINTF("Low Power: %d", tx_power);

  server.on("/", handle_root);
  server.begin();
  // IPAddress ip = WiFi.localIP();
  // DEBUG_PRINTF("%s", ip.toString());
  if(!MDNS.begin("weldconnect")){
    while(1){
      digitalWrite(gpio::STATUS_LED, (int)(millis()/100)%2);
    }
  }
}

void loop()
{
  server.handleClient();
  digitalWrite(13, (int)(millis()/1000)%2);
}

// Handle root url (/)
void handle_root() {
  DEBUG_PRINT("Sending HTML page");
  server.send_P(200, "text/html", web_html);
}
