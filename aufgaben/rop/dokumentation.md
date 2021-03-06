# ROP Attack

Zusätzlich haben wir eine ROP ausarbeiten wollen, haben diese aber selbst noch
nicht fertig gestellt, da wir der Auffassung waren, dass die ROP für einen
erfahrenen Code-Analyser schnell sichtbar wird, dennoch viel Zeit benötigt, um
diese exploiten zu können, aber Personen, die das das erste Mal angehen,
komplett verzweifeln. Hier der aktuelle Ausbaustand am Anfang eines Programms.

Stand: Anfangsstufe - nicht wie geplant ausnutzbar -, nicht weiter
implementiert, da Aufgabenwechsel

## Was ist eine ROP-Attacke und wozu wurde diese angedacht

Bei der ROP-Attacke (Return Oriented Programming) handelt es sich um eine
Technik, mit der man den Aufrufstack manipuliert, um dann Maschinenbefehle
auszuführen. Hierbei ist anzumerken, dass diese Angriffsform vor allem deshalb
effektiv ist, weil durch Ausnutzung einer Sicherheitslücke die
Speicherschutzmechanismen, wie zum Beispiel die Data Execution Prevention (DEP)
bzw. die NX-Bits umgangen werden können. Daher ist auch Maschinencode, welcher
sich auf dem Stack finden, ausführbar. Normalerweise werden auf dem Stack nur
nichtausführbare Elemente wie beispielsweise Variablen einer Funktion,
abgelegt. Durch die ROP-Attacke wird zunächst eine Rücksprung-Adresse
(ebenfalls auf dem Stack befindend) überschrieben, welche dann auf eine andere
Funktion im Stack verweist und dann ausgeführt wird und im Gegensatz zu einer
"normalen" Überschreibung dafür sorgt, dass nach Verlassen der Funktion, die
eigentliche Funktion ausgeführt wird. Dadurch wird der Programmfluss nur kurz
umgelenkt, mit dem Effekt, dass das Programm keinen Absturz verursacht und
oftmals für den Anwender nicht erkennbar ist, dass im Hintergrund ein Schadcode
ausgeführt wurde. Als spezielle Form der ROP-Attacke wurde daher das return
into libc angedacht, welche eine Sammlung vieler Funktionalitäten,
beispielsweise der system()-Funktion beinhaltet. Um den Stack entsprechend
manipulieren zu können, wurde an einen einfachen Bufferoverflow gedacht.

## Warum wurde die ROP-Attacke abgebrochen

Die ROP-Attacke wurde abgebrochen, da es nach einigen Experimenten nicht
möglich war, einen entsprechenden Exploit selbst zu testen. Da dieser nicht
selbst getestet wurde und wir uns einig waren, dass die Analyse schwierig ist
und nicht eindeutig auf die ROP-Attacke verweisen könnte (da beispielsweise ein
normaler Bufferoverflow angenommen werden kann), wurde die Aufgabe abgebrochen.
Ebenso hatten wir kein konkretes Beispiel für die ROP-Attacke entwickelt, es
handelt sich nach wie vor um ein Grundlagenprogramm mit entsprechender
Schwäche.
