
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "credentials.h"

// MQTT
String clientId = "ESP32-Haltestelle";
const char *mqtt_server = "49.13.212.23";
const char *mqtt_user = "dom";
const char *mqtt_password = "cobb";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      client.subscribe("bushaltestelle/info");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// only required if we get informations from mqtt

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "bushaltestelle/info")
  {
    Serial.println(messageTemp);
    // Stream& input;
// Stream& input;

  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, messageTemp);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* station = doc["station"]; // "Schottentor U"
  int departure1 = doc["departure1"]; // 9
  int departure2 = doc["departure2"]; // 18
  int departure3 = doc["departure3"]; // 28

    myFahrplan[0].station=station;
    myFahrplan[0].departure1=departure1;
    myFahrplan[0].departure2=departure2;
    myFahrplan[0].departure3=departure3;

    state=SHOWDATA;
  }
}

void connectAP()
{

  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt > 30)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}
