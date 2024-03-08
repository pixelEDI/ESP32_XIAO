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
ESP32 Websocket Beispiel | V1.0 | 03.2024
*/
#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include "credentials.h"

const char *websockets_server_host = "nodered.ipv64.net"; // Enter server adress
const uint16_t websockets_server_port = 1880;  
byte led = D7;
using namespace websockets;
WebsocketsClient client;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    pinMode(led, OUTPUT);

    for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.print(".");
        delay(1000);
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("No Wifi!");
        return;
    }

    Serial.println("Connected to Wifi, Connecting to server.");
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/esp32");
    if (connected)
    {
        Serial.println("Connected!");
        client.send("Hello Node-RED");
    }
    else
    {
        Serial.println("Not Connected!");
    }

    client.onMessage([&](WebsocketsMessage message){
        Serial.print("Got Message: ");
        Serial.println(message.data());

        byte ledOn= message.data().toInt();
        if(ledOn==1){
            digitalWrite(led, HIGH);
        }
        else {
             digitalWrite(led, LOW);
        }

      }); 
}

void loop()
{

    if (client.available())
    {
        client.poll();
    }
     else{
        client.connect(websockets_server_host, websockets_server_port, "/esp32");
        Serial.println("reconnected");
    }

    client.send(String(25));
    delay(1000);
    
}