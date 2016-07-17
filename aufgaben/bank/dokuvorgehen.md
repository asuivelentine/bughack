## Dokumentation des Vorgehens zur Lösung der Aufgabe
### Allgemeine Informationen sammeln
1. `file` angewendet: `ELF64`, dynamisch gelinkt, stripped
1. `ldd` angewendet: `libcrypt.so` wird benutzt
1. Programm ausgeführt: Hinweis auf `$MEMBER`-Umgebungsvariable gefunden
1. Mit `$MEMBER`-Umgebungsvariable experimentiert ("admin", "root", etc.): kein
   Ergebnis
1. `strings` angewendet: Passwort-Hash und ein paar interessante Strings
   gefunden (Unterscheidung zwischen User und Manager)

### Genauere Analyse
1. `strace` angewendet: Einen Signalhandler gefunden (`SIGINT`)
    1. `SIGINT` getriggert, Rückgabewert ist 1 anstelle der üblichen 130
1. Mit Disassembler statisch analysiert (`radare2`)
    1. `signal` wird über `dlsym` eingebunden (Verschleierung)
    1. Signalhandler wurde auf `SIGINT` (Konstante 2) eingerichtet
    1. `Member-ID` muss nicht als Umgebungsvariable mitgegeben werden, wird auch
       eingelesen
    1. `Member-ID` muss ein signed Integer sein
    1. `Member-ID`:
        1. `== 0`: Manager-Account
        1. `< 0`: Normaler Benutzer
        1. `> 0`: Invalide Eingabe
    1. Signal-Handler muss im richtigen Moment ausgeführt werden, z.B. durch
       Drücken von `CTRL + C`
1. C-Datei aus den Erkenntnissen erstellt, siehe Github

### Erklärung für die Lösung erforderlichen Kenntnisse
1. Aufbau einer ELF-Executable
1. Funktionsweise des Stacks
1. Call-Conventions
1. Assembler-Befehle und CPU-Register
1. Funktionsweise eines Bufferoverflows
1. Grundlegende Nutzung von `radare2`

