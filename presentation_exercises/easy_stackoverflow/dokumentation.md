## Aufgabenstellung Stackoverflow

### Dokumentation
Bei diesem Beispiel ging es um einen einfach Stackoverflow. Dieser kann
ausgelöst werden, wenn man mehr als 3 Zeichen eingibt, da die Input-Variable
4 Zeichen speichert (eins für das Null-Terminiert Zeichen). Um den Angriff
zu verdeutlichen, wird zunächst der normale Inhalt aus der toAttack-Variable
angegeben. Erst nach dem strcpy von Argument 1, kann die toAttack-Variable
überschrieben werden. Um dies zu verdeutlichen bzw. zu überprüfen erfolgt danach
eine einfache Ausgabe beider Variablen.<br/>
Stackoverflows werden oft verwendet, um Shellcodes auf dem Stack abzulegen
und um diesen Shellcode nachher ausführbar zu machen, in dem man bspw. die
Schutzmechanismen des Betriebssystems deaktiviert + den Stack-Protector beim
Kompilieren. Da man als Anwender der Software oftmals nur den Binärcode erhält,
kann man ohne eine Analyse des Programms auch nicht herausfinden, ob der Stack-
Schutz deaktiviert ist. Überschreibt man dann zusätzlich nicht nur die toAttack-
Variable, lässt sich auch der BasePointer und der gerettete InstructionPointer
überschreiben, so dass man nach der Funktion auf jeden beliebigen Speicherinhalt,
bspw. der des eingefügten Shellcodes, verweisen kann. Diese Aufgabe demonstriert
also anschaulich, was mit dem Stack passieren kann. Damit die Leute nicht ganz
ratlos sind, haben wir zudem ein kleines Beispielprogramm geschrieben, in denen
daher die Argumente geprüft werden.

### Aufgabenstellung
- Finden Sie die Schwachstelle im Quelltext
- Erläutern Sie die Gefahren, welche daraus entstehen
