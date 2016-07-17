# ROP-Attack

## Szenario

ROP ist eine Attacke, welche prinzipiell bei jedem Programm angewendet werden
kann. Dabei wird der Base-Pointer verändert, sodass das Programm einen
alternativen Ablauf nimmt. Z.B. koennen dadurch Funktionen aufgerufen werden,
welche das Programm eigentlich nicht nutzt.

`Hinweis: Der Stackprotecor sowie ASLR müssen ausgeschalten werden`

## Aufgabenstellung
Rufen Sie die Funktion `notCalled` auf, ohne den Quellcode des Programmes
abzuändern.

## Dokumentation
Dieses Beispiel wurde selbst nicht näher ausgebaut und ist bewusst abstrakt
gehalten, falls Experten sich das Ganze ansehen und rumtüfteln wollen. Im
Allgemeinen ist der Ablauf so, dass man bei vielen Programmen das Problem hat,
dass man als Angreifer oftmals die Rücksprungadresse durch eine vorhandene
Schwäche überschreiben kann und somit bspw.  in Funktionen wie die notCalled,
welche man als bösartiger Entwickler versteckt im Programm hat, springen kann.
Die notCalled-Methode soll hierbei root-Rechte durch setuid-Bits erhalten,
obwohl das Programm unter lokalen Privilegien gestartet wird. Dazu müssen chmod
und chown jeweils dafür sorgen, dass die Datei vor dem Ausführen einmalig dem
Benutzer root zugeordnet werden.  Der normale Ablauf bei einer Funktion ist
der, dass eine Funktion eine andere aufruft und sobald diese beendet ist, man
in die aufzurufende Funktion eine Stelle nach dem Call landet. Dieser Wert wird
im InstructionPointer gespeichert und durch die Call-Konvention auf dem Stack
gepusht und dort kann dieser überschrieben werden. Springt man nun aber nicht
in die aufzurufende Funktion, sondern in die notCalled, findet kein pushen es
InstructionPointers auf den Stack statt. Man landet zwar in der gewissen
Funktion, diese wird auch abgearbeitet, aber beim Verlassen der
notCalled-Funktion stürzt oftmals das Programm ab. Das hat oft den Nachteil,
dass der Anwender feststellen kann, dass eine Manipulation des Programms
vorliegt. Bei ROP ist der Ansatz daher so gewählt, dass man zwar in eine andere
Funktion springt, diese aber dann danach dort weiter macht, wo der normale
Programmablauf weiter machen würde. Man unterbricht also den Programmfluss,
setzt aber nachher wieder an der richtigen Stelle an, um so dem Benutzer zu
verschleiern, dass eine Manipulation vorliegt. Wie dies genau funktioniert,
kann man in der Quelle zu dem Programm nachlesen. Da diese Aufgabe auch nur für
Experten gedacht war, haben wir diese nicht näher aus- gearbeitet. Wir haben
diese auch bewusst dem Schwierigkeitsgrad "Medium" zugeordnet, obwohl diese mit
Abstand die schwerste Aufgabe war, da wir natürlich auch herausfinden wollten,
welcher der Personen sich auskennt. Allen anderen würde dies nicht auffallen ;)
Programm darf natürlich weiter ausgearbeitet werden [^1].

[^1]: Quelle: http://codearcana.com/posts/2013/05/28/introduction-to-return-oriented-programming-rop.html
