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
#include "OTA.h"
#include "scripts.h"
#include "styles.h"
#include "battery.h"

WebServer server(80);

void handle_root();
void  handle_js();
void handle_css();
void handle_battery();
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

  activateWifiBootloader();

  server.on("/", handle_root);
  server.on("/scripts.js", handle_js);
  server.on("/styles.css", handle_css);  
  server.on("/battery.html", handle_battery);
  server.begin();
  // IPAddress ip = WiFi.localIP();
  // DEBUG_PRINTF("%s", ip.toString());

  // if(!MDNS.begin("weldconnect")){
  //   while(1){
  //     digitalWrite(gpio::STATUS_LED, (int)(millis()/100)%2);
  //   }
  // }
}

void loop()
{
  server.handleClient();
  digitalWrite(13, (int)(millis()/1000)%2);
  ota_loop();
}

// Handle root url (/)
void handle_root() {
  DEBUG_PRINT("Sending HTML page");
  server.send_P(200, "text/html", web_controller);
}

void handle_js(){
  DEBUG_PRINT("Got reuest for js");
  server.send_P(200, "text/js", scripts);
}

void handle_css(){
  DEBUG_PRINT("Got request for css");
  server.send_P(200, "text/css", styles);
}

void handle_battery(){
  DEBUG_PRINT("Got request for battery.html");
  server.send_P(200, "text/html", battery);
}