# Executable 3: Webserver

## Aufbau

Der Server ist in zwei Teile aufgebaut:-

- Login
- User Commands

Der Login teil kümmert sich um die Authentifizierung der User die versuchen sich
einzuloggen. Falls ihnen dies gelingt bekommen sie eine vereinfachte Command
Prompt worauf sie dann Kommands ausführen können.

Der Lösungsweg war hier dieses Kommando auszuführen: `showserverstatus 666`
Dies hat dann durch einen *bug* dem User Administrator Zugang gegeben.
Die Schwierigkeit war hier in den Account zu kommen sowie im Source Code den
Fehler zu finden.

## Erklärung

Der eingebaute Fehler sah folgendermassen aus:


*handler.c*
```c
check_database_permissions(answer, mem->name, "passwort", &mem->reputation);
if(id == 6666)
    show_server_info(answer, 6666, ADMIN_REPUTATION);
else if(id == 1234 || id == 1337)
    show_server_info(answer, id, ADMIN_REPUTATION);
else
    strcat(answer, "unknown ID\n");

```
```c
extern void show_server_info(char*, int, user_group);
```

*lib.c*
```c
void show_server_info(
        char buffer[],
        int server_id,
        user_group rights,
        unsigned int* status)
{
    int state = is_server_online(server_id);
    /* Code */
}
```

Der Fehler hier ist die falsche Signature von `show_server_info`, und zwar fehlt
das letzte Argumente in dem Prototypen. Dies hat zur Folge das zwar im
compilierten Objekt ein 4. Argument erwartet wird aber keins angegeben wird und
der Compiler dies erlaubt.

Der Ablauf ist nun also wie folgt:

1. Eine Funktion wird mit 4 Argumenten aufgerufen, das letzte Argument ist der
   anzugreifende Wert
2. Die *fehlerhafte* Funktion wird nun aufgerufen. Das 4. Argumente liegt nun
   aber immer noch im Register und wird nun benutzt vom Objekt.
3. Der Gewünschte Effekt kann nun passieren, in diesem Fall wird `reputation`
   überschrieben.
4. Der Compiler gibt keine Fehler oder Warnungen aus.


