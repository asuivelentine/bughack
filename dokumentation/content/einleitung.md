\chapter{Einleitung}

# Projektumfeld

Das Projekt wird von Studierenden der HFU als Semesterprojekt durchgeführt. Die
Idee kam von \kaspar der dieses Projekt im Sommersemester 2016 bereitstellte.
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

Nach dem ersten Treffen hat sich dann diese Vorgehensweise ergeben:

1. Es werden zwei Teams gebildet
1. Ein Team entwickelt eine Executable für die jeweils andere
1. Nun wird versucht die Hintertür zu finden und auszunutzen.
1. Als letzer Schritt wird der Source Code preisgegeben
1. Die Hintertür sollte am besten in beiden Versionen nicht offensichtlich sein
1. Nach etwa 4 Wochen werden die Teams neu zusammengestellt und der Prozess
   wiederholt.

# Projektverlauf

Der Verlauf des Projekts wurde nur durch wenige Organisationsprobleme
unterbrochen und lief somit nach dem oben dargestellten Plan. Das Endresultat
besteht aus vier Executables in C geschrieben die verschiedene Schwachstellen
beinhalten:

- Eine Bank Emulation, die Signale benutzt um eine Hintertür zu öffnen
- Eine Kalender Applikation mit einem Timing um hereinzukommen
- Ein Remote Server mit eingebautem Fehlerverhalten
- Eine gepatchte `su` executable mit einem Bufferoveflow um root-Rechte zu
  bekommen

Diese wurden auf ein Online Repository[^1] hochgeladen und sind dort einsehbar.

## Projektpräsentation

Am Ende des Semesters wurden im Rahmen der Thesisvorstellungen auch die
Semesterprojekte vorgestellt. Dafür wurden weitere Programme erstellt (auch im
Online Repository einsehbar). Die Besucher konnten sich an den verschiedenen
Schwierigkeitsstufen selbst versuchen. Folgende Hintertüren wurden
implementiert:

- Ein Heapoverflow welcher durch die Übergabeparameter ausgelöst wird.
- Beim Integerunderflow-Beispiel wird auf unzulässigen Speicher zugegriffen.
- Ein Stackoverflow
- Eine Hintertür im Grub-Bootloader (CVE-2015-8370) durch die man eine
  rootshell bekommt.
- Returned Oriented Programming um eine Manipulation am Callstack zu
  veranschaulichen.

Desweiteren wurden den Besuchern weitere Grundlagen wie ASLR, Assembler und
Bruteforcer vermittelt und veranschaulicht.

[^1]: https://github.com/asuivelentine/bughack
