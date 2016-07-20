# Aufgabenstellung Integer Underflow

## Szenario
Mit diesem Beispiel wird veranschaulicht, dass bei Angaben von einer Länge
doppelt geprüft werden muss. In Vielen C-Funktionen muss als zusätzlicher
Parameter die Bufferlänge angegeben werden. Hier können Unachtsamkeiten schnell
zu einem ungewollten Sicherheitsrisiko führen.

## Aufgabenstellung
Analysieren Sie das Programm, finden Sie den Fehler und nutzen sie diesen zu
Ihren Gunsten (letzteres Verbal).

## Dokumentation
Als weiteres Beispiel einer Schwachstelle wurde ein einfacher Integer-Underflow
verwendet. Hierzu wird eine Eingabe mit memcpy() in den vorgesehenen
Speicherbereich kopiert. Anzumerken ist, dass i mal die Größe eines Integers
zum Kopieren vorgesehen ist. Errechnet man sich hierbei die maximale Größe
eines Unsigned Integers (z. B. 2^32) und teilt dies durch die Speichergröße
eines Integers (z. B. 4 Byte), so erhält man z. B. die Zahl 1073741824. Diese
nimmt man beispielsweise als negative Eingabe und startet das Programm dann mit
folgendem Befehl:

    ./easy_integer_underflow -1073741824 test

Hierbei sieht man, dass diese Zahl als 0 übernommen wird. Das liegt daran,
dass durch die Multiplikation die Zahl -(2^32) entstanden ist und dadurch 33
Bit benötigt werden, um die Zahl negativ darzustellen - durch den Integer
Underflow wird aber das Vorzeichen-Bit abgeschnitten.
Warum sollte das sinnvoll sein?
Für Angreifer ist es je nach Aufgabe leichter, den EBP und den ESP zu
überschreiben, wenn man statt einem Overflow einen Underflow verursacht.

Die Anwendung kann beispielsweise mittels folgendem Befehl exploitet werden und
auf eine andere Funktion verweisen:

    ./easy_integer_underflow -1073741812 AAA(36x)BBBB(mit Rücksprungadresse ersetzen)
