# Aufgabenstellung Stackoverflow

## Dokumentation
Bei diesem Beispiel ging es um einen einfachen Stackoverflow. Dieser kann
ausgelöst werden, sobald man mehr als 3 Zeichen eingibt, da die Input-Variable
4 Zeichen speichert (eins für die Null-Terminierung). Um den Angriff zu
verdeutlichen, wird zunächst der normale Inhalt aus der toAttack-Variable
angegeben. Erst nach dem strcpy von Argument 1, kann die toAttack-Variable
überschrieben werden. Um dies zu verdeutlichen beziehungsweise zu überprüfen
erfolgt danach eine einfache Ausgabe beider Variablen.

Stackoverflows werden oft verwendet, um Shellcodes auf dem Stack abzulegen und
um diesen Shellcode nachher ausführbar zu machen, indem man beispielsweise die
Schutzmechanismen des Betriebssystems und den Stack-Protector beim Kompilieren
deaktiviert. Da man als Anwender der Software oftmals nur den Binärcode erhält,
kann man ohne eine Analyse des Programms auch nicht herausfinden, ob der Stack-
Protector deaktiviert ist. Überschreibt man dann zusätzlich nicht nur die
toAttack-Variable, lässt sich auch der Base-Pointer und der gerettete
Instruction-Pointer überschreiben, so dass man nach der Funktion auf jeden
beliebigen Speicherinhalt, beispielsweise den des eingefügten Shellcodes,
verweisen kann. Diese Aufgabe demonstriert also anschaulich, was mit dem Stack
passieren kann. Damit die Probanden nicht ganz ratlos sind, haben wir zudem ein
kleines Beispielprogramm geschrieben, in dem die Argumente geprüft werden.

## Aufgabenstellung
- Finden Sie die Schwachstelle im Quelltext
- Erläutern Sie die Gefahren, welche daraus entstehen
