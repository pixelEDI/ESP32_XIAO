#ifndef globals_h
#define globals_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int moves = 0;
unsigned long solvingTime = 0;
unsigned long startTime = 0;

// MQTT
String clientId = "ESP32-cube";
const char *mqtt_server = "126.202.13.142";
const char *mqtt_user = "";
const char *mqtt_password = "";;
WiFiClient espClient;
PubSubClient client(espClient);

#endif
