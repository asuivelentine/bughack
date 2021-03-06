# Aufgabenstellung Heapoverflow
## Szenario

Sie arbeiten bei einem mittelständischen Softwareunternehmen. Bei der Analyse
des Legacy Codes stoßen Sie über ungeschützte Stringoperationen. Diese melden
Sie beim nächstem Meeting. Ihre Kollegen sehen jedoch kein Problem mit diesem
Code und glauben nicht, dass dieser Schwachstellen beinhaltet.

## Aufgabenstellung

Zeigen Sie den Kollegen, dass dieser Code unsicher ist, indem Sie das Programm
zum Absturz bringen. Erläutern Sie daraufhin, wie man diesen dazu nutzen kann,
eigenen Code einzuschleusen und ausführen zu lassen.

## Dokumentation

Bei der Erstellung dieser Aufgabe ging es uns darum, ein einfaches Beispiel zu
finden, wie man auch Einsteigern in der Programmiersprache C zeigen kann,
welche Auswirkungen ein kleiner Programmierfehler haben kann. Für den
erfahrenen Programmierer zeigt dies eine Möglichkeit, wie man Bugs verstecken
kann, um diese in anderen Szenarien auszunutzen. Daher haben wir hier einen
Heap-Overflow implementiert, der dafür sorgt, dass wenn man mehr als 5 Zeichen
mit strcpy(...) in var2 kopiert, dieser auf dem Heap auch die var1
überschreiben kann. Dazu gibt man zur erleichterten Nachvollziehbarkeit des
Vorgehens zunächst die Speicheradressen von var1 und var2 aus und zeigt auch
den Abstand zwischen diesen Variablen an. Danach zeigt man, dass eine normale
Eingabegröße dennoch ausgegeben werden kann und var1 nicht überschreibt. Erst
wenn man das Programm mit entsprechend großem Argument, das heißt mehr als 4
Zeichen, startet, sieht man den Effekt eines Heap-Overflows. Heap-Overflows
können von Angreifern verwendet werden, um Shellocde auf den Heap abzulegen.
Standardmäßig besteht auf dem Heap nur ein Lese-/Schreibzugriff, das heißt
Daten auf dem Heap können nicht ausgeführt werden. Umgeht man auch diesen
Schutzmechanismus der Betriebsysteme (Linux: NX-Bits, Windows: DEP), so ist es
Angreifern möglich, viel Schadcode einzuschleusen und dadurch die Kontrolle
über das System zu erlangen. Ein Heap-Overflow ist deshalb gefährlich, weil die
meisten Variablen auf dem Heap dynamisch angelegt werden. Hier gibt es keinen
zusätzlichen Schutz, wie beispielsweise beim Stack durch den Stack-Protector.
Daher ist es möglich bei Programmen, die diese Schwäche haben und bei denen
sich diese Schwäche dann ausnutzen lässt, auch größere Shellcodes auszuführen,
weshalb ein größeres Schadenspotential gegeben ist.
