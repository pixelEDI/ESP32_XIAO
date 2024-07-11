/*
        _          _ ______ _____ _____
       |_|        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

https://links.pixeledi.eu
Webserver | V1.0 | 05.2024
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "credentials.h"
#include <ESPmDNS.h>
#include <LittleFS.h>

WebServer server(80);

const byte led = 10;

unsigned long previousMillis = 0;
String webserverText = "Warte auf Input";
bool updateText = false;

void handleMillis()
{
  String millisStr = String(millis()/1000);
  server.send(200, "text/plain", millisStr);
}

void handleRoot()
{
  File file = LittleFS.open("/index.html", "r");
  if (!file)
  {
    server.send(404, "text/plain", "File not found");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void setup()
{
  Serial.begin(115200);

  if (!LittleFS.begin())
  {
    Serial.println("LittleFS mount failed");
    return;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (!MDNS.begin("laufzeit"))
  { // laufzeit.local im Browser
    Serial.println("Error setting up mDNS.");
  }

  MDNS.addService("http", "tcp", 80); 

  server.on("/", handleRoot);
  server.on("/millis", handleMillis);
  server.begin();
  Serial.println("Server ist online!");
}

void loop()
{
  server.handleClient();

}
