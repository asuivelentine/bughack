# Private Calendar
## Aufgabenstellung
Es handelt sich hierbei um eine Fake-Application. Diese stellt einen
passwortgeschützten Monatskalender zur Verfügung. Es gibt zwei Wege den
Kalender einzusehen:

- Durch Eingabe des korrekten Passworts
- Durch eine eingebaute Backdoor

Der Backdoor ist fest in das Programm eingebaut. Es handelt sich __nicht__ um
einen Buffer-Overflow, Undefined-Behaviour, etc.

Ziel der Aufgabe ist, herauszufinden wie man auch ohne Eingabe des Passworts
Zugang zum Kalender bekommt.

## Dokumentation
Der oben beschriebene Backdoor kann genutzt werden, wenn man bei der
Passwortabfrage in der vierten Sekunde einer jeden Minute auf Enter drückt (=
das Passwort validieren lässt) unabhängig von dem Inhalt des Passorts.

Die Ursprungsidee war es, eine zeitabhängige Funktionalität einzubauen, sodass
man zu einem bestimmten Zeitpunkt auch ohne richtige Zugansdaten an den
geschützten Teil des Programms herankommt.

Wir haben den benötigten Vergleich mit der Zeit versteckt, indem wir die
entsprechenden zugrundeliegenden Funktionen in anderer Konstellation
(Zeitanzeige oben rechts) häufig benutzt haben.

Dies loggt den Benutzer jedoch nicht automatisch ein, sondern setzt lediglich
einen Flag, der anschließend in der main-Funktion mit abgefragt wird.

Dieser Flag wird nicht in einer globalen Variable gespeichert, sondern wir
nutzen hierfür einen bis jetzt unbenutzten struct-Member im WINDOW struct der
benutzten curses-Bibliothek.

Dies fällt nicht auf, da die entsprechende WINDOW-Variable in viele unserer
Funktionen mitübergeben wird und wir dadurch eine Möglichkeit haben diese an
vielen Stellen unbemerkt zu verändern.

In der Hauptfunktion (main-Funktion) haben wir den Login-Vorgang verschleiert,
indem wir

1. für die Fallunterscheidung, ob der Benutzer eingeloggt ist oder nicht, den
   else-Zweig durch einen else if-Zweig ersetzt haben
1. und darin die Abfrage nach dem zweckentfremdeten struct-Member durch einen
   logisch sinnvoll benannten Makro-Aufruf ersetzt haben (der letzten Endes
   diesen Member zurückgibt)

==> Das heißt: Wir haben die Logik für dem Backdoor komplett von der
Passwortvalidierung entkoppelt. Der Flag wird zwar in der Login-Routine
gesetzt, jedoch im Kontext der Zeitangabe oben rechts. Aus
Verschleierungsgründen umgehen wir das if-Konstrukt und weisen das boolsche
Ergebnis unserer Bedingung der besagten Member-Variable zu.
