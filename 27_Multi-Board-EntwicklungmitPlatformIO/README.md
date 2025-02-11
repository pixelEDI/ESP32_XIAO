# Multi-Board Entwicklung mit ESP32 und PlatformIO

Diese Anleitung zeigt, wie man mehrere ESP32-Boards in einer PlatformIO-Projektdatei (`platformio.ini`) konfiguriert und steuert. Du kannst zwischen verschiedenen ESP32-Modellen wechseln, ohne die gesamte Konfiguration neu anlegen zu müssen. Dies erleichtert das Testen und Entwickeln für verschiedene Hardware.

## Konfiguration in `platformio.ini`

In der Datei `platformio.ini` definierst du unterschiedliche Umgebungen für jedes ESP32-Modell, das du verwenden möchtest. Hier sind Beispiele für die Konfiguration von drei Seeed Xiao ESP32-Modellen.

### Beispielkonfiguration

```ini
[env:seeed_xiao_esp32c3]
platform = espressif32
board = seeed_xiao_esp32c3
framework = arduino
monitor_speed = 115200
upload_port = /dev/ttyACM*
monitor_port = /dev/ttyACM*
lib_deps = 

[env:seeed_xiao_esp32s3]
platform = espressif32
board = seeed_xiao_esp32s3
framework = arduino
monitor_speed = 115200
upload_port = /dev/ttyACM*
monitor_port = /dev/ttyACM*
lib_deps = 

[env:seeed_xiao_esp32c6]
platform = https://github.com/mnowak32/platform-espressif32.git#boards/seeed_xiao_esp32c6
board = seeed_xiao_esp32c6
platform_packages = 
    framework-arduinoespressif32 @ https://github.com/espressif/arduino-esp32.git#3.0.2
    framework-arduinoespressif32-libs @ https://github.com/espressif/arduino-esp32/releases/download/3.0.2/esp32-arduino-libs-3.0.2.zip
framework = arduino
monitor_speed = 115200
upload_port = /dev/ttyACM*
monitor_port = /dev/ttyACM*
lib_deps = 
```

Um ein Projekt mit einem bestimmten Board zu kompilieren und hochzuladen, verwendest du den Befehl `pio run -e <environment>`. Der Parameter `<environment>` entspricht dem Namen der gewünschten Umgebung aus der `platformio.ini`.

#### Beispielbefehle:

- **Build für ESP32-C3**:
  ```bash
  pio run -e seeed_xiao_esp32c3
  ```

- **Build für ESP32-S3**:
  ```bash
  pio run -e seeed_xiao_esp32s3
  ```

- **Build für ESP32-C6**:
  ```bash
  pio run -e seeed_xiao_esp32c6
  ```

### Weitere nützliche Befehle

- **Upload des Programms auf das Board**:
  ```bash
  pio run -e seeed_xiao_esp32c3 -t upload
  ```

- **Serielle Konsole öffnen**:
  ```bash
  pio device monitor -e seeed_xiao_esp32c3
  ```

Viel Spaß beim Ausprobieren
