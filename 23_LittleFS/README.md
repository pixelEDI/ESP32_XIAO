## LittleFS mit PlatformIO

* Zuerst "data" Ordner in selber Ebene wie "src" erstellen
* Inhalte in "data" reinkopieren
* Dann unter Menüpunkt: PlatformIO -> Projekt Task -> Platform -> Bild Filesystem Image   
```
Building in release mode
Building FS image from 'data' directory to .pio/build/seeed_xiao_esp32c3/littlefs.bin
/index.html
/messdaten.txt
```
* ESP32 mit PC verbinden
* Zwei Menüpunkte darunter -> Upload Filesystem Image

## Links
* ESP32 Core Librarys: https://github.com/espressif/arduino-esp32/tree/master/libraries/LittleFS
* LittleFS:  https://github.com/littlefs-project/littlefs
