# Node-RED und ESP32 mit REST API

Node-RED ist die perfekte Lösung, wenn es darum geht, REST-API-Aufrufe effizient zu handhaben, ohne den Code direkt auf dem Mikrocontroller wie dem ESP32 zu ändern. Dies hat mehrere Vorteile, die in verschiedenen Szenarien zum Tragen kommen.

Ein zentraler Vorteil von Node-RED ist, dass es eine flexible Brücke zwischen Mikrocontrollern und verschiedenen Schnittstellen darstellt. Anstatt direkt im ESP32 einen API-Call zu implementieren und bei Änderungen die Firmware anzupassen, kann Node-RED die API-Calls durchführen und die Ergebnisse in einem standardisierten Format zurückgeben. So bleibt der Code des Mikrocontrollers unverändert, während die Logik für den API-Aufruf und die Verarbeitung von Daten zentral in Node-RED gepflegt werden kann.

Wenn sich zum Beispiel die URL einer API ändert oder zusätzliche Header benötigt werden, müssen diese Änderungen nur in Node-RED vorgenommen werden, ohne dass die Firmware des ESP32 angepasst werden muss. Das JSON, das Node-RED von der API empfängt, bleibt dabei konstant und kann einfach weiterverarbeitet werden, was eine hohe Flexibilität und Wartungsfreundlichkeit ermöglicht.

In einem praktischen Beispiel zeigt Node-RED, wie man mit einem HTTP-Request eine REST-API ansteuert, die Antwort in einem Function-Node bearbeitet und dann die Daten über MQTT an den ESP32 sendet. Dies ermöglicht eine saubere Trennung der Aufgaben: Der ESP32 übernimmt die Sensoren und sendet regelmäßig JSON-Daten, während Node-RED sich um den API-Aufruf und die Weiterverarbeitung der Daten kümmert.

Node-RED macht es einfach, die Logik nachträglich anzupassen, Fehler zu beheben oder neue Anforderungen zu integrieren, ohne in den Code des Mikrocontrollers eingreifen zu müssen. Dies ist besonders nützlich, wenn sich Schnittstellen oder APIs ändern, da diese Änderungen ausschließlich in Node-RED vorgenommen werden können.


### Verwendete Links

- https://arduinojson.org/
- https://jsonplaceholder.typicode.com/guide/

# Beispiel Node-RED mit ESP32 und HTTP REST API

In diesem Projekt zeigen wir, wie man mit Node-RED eine REST API ansteuert, die Antwort verarbeitet und diese dann an den ESP32 über MQTT weiterleitet.

## Voraussetzungen
- **Node-RED** ist installiert und läuft.
- **ESP32** ist eingerichtet und läuft mit MQTT.
- **MQTT-Broker** (z.B. Mosquitto) läuft.

## Setup und Konfiguration

### 1. REST API ansteuern

1. **HTTP-Request-Node einrichten:**
   - Füge einen **HTTP Request**-Node hinzu.
   - Wähle als Methode **GET** (oder **POST**, je nach API).
   - Gib eine **Fake API** ein, z.B. `https://jsonplaceholder.typicode.com/posts`.
   - Verbinde den Node mit einem **Debug-Node**, um die Antwort zu sehen.

   ```json
   {
       "method": "GET",
       "url": "https://jsonplaceholder.typicode.com/posts"
   }
   ```

2. **Ausgabe prüfen:**
   - Klicke auf **Deploy**, um den Node auszulösen.
   - Im Debug-Tab siehst du nun die Rückgabe der API.

### 2. Daten verarbeiten

1. **Daten im Function-Node bearbeiten:**
   - Füge einen **Function-Node** hinzu, um die Antwort von der API zu verarbeiten.
   - Beispiel für das Extrahieren von Daten aus dem JSON:

   ```javascript
   var lat = msg.payload[0].latitude;
   var lon = msg.payload[0].longitude;
   msg.payload = "Koordinaten: " + lat + ", " + lon;
   return msg;
   ```

2. **MQTT-Daten an ESP32 senden:**
   - Füge einen **MQTT Output**-Node hinzu.
   - Verbinde diesen mit dem vorherigen Function-Node.
   - Wähle den Broker aus und setze das **Topic** zu `apiupdate`.

   Beispiel für das MQTT-Payload:
   ```json
   {
       "latitude": 48.8588443,
       "longitude": 2.2943506
   }
   ```

### 3. ESP32: Daten senden

**ESP32 Code vorbereiten:**
   - Verwende `ArduinoJSON` in Kombination mit dem Assistenten (Link unten), um die Daten zu serialisieren.
   - Der ESP32 wird nun alle 5 Sekunden GPS-Daten als JSON an das MQTT-Topic `API-Update` senden.

### 4. REST API via HTTP-Request aktualisieren

1. **Daten an die REST API senden:**
   - Füge einen **HTTP Request**-Node hinzu, um die verarbeiteten Daten zu aktualisieren.
   - Verwende die folgende URL:
     ```json
     https://jsonplaceholder.typicode.com/posts/10
     ```
   - Wähle **PUT** als Methode und füge den Payload mit den neuen Daten hinzu.


### 5. Test und Auswertung

- Wenn du den **ESP32**-Code hochgeladen hast und Node-RED läuft, kannst du testen, ob die Daten wie gewünscht an die REST API gesendet werden.
- Überprüfe die Rückgabe der API und stelle sicher, dass die Daten korrekt aktualisiert wurden.

### Fazit
In diesem Projekt haben wir gesehen, wie man mit Node-RED eine REST-API ansteuert, die Antwort verarbeitet und diese dann an den ESP32 über MQTT weiterleitet. Dies ist eine leistungsstarke Methode, um Daten zwischen verschiedenen Systemen zu integrieren und die Logik im Node-RED zu zentralisieren.
