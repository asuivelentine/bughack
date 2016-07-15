## Vorgehensweise zur Lösung der Server-Login Aufgabe

- Mit nmap den Port ausfindig machen, auf dem der telnet server läuft (9000)
- als "guest" mit den gegebenen Logindaten einloggen
    - `help` aufgerufen: Übersicht der Befehle erhalten:
        - `help`
        - `showuser`
        - `logout`
        - `showlisence`
    - sämtliche angezeigten Befehle ausprobieren (auch mit richtig langen
      Parametern - um einen eventuellen Bufferoverflow zu finden)
- Passwort rausfinden für user `banane` mit fuzzy-matching und Ausprobieren
    - Passwort: `rhababerkuchen`
- Als `banane` eingeloggt
    - `help` aufgerufen, zusätzliche Befehle entdeckt:
        - `listserver`
        - `serverstatus SERVERID`
    - `showuser` aufgerufen, reputation ist jetzt 4 statt 0 wie bei guest
    - `listserver` aufgerufen:

        ```
        Server-ID:      [1234]
        Status:         [running]
        port:           [9000]

        Server-ID:    [1337]
        Status:       [running]
        port:         [1337]

        Server-ID:    [6666]
        Status:       [stopped]
        port:         [6666]
        ```

    - aufgefallen, dass `listserverasdfghjk` auch den gleichen Output generiert
    - wenn `ctrl + c` gedrückt wurde, wurde nur noch `logout` abgefangen (die Verbindung wurde serverseitig bereits beendet)
    - nach `serverstatus 6666` gibt `showuser` folgenden Output:

        ```
        UserInfo:
        ---------

        reputation:   [-2147483648]
        name:         [admin]
        debug:        [True]
        ```
    - offenbar ist man jetzt admin
    - `help` gibt jetzt zusätzlich noch `enableDebug` als Befehl aus,
      allerdings ist die Liste korrumpiert
    - `enableDebug` scheint keine Funktion zu haben, da der Befehl nicht
      gefunden wird

      ```
      enableDebug
      Command not found. Enter help for an overview of existing commands
      ```
      
## Finden der Sicherheitslücke im C-Quellcode

Bei einer Quellcode-Analyse sind folgende Auffälligkeiten ins Auge gestochen:
    - Das Kommando, das die Rechteerweitung ausführt (`serverstatus`) wird in der Funktion `parse_command` in der Datei `handler.c` implementiert.
    - In der Funktion `parse_command` wird dabei die Funktion `show_server_info` aufgerufen:

        ```
        // handler.c:134: parse_command
        COMMAND("serverstatus", data, 12) {
        char token[] = " ";
        char* split;
        split = strtok(data, token);
        split = strtok(NULL, token);

        if(split == NULL) {
            strcat(answer, "Missing serverID argument\n");
        } else {
            int id = atoi(split);
            check_database_permissions(answer, mem->name, "passwort", &mem->reputation);
            if(id == 6666)
                show_server_info(answer, 6666, ADMIN_REPUTATION);
            else if(id == 1234 || id == 1337)
                show_server_info(answer, id, ADMIN_REPUTATION);
            else
                strcat(answer, "unknown ID\n");
        }
        ```
        
    - In der Datei `lib.c` wurde die Funktion `show_server_info` implementiert, dort hat sie vier Übergabeparameter: 
        ```
        void show_server_info(char buffer[], int server_id, user_group rights, unsigned int* status)
        ```
        
    - In der Datei `handler.c` wird die Funktion `show_server_info` jedoch mit nur drei Übergabeparametern bekannt gemacht: 
        ```
        extern void show_server_info(char*, char*, user_group)
            vs.
        extern void show_server_info(char*, char*, user_group, unsigned int*)
        ```
    - Beim Aufruf der Funktion scheint der derzeitig eingeloggte User jedoch in der Variablen `status` referenziert zu werden.
        ```
        // lib.c:257: show_server_info(...)
        if(status && (state == false)){
            *status = -1;                                  // <-- hier wird der Benutzer `banane` zum Admin.
        }
        ```

### Wieso wird der User referenziert, obwohl er gar nicht mitübergeben wird?

Um diese Frage beantworten zu können, müssen wir uns die Calling-Convention von x86_64-Prozessoren genauer ansehen:

```
void foo(int a, int b, int c, int d, int e, int f);
```

Wenn die Funktion `foo` aufgerufen wird, so werden die Parameter anhand der folgenden Tabelle übergeben:

| Argument | Register |
| -------- | -------- |
| a (1.)   | rdi      |
| b (2.)   | rsi      |
| c (3.)   | rdx      |
| d (4.)   | rcx      |
| e (5.)   | r8       |
| f (6.)   | r9       |
| 7. - 14. | xmm0 - xmm7 |

Anschließend, sollte es noch weitere Parameter geben, so wird der Stack benutzt.

Wenn nun die Funktion `show_server_info` mit einem Parameter zu wenig aufgerufen wird,
so "bekommt" sie dennoch den fehlenden Parameter. Genauer gesagt, wird einfach der Wert genommen, der bereits davor im entsprechenden Register (hier das `rcx` Register) drin stand, also zum Beispiel der Wert aus einem anderen Funktionsaufruf (mit entsprechend vielen Parametern).
In unserem Fall ist das der folgende Funktionsaufruf:
    ```
    check_database_permissions(answer, mem->name, "passwort", &mem->reputation);
                                                                     ^
                                                                     |
    ```
    
Letztlich wird also folgendes Aufgerufen:

```
show_server_info(answer, 6666, ADMIN_REPUTATION, &mem->reputation);
```
