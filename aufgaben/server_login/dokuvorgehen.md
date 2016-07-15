## Vorgehensweise zur Lösung der Server-Login Aufgabe

- Mit nmap den Port ausfindig machen, auf dem der telnet server läuft (9000)
- als guest einloggen
    - `help` aufgerufen: Übersicht der Befehle erhalten:
        - `help`
        - `showuser`
        - `logout`
        - `showlisence`
    - sämtliche der angezeigten Befehle ausprobieren (auch mit richtig langen
      Parametern - aufgrund eines eventuellen Bufferoverflows)
- Passwort rausfinden für user `banane` mit fuzzy-matching und ausprobieren
    - PW: `rhababerkuchen`
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

    - aufgefallen, dass `listserverasdfghjk` auch den gleichen output generiert
    - wenn `ctrl + C` gedrückt wurde, wurde nur noch logout abgefangen
    - nach `serverstatus 6666` gibt `showuser` folgenden output:

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


