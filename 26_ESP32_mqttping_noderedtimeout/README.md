
# NodeRED Timer und ESP32 MQTT Ping mit ESPHome

Video unter: https://www.youtube.com/@pixeledi

esphome sketch

```yaml
substitutions:
 device_name: mqttping
 device_board: seeed_xiao_esp32c3
 device_type: arduino

packages:
  base: !include 00_common/main.yaml

interval:
  - interval: 5sec
    then:
      - mqtt.publish:
          topic: "studio/ping"
          payload: "ich bin da"
```

Node-RED Function - Timer

```js
// Aktuellen Timer aus dem Kontext abrufen
let timeout = context.get('timeout');

// Falls ein Timer existiert, zurücksetzen
if (timeout) {
    clearTimeout(timeout);
}

// Neuen Timer setzen
timeout = setTimeout(() => {
    msg.payload = "ON";
    node.send(msg);
}, 15000);

// Timer im Kontext speichern
context.set('timeout', timeout);

return null;
```
