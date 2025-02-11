
#include "credentials.h"
#include "globals.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

// MQTT
String clientId = "ESP32XIAO-statemachine";
const char *mqtt_server = "26.321.105.88";
const char *mqtt_user = "pixelediderganzechte";
const char *mqtt_password = "einunglaublichgutespasswort";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // for this example not necessary

      client.subscribe("office/light/on");
      client.subscribe("office/light/off");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char *topic, byte *message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "office/light/on") {
    Serial.println("MQTT ON");
  } else if (String(topic) == "office/light/off") {
    Serial.println("MQTT OFF");
  }
}

void connectAP() {

  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt > 30)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}
