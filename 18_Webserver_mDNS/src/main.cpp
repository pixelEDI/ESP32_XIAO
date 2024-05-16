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
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

WebServer server(80);
const byte led = 10;
bool changeLED=false;
int pwmvalue = 0;

void handleRoot_1()
{
  String htmlContent = "<!DOCTYPE html><html lang='de'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>pixelEDI</title></head><body>";
  htmlContent += "<h1>Hallo 🖖</h1>";
  htmlContent += "</body></html>";
  server.send(200, "text/html", htmlContent);
}

void handlesendvalues()
{
  String input = server.arg("inputField");
  Serial.println(input);
  server.sendHeader("Location", "/"); // Weiterleitung zur Startseite
  server.send(303);        
             // 303: See Other - Weiterleitung mit GET-Methode
  pwmvalue = input.toInt();
  changeLED=true;
}

void handleRoot()
{

  String htmlContent = "<!DOCTYPE html><html lang='de'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>pixelEDI</title></head><body>";
  htmlContent += "<h1>Hallo 🖖</h1>";
  htmlContent += "<form method='post' action='/sendvalues'>";
  htmlContent += "<input type='range' min='0' max='255' name='inputField' onchange='updateValue(this.value)'>";
  htmlContent += "<input type='submit' value='Submit'>";
  htmlContent += "</form>";
  htmlContent += "<p>Aktueller Wert: <span id='selectedValue'>0</span></p>";
  htmlContent += "<script>function updateValue(value) { document.getElementById('selectedValue').textContent = value; }</script>";
  htmlContent += "</body></html>";
  server.send(200, "text/html", htmlContent);
}

void handlepixeledi()
{
  server.send(200, "text/plain", "hallo webserver!");
}

void setup()
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32's IP address
  // Serial.print("ESP32 Web Server's IP address: ");
  // Serial.println(WiFi.localIP());

  if (!MDNS.begin("led")) // led.local
  {                       // epaper.local
    Serial.println("Error setting up mDNS.");
  }

  MDNS.addService("http", "tcp", 80);

  server.on("/", handleRoot);
  server.on("/pixeledi", handlepixeledi);
  server.on("/sendvalues", handlesendvalues);

  server.begin();
  Serial.println("server ist online");
}

void loop()
{
  server.handleClient();

  if(changeLED){
    changeLED=false;
    analogWrite(led, pwmvalue);
  }
}