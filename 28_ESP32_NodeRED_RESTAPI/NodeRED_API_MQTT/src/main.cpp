/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | https://links.pixeledi.eu
Statemachine in Arduino Projekten 11.2024

*/

#include <Arduino.h>

#include "button.h"
#include "globals.h"
#include "wifimqtt.h"
#include <ArduinoJson.h>

Button btn1(D2);
Button btn2(D3);

void checkButtons() {
  switch (btn1.checkBTN()) {
  case 1:
    state = SENDMQTT;
    break;
  case 2:
    state = REQUESTVIAMQTT;
    break;
  }
}

void setup() {
  Serial.begin(115200);

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  state = WAIT;
}

void loop() {
  checkButtons();

  unsigned long currentMillis = millis();

  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP32XIAO-statemachine");

  switch (state) {
  case WAIT:
    {
      if (currentMillis - previousMillis >= 2000) {
        previousMillis = currentMillis;
        Serial.println("WAITING");
      }
      break;
    }
  case SENDMQTT:
    {
      Serial.println("SENDMQTT");

      // {"sensor":"gps","time":1351824120,"data":[48.75608,2.302038]} 
// Stream& output;

      JsonDocument doc;

      doc["sensor"] = "gps";
      doc["time"] = 1351824120;

      JsonArray data = doc["data"].to<JsonArray>();
      data.add(48.75608);
      data.add(2.302038);

      doc.shrinkToFit();  // optional
      char output[128]; // Puffer für JSON
      serializeJson(doc, output);

      client.publish("api/update", output); 
      state=WAIT;
      break;
     
    }
  case REQUESTVIAMQTT:
    {
      client.publish("api/getData", "pixeledi_abonniert?");
      Serial.println("REQUESTVIAMQTT");
      break;
    }
  
  }
}
