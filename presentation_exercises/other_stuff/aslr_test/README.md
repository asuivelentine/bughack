##ASLR - Address-Space-Layout-Randomization
### Beschreibung

ASLR ist eine Technik, die das Ausnützen von Buffer-Overflows deutlich erschwert.
Dies wird erreicht, indem die Adressen bestimmter Schlüsselregionen beim Programmstart zufällig gewählt werden.

Diese Schlüsselbereiche umfassen:
* Start der ausführbaren Datei
* Position des Stacks
* Position des Heaps
* Position von hinzugefügten Bibliotheken

Dadurch kann ein Angreiffer die entsprechenden Adressen nicht mehr berechnen und ist gezwungen zu raten.


### Ein- / Ausschalten von ASLR
Die entsprechende Konfigurationsdatei liegt unter `cat /proc/sys/kernel/randomize_va_space`. 
Diese kann nur vom Root-User geändert werden.

```
$ su -c 'echo 0 > /proc/sys/kernel/randomize_va_space'
$ sysctl kernel.randomize_va_space=0
$ setarch $(uname -m)  -R <application> [<parameter>, ..]
```

Die "0" steht hierbei für das Deaktivieren dieser Funktionlität, und die "1" für das Aktivieren.
Um dies permanent zu machen, kann eine entsprechende Datei in `/etc/sysctl.d` anlegt werden.

Um diese Technik zu veranschaulichen, wurde ein Programm erstellt, welches eine 
Hart-Codierte-Adresse ausgibt. \
Ist ASLR deaktiviert, bleibt die Adresse gleich. \
Ist ASLR hingegen aktiv, werden unterschiedliche Adressen ausgegeben.

### Aufgabenstellung
1. Kompilieren der Beispielanwendung  
```
$ gcc -o test test.c
```

2. Mehrfaches Ausführen des Programmes
```
$ ./test
```

3. Ändern der ASLR Konfiguration mit einer der oben genannten Methoden.

4. Erneutes, mehrfaches Ausführen des Programms.
