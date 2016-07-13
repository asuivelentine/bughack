# Bank
## Szenario

Die Anwendung stellt ein Demo-Programm da, welches eine Account-Sperre hat, d.
h., das viele Funktionen erst nach einer Legitimierung zur Verfügung stehen. So
ein Programm kann bspw. in einer Bank am Bankautomaten oder am Schalter oder
sogar für den Zugang des Filialleiters verwendet werden. Daher ist für dieses
Programm relevant, das keine unbefugten Zugriffe möglich sind, die bspw. der
Hersteller der Software hätte implementieren sollen.

## Aufgabenstellung

Überprüfen Sie daher die Anwendung auf Möglichkeiten, die neben dem normalen
Login, einen weiteren Zutritt ins System gewähren könnten. Erläutern Sie Ihre
Vorgehensweise und dokumentieren Sie diese. Überprüfen Sie die Anwendung aber
auch, auf weitere Schwachstellen im Bezug auf das Account-Management. Woher weiß
die Anwendung, welche Kennwörter richtig sind?  Welche Benutzerrollen könnte es
geben? Und wo, vor allem aber wie sicher (bspw. Klartext, base64, MD5, …),
werden diese Informationen gespeichert?
