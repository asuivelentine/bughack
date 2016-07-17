\chapter{Einleitung}

# Projektumfeld

Das Projekt wird von Studenten der HFU als Semesterprojekt durchgeführt. Die
Idee kam von \kaspar der dieses Projekt im Sommersemester 2016 bereit stellte.
Das Projekt wurde folgendermaßen beworben:

> In diesem Projekt soll gezielt verborgene Funktionalität vorzugsweise
> als Bugs in C oder C++ Code eingebaut werden. Jeder Teilnehmer
> überlegt sich, wie er möglichst schwer zu erkennende Bugs, die als
> verborgene Hintertür genutzt werden können, in eine Software einbaut.
> In einer zweiten Rolle sucht jeder Teilnehmer Bugs bzw. Hintertüren
> in der Software anderer Projektteilnehmer. In einem ersten
> Schritt steht dafür nur der Binärcode zur Verfügung, im zweiten Schritt
> dann zusätzlich der Quelltext. Werkzeuge erleichtern das Auffinden
> von Bugs bzw. Hintertüren. Es gilt dabei möglichst produktiv zu sein,
> das bedeutet, die richtigen Werkzeuge zu verwenden.


Nach dem erstem Treffen hat sich dann diese Vorgehensweise ergeben:

1. Zwei Teams werden gebildet
    - Ein Team entwickelt eine Executable für die andere
1. Nun wird versucht die Hintertür zu finden und auszunutzen.
1. Als letzer Schritt wird der Source Code auch preisgegeben
1. Es sollte am besten in beiden Versionen nicht sichtbar sein
1. Nach etwa 4 Wochen werden die Teams neu zusammengestellt und der Prozess
   wiederholt.

# Projektverlauf

Der Projektverlauf verlief nur mit wenigen Organisationsproblemen und lief
somit nach dem oben angegebenem Plan. Das Endresultat besteht aus vier
Executables in C geschrieben die verschiedene Schwachstellen darstellen:

- Eine Bank Emulation die Signale benutzt um eine Hintertür zu öffnen.
- Eine Kalendar Applikation mit einem Timing um hereinzukommen
- Ein Remote Server mit eingebautem Fehlerverhalten
- Eine gepatchte `su` executable mit einem Bufferoveflow um root rechte zu
  bekommen.

Diese wurden auf ein Online Repository[^1] hochgeladen und sind dort
ersichtlich.

## Projektpräsentation

Am Ende des Semesters wurden im Rahmen der Thesisvorstellungen auch die
Semesterprojekte vorgestellt. Dafür wurden weitere Programme erstellt (auch im
Online Repository ersichtlich). Die Besucher konnten sich an den verschiedenen
Schwierigkeitsstufen selbst versuchen. Folgende Hintertüren wurden
implementiert:

- Einen Heapoverflow welcher durch die Übergabeparameter ausgelöst wird.
- Beim Integerunderflow-Beispiel wird auf unzulässigen Speicher zugegriffen.
- Den Stackoverflow
- Eine Hintertür im Grub-bootloader (CVE-2015-8370) durch die man eine
  rootshell bekommt.
- Returned Oriented Programming um eine Manipulation am Callstack zu
  veranschaulichen.

Desweiteren wurde den Besuchern weitere Grundlagen wie ASLR, Assembler und
Bruteforcer vermittelt und veranschaulicht.

[^1]: https://github.com/asuivelentine/bughack
