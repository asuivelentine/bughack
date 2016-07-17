## Bruteforce
### Beschreibung
Hierbei handelt es sich um keine Schwachstelle oder Sicherheitslücke. Es soll
den Besuchern zeigen, dass man bereits mit wenig Zeilen Programmcode ein
Passwortcracker programmieren kann. Zugegeben, ein Brutefircer ist nicht die
effektivste Attacke, jedoch oft hilfreich.  
Um dies zu Demonstrieren, wurde ein weiteres Programm erstellt. Dieses wartet
auf eine bestimmte Eingabe, welche der Bruteforcer erraten soll.

### Aufgabenstellung
1. Mit `gcc` Kompilieren das Demoprogramm Kompilieren: 
gcc -o pass pass.c

2. Schreibtischtests durchführen.
3. Sicherung von `brute.c` anlegen
cp brute.c brute.c.BK

4. `brute.c` anpassen und Zeichensatz festlegen
5. Bruteforcer Kompilieren:  
gcc -o bruteforce brute.c

6. Angriff starten
