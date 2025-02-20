# ESP32 Arduino Core - Einführung in Pointer

In diesem Repository wird ein Beispielprojekt vorgestellt, das die Verwendung von Pointern auf dem ESP32 mit dem Arduino Core zeigt. Es handelt sich um eine einfache Einführung in die Grundlagen von Pointern, ihren Nutzen und wie man sie effektiv einsetzt, insbesondere im Hinblick auf die Arbeit mit größeren Datenmengen.

## Beschreibung

Das Beispiel zeigt, wie ein Pointer auf eine Variable zeigt und wie man damit auf die Speicheradresse zugreift, um den Wert der Variable effizient zu ändern. Dies wird durch das Arbeiten mit Integer-Werten und einem einfachen Beispiel zum Ermitteln des größten Werts in einem Array verdeutlicht.

Im zweiten Teil des Projekts wird ein Array mit Messwerten erstellt, und die Funktion `FindMaxValue` wird verwendet, um den größten Wert zu ermitteln. Dabei wird ein Pointer verwendet, um die Array-Daten zu übergeben, was eine speichereffiziente Methode darstellt.

### Code von Pointer Variable
In diesem Code wird die Verwendung von Zeigern in C++ auf dem ESP32 gezeigt. Zu Beginn wird die serielle Kommunikation mit einer Baudrate von 115200 gestartet. In der `loop`-Funktion wird eine Variable `eineVariable` erstellt und ein Pointer `einPointer` auf ihre Adresse gesetzt. Es werden verschiedene Werte ausgegeben:

- Der Wert von `eineVariable` und der Wert, auf den der Pointer zeigt (`*einPointer`).
- Die Speicheradresse von `eineVariable`.
- Die Adresse, auf die der Pointer zeigt (`*einPointer`).
- Die Speicheradresse des Pointers selbst.

Das Ganze wird alle 3 Sekunden wiederholt. Dies dient als einfaches Beispiel für das Arbeiten mit Pointern und Speicheradressen in Arduino/C++.


### Code von Pointer Array

In diesem Code wird eine Funktion `findMaxValue` erstellt, die den höchsten Wert in einem Array sucht. Die Funktion erhält einen Pointer auf das Array sowie die Größe des Arrays und gibt den maximalen Wert zurück. In der `loop`-Funktion wird ein Array `messwerte` mit 40 vorgegebenen Werten erstellt, und der maximale Wert des Arrays wird mit der Funktion ermittelt und über die serielle Ausgabe ausgegeben.

Einige interessante Punkte:

- Der Pointer `arr` wird an die Funktion `findMaxValue` übergeben, um auf das Array zuzugreifen.
- Es wird der `sizeof`-Operator verwendet, um die Größe des Arrays und des Pointers zu ermitteln, wobei dies in auskommentierten Zeilen zu finden ist.
- Der Code gibt den größten Messwert aus, nachdem er alle Werte im Array durchlaufen hat.

Die Verwendung von Zeigern und der direkte Zugriff auf Array-Elemente in der Funktion zeigen, wie Speicher und Arrays effizient genutzt werden können.
