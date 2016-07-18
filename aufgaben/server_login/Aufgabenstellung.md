# Server Login
## Szenario

Das Programm repräsentiert eine Online-Serververwaltung. Nach erfolgreichem
Login, kann die Verwaltung mittels einer Terminal-Sitzung bedient werden. Die
Benutzer können Gruppen zugewiesen werden. Ein Gast-Login steht zur Verfügung
um den Serverstatus und die Lizenz einzusehen.

> user: 	guest

> passwd:	guest

## Aufgabenstellung

Verbinden Sie sich mit dem Server und melden sich als `guest` an. Machen Sie
sich einen ersten Eindruck von der Verwaltung und deren Funktionen.

> hacking.studicloud.hs-furtwangen.de

> port: unknown

Durch die Unachtsamkeit eines Kollegen konnten Teile eines User-Logins geleakt
werden:

> user:		banane

> passwd:	ra\_\_a\_er\_\_\_he\_

Ein Bug im Programmcode ermöglicht das Umgehen des Sicherheitssystems. Finden
Sie den Bug zuerst innerhalb der Terminalsitzung und daraufhin anhand des
Programmcodes.

## Dokumentation
Ein Teil der Aufgabenstellung ist herauszufinden, ob eine Sicherheitslücke so
versteckt werden kann, dass sie unauffindbar ist. Aufgrund dessen geht es in
dieser Aufgabe darum, die Schwachstelle möglichst gut im Quelltext zu
verstecken.

Als Präsentation der Schwachstelle wurde ein Server-Informationssystem gebaut.
Durch ein Anmeldeverfahren wird eine Reputation vergeben. Je höher diese ist,
desto mehr Rechte hat der Benutzer auf dem System. Der Administratoraccount hat
eine reputation von `-1`.


### Im Detail
Die Schwachstelle steht hierbei nicht direkt im Quelltext. Sie entsteht viel
mehr durch das Herausnehmen von Programmteilen. Wirklich eingesehen werden kann
sie erst, nachdem der Assembler die Datei geparsed hat. Dafür wurde der
`X86-Call-Stack` ausgenutzt, indem die Prototype Deklaration einer externen
Funktion abgeändert wurde. Der letzte Übergabeparameter wurde dabei gestrichen.
Dies hat zufolge, dass im Code kein Parameter zu sehen ist, der Compiler jedoch
nimmt das Register des vorherigen Aufrufs.

Zuerst wird die Reputation des Benutzers überprüft, daraufhin wird dann
entschieden ob der Benutzer die Funktionalität nutzen kann. Dies ist in der
Praxis ein gängiges Verfahren, um Benutzergruppen zu implementieren.  In
unserem Beispiel wurde der vorherige Check genutzt, um die Reputation in ein
Register zu laden. Die Parameter werden der Reihe nach in vorgeschriebene
Register geladen. Das heißt: Die Funktion, dessen Prototyp gekürzt wurde, nutzt
das Register für den `n-ten` Parameter, welches zuvor zur Übergabe der
Reputation genutzt wurde. In unserem Fall war der n-te Parameter ein
Statusflag. Wenn eine Funktion fehlschlägt ist es üblich als Error `-1`
anzugeben. In diesem Fall wird die reputation eines beliebigen Benutzers
verändert und er wird zum Administrator.

### Hilfestellungen
Aufgrund der Länge des Quelltextes wurden sowohl im Quelltext, als auch in der
Bedienung der Anwendung Hinweise eingebaut:

1. Es gibt eine Hilfe, welche die verfügbaren Befehle auflistet
1. Durch das Benutzen aller Befehle bekommt man Administrator-Rechte
1. Durch das Verhalten lässt sich auf den Bereich im Quelltext schließen
1. Der Quelltext beinhaltet in diesem Bereich eine auffällige
   Fallunterscheidung.
