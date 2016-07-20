# Bruteforce
## Beschreibung
Hierbei handelt es sich um keine Schwachstelle oder Sicherheitslücke, sondern
es soll den Probanden zeigen, dass man bereits mit wenig Zeilen Quellcode ein
Passwortcracker programmieren kann. Zugegeben, eine Bruteforce-Anwendung ist
nicht die effektivste Attacke, jedoch ist sie oft hilfreich. Um dies zu
demonstrieren, wurde ein weiteres Programm erstellt: dieses wartet auf eine
bestimmte Eingabe, welche der "Bruteforcer" anschließend erraten soll.

## Aufgabenstellung
1. Mit `gcc` das Demoprogramm kompilieren: 

    $ gcc -o pass pass.c

1. Awendung testhalber mit Beispielargumenten ausführen
1. Sicherung von `brute.c` anlegen

    $ cp brute.c brute.c.BK

1. `brute.c` anpassen und erlaubte Zeichenmenge entsprechend festlegen
1. Bruteforce-Awendung kompilieren:  

    $ gcc -o bruteforce brute.c

1. Bruteforce-Angriff starten:
