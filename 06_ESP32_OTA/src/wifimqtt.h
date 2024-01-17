#include <Arduino.h>
#include <WiFi.h>

IPAddress local_IP(192, 168, 178, 93);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional


void connectAP()
{
  Serial.println("Connect to my WIFI");

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    Serial.println("STA Failed to configure");
  }

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