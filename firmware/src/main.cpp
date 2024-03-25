#include <Arduino.h>
#include "WiFi.h"
#include <ArduinoOTA.h>
#include <WebServer.h>
#include "web_controller.h"

WebServer server(80);


void handle_root();

void setup()
{

  Serial.begin(115200);
  
  pinMode(13, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("WeldConnect", NULL);
  server.on("/", handle_root);
  server.begin();
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

}

void loop()
{
  server.handleClient();
  digitalWrite(13, (int)(millis()/500)%2);
}

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", web_html);
}
