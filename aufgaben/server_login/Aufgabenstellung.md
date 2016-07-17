# Server Login
## Szenario

Das Programm repraesentiert eine Online-Serververwaltung. Nach erfolgreichen 
Login, kann die Verwaltung mittels einer Terminal-Sitzung bedient werden.
Die Benutzer koennen Gruppen zugewiessen werden.
Ein Gast login steht zur verfuegung um den Serverstatus und die Lizenz 
einzusehen.

> user: 	guest

> passwd:	guest

## Aufgabenstellung

Verbinden Sie sich mit dem Server und melden sich als Guest an. Machen Sie sich
einen ersten Eindruck von der Verwaltung und deren Funktionen.

> hacking.studicloud.hs-furtwangen.de

> port: unknown


Durch die Unachstamkeit eines Kollegens konnten Teile eines User-
Logins geleakt werden:

> user:		banane

> passwd:	ra\_\_a\_er\_\_\_he\_

Ein Bug im Programmcode, ermoeglicht das Umgehen des Sicherheitssystems.
Finden Sie den Bug zuerst innerhalb der Terminalsitzung und daraufhin anhand
des Programmcodes.

## Dokumentation
Ein Teil der Aufgabenstellung ist herauszufinden, ob eine Sicherheitsluecke so
versteckt werden kann, dass sie unauffindbar ist. Aufgrund dessen geht es in
dieser Aufgabe darum, die Schwachstelle moeglichst gut im Quelltext zu 
verstecken.

Als Praesentation der Schwachstelle wurde ein Server-Informationssystem gebaut. 
Durch ein Anmeldeverfahren wird die reputation vergeben. Je hoeher diese ist,
desto mehr Rechte hat der User auf dem System. Der Adminaccount hat eine
reputation von `-1`.


### Im Detail
Die Schwachstelle steht hierbei nicht direkt im Quelltext. Sie entsteht viel
mehr durch das das Herausnehmen von Programmteilen. Wirklich eingesehen werden
kann sie erst, nachdem der Assembler die Datei geparsed hat. Dafuer wurde der
`X86-Call-Stack` ausgenutzt, indem die Prototype deklaration einer externen
Funktion abgeaendert wurde. Der letzte Uebergabeparameter wurde dabei 
gestrichen. Dies hat zufolge, dass im Code kein Parameter zu sehen ist,
der Compiler jedoch nimmt das Register des vorherigen Aufrufs.

Zuerst wird die Reputation des Users ueberprueft, daraufhin wird dann 
entschieden ob der User die Funktionalitaet nutzen kann. Dies ist in der Praxis
ein gaengiges Vorgehen, um Usergruppen zu implementieren.  
In unserem Beispiel wurde der vorherige Check genutzt, um die Reputation in ein
Register zu laden. Die Parameter werden der Reihe nach in vorgeschriebene 
Register geladen. Das heisst: Die Funktion, dessenPrototyp gekurt wurde, 
nutzt das Register fuer den `n-ten` Parameter, welches zuvor zur reputation-
uebergabe genutzt wurde.  
In unserem Fall war der n-te Parameter ein Statusflag. Wenn eine Funktion
fehlschlaegt ist es ueblich als Error `-1` anzugeben. In diesem Fall wird die
reputation eines beliebigen nutzers veraendert und er wird zum Admin.

### Hilfestellungen
Aufgrund der laenge des Quelltextes wurden sowohl im Quelltext, als auch in der
Bedienweisse hinweisse eingebaut:

1. Es gab eine Hilfe, welche die verfuegbaren Befehle zeigte.
1. Durch benutzen aller Befehle bekam man Admin rechte
1. Durch das Verhalten laesst sich auf den Bereich im Quelltext schliessen
1. Der Quelltext beinhaltet in diesem Bereich eine auffaellige 
Fallunterscheidung.
