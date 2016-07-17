# Aufgabenstellung Integer Underflow

## Szenario
Mittels diesem Beispiel wird veranschaulicht, dass bei Angaben von einer Länge
doppelt geprüft werden muss. In Vielen C-Funktionen muss als zusätzlicher
Parametere die Bufferlength angegeben wird. Hier können unachtsamkeiten schnell
zu einem ungewollten Sicherheitsrisiko führen.

## Aufgabenstellung
Analysieren Sie das Programm, finden Sie den Fehler und nutzen sie diesen zu
Ihren gunsten (letzteres Verbal).

## Dokumentation
Als weiteres Beispiel einer Schwachstelle wurde ein einfacher Integer-Underflow
verwendet.  Hierzu wird eine Eingabe mit Memcpy() in den vorgesehenen
Speicherbereich kopiert.  Anzumerken ist, dass i mal die Größe eines Integers
zum Kopieren vorgesehen ist.  Errechnet man sich hierbei die max. Größe eines
Unsigned Integers (z. B. 2^32) und teilt dies durch die Größe eines Integers
(z. B. 4), so erhält man z. B. die Zahl 1073741824.  Diese nimmt man bspw. als
negative Eingabe und startet das Programm bspw. mit folgendem Befehl:

    ./easy_integer_underflow -1073741824 test

Hierbei sieht man, dass diese Zahl als 0 Byte angenommen wird. Das liegt daran,
weil durch die Multiplikation die Zahl -(2^32) entstanden ist und dadurch 33
Bit-Zahlen benötigt werden, um die Zahl negativ darzustellen, durch den Integer
Underflow wird aber das Vorzeichen-Bit abgeschnitten.
Warum sollte das sinnvoll sein?
Für Angreifer ist es je nach Aufgabe leichter, den EBP und den ESP zu
überschreiben, wenn man statt einem Overflow einen Underflow verursacht.

Die Anwendung kann bspw. mittels folgendem Befehl exploitet werden und auf eine
andere Funktion verweisen:

    ./easy_integer_underflow -1073741812 AAA(36x)BBBB(mit Rücksprungadresse ersetzen)
