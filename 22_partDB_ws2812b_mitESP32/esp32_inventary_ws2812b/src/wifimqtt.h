#include <Arduino.h>
#include "globals.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// MQTT
String clientID = "ESP32-";
const char *mqtt_server = "114.201.11.122";
const char *mqtt_user = "";
const char *mqtt_password = "";
WiFiClient espClient;
PubSubClient client(espClient);

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    clientID += String(random(0xffff), HEX);
    if (client.connect(clientID.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connect to MQTT");
      client.subscribe("shelf");
      client.subscribe("shelf/wait");
      client.subscribe("shelf/rainbow");
      client.subscribe("shelf/range");
      // client.subscribe("shelf/2/range");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char *topic, byte *message, unsigned int length)
{
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    messageTemp += (char)message[i];
  }

  if (String(topic) == "shelf/rainbow")
  {
    // Serial.println("rainbow via mqtt");
  }

  if (String(topic) == "shelf/wait")
  {
    Serial.println("wait via mqtt");
    state = CHANGED;
  }

  if (String(topic) == "shelf/range")
  {

  

    Serial.println(messageTemp);

    // Stream& input;

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, messageTemp);

    if (error)
    {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    int from = doc["from"]; // 1
    int to = doc["to"];     // 3

    JsonObject color = doc["color"];
    int color_r = color["r"]; // 255
    int color_g = color["g"]; // 0
    int color_b = color["b"]; // 255

    neoleds.startled = from;
    neoleds.endled = to;
    neoleds.shelf = 1;
    neoleds.r = color_r;
    neoleds.g = color_g;
    neoleds.b = color_b;
    state = CHANGED;
  }
}

void connectAP()
{
  Serial.println("Connect to my WIFI");

  WiFi.begin(ssid, password);

  byte cnt = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt > 30)
    {
      ESP.restart();
    }
  }

  Serial.println(WiFi.localIP());
}
