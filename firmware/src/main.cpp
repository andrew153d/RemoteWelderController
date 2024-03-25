#include <Arduino.h>
#include "WiFi.h"
#include <ArduinoOTA.h>
#include <WebServer.h>


WebServer server(80);

String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

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
}

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
  digitalWrite(13, (int)(millis()/1000)%2);
}
