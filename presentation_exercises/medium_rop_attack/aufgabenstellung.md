## Aufgabenstellung ROP-Attack

### Szenario

ROP ist eine Attacke, welche prinzipiell bei jedem Programm angewendet werden 
kann. Dabei wird der Base-Pointer veraendert, sodass das Programm einen
alternativen Ablauf nimmt. Z.B. koennen dadurch Funktionen aufgerufen werden, 
welche das Programm eigentlich nicht nutzt.

`Hinweis: Der Stackprotecor sowie ASLR muessen ausgeschalten wernden`

### Aufgabenstellung
Rufen Sie die Funktion `notCalled` auf, ohne den Quellcode des Programmes 
abzuaendern.
