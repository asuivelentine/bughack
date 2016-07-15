## Szenario / Aufgabenstellung
Als Hacker habt ihr unbemerkt auf einem Server ein Rootkit installiert euch bei
der Installation eines Rootkits. Es gibt noch einen unprivilegierten user, mit
dem ihr euch einloggen könnt.

> Server: [arch.studicloud.hs-furtwangen.de]()

> Benutzer: clouduser

> Passwort: thisisthechallenge

Loggt euch als unprivilegierter Benutzer ein und nutzt das installierte Rootkit
um eurer täglichen Arbeit als Serveradmin wieder nachgehen zu können.

## Dokumentation
Dieses Mal war eine richtige Sicherheitslücke angedacht. Dabei war unser
Augenmerk weniger auf dem C-Quellcode, sondern viel mehr auf der Demonstration
wie man Bufferoverflows ausnutzen kann. Dazu haben wir das login-utils (Version
2.27.1-1) Projekt auf Archlinux-Systemen modifiziert. Genauer: den Quellcode
der `su` Executable.

Der Rootkit ist folgendermaßen implementiert:

- Einführung eines Kommandozeilenparameteres mit optionalem Argument
- Das optionale Argument wird als Dateiname interpretiert
- Falls die Datei existiert, wird deren Inhalt ohne Längenüberprüfung in einen
  Buffer kopiert
- Durch das Verlassen der Funktion (überschriebene Rücksprungadresse) kann
  somit ein Bufferoverflow ausgelöst werden

### Im Detail
Da es ein Teil der Aufgabenstellung ist, den Rootkit erst zu finden, haben wir
dessen Mechanismus verschleiert. Wir haben uns für das verbose-Flag als
zusätzlichen Kommandozeilenparameter entschieden, da dieser, aufgrund der
häufigen Nutzung in den meisten CLI-Programmen, weniger schnell auffällt und
noch nicht vorhanden war. Außerdem haben wir uns aus demselben Grund für die
Benutzung des optionalen Parameters entschieden. Im Falle der gewohnten Nutzung
des verbose-Flags würde dem Admin kein Unterschied auffallen, da erst bei
Angabe eines gültigen Dateipfades die sichtbare Anwendungslogik verändert wird.

Der Bufferoverflow selbst kann durch Eingabe eines korrekten
Stacki-Basepointers und der korrekten Rücksprungadresse ausgelöst werden. Es
ist kein Shellcode im eigentlichen Sinne notwendig.

### Hilfestellungen
Damit die Aufgabe im Rahmen des Semesterprojekts lösbar bleibt, haben wir
verschiedene Hilfestellungen sowohl in die Executable eingebaut, als auch
mündlich weitergegeben.

1. Aussage: "Es wurde eine *Hilfe* eingebaut." In diesem Fall ist die Aussage
   wörtlich zu nehmen.
1. Durch einen Vergleich der manpage und der Ausgabe des Programms bei Übergabe
   von `--help` sollte ersichtlich werden, dass ein Parameter (`-v, --verbose`)
   eingebaut wurde.
1. Bei anschließender Analyse der zugehörigen Implementation in der
   ausführbaren Datei sollte auffallen, dass der `verbose`-Parameter ein
   optionales Argument besitzt.
1. Zuletzt wird der korrekte Stack-Basepointer, der für die Ausnutzung des
   Rootkits erforderlich ist, ausgegeben sobald das verbose-Flag zusammen mit
   dem optionalen Argument (kann beliebig sein) übergeben wird.
1. Der Einfachheit halber haben wir auf der VM die Address Space Layout
   Randomization (ASLR) deaktiviert.

### VM
Wie der Aufagbenstellung zu entnehmen ist, wurde der Rootkit auf einer VM
innerhalb der Studicloud installiert. Anschließend haben wir sämtliche anderen
Möglichkeiten root-Rechte zu erlangen deinstalliert. Außerdem haben wir
sämtliche Passwörter durch cryptischen Hashes ersetzt.

Die einzige Möglichkeit jetzt noch root-Rechte zu erlangen ist damit unser
Rootkit. Nun haben wir einen Testbenutzer mit den voraussichtlich benötigten
Werkzeugen (gdb, lldb, radare2, HTEditor, binutils, strace) eingerichtet.

Die ASLR wurde bootfest deaktiviert.

### Aufgetretene Probleme
Wir haben uns aus unserer VM einmal ausgeschlossen, da der Paket-Manager des
Betriebssystems die von uns gepatchte `su`-Datei wieder durch das original
ersetzt hat. Deshalb mussten wir die VM ein zweites Mal aufsetzen.

