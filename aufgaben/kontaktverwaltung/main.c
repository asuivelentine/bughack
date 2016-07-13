#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "kontakt.h"
#include "menu.h"
#include "functions.h"
#include "readStr.h"
#include "replaceStr.h"
#include "dbLaden.h"
#include "dbSpeichern.h"
#include "main.h"

int main(int argc, char** argv) {
	mainMenu = initMenu(mainMenu, Hauptmenu);
	showContacts = initMenu(showContacts, MenuKontakteAnsehen);
	importContacts = initMenu(importContacts, MenuKontakteImportieren);
	exportContacts = initMenu(exportContacts, MenuKontakteExportieren);
	showContact = initMenu(showContact, MenuKontaktAnsehen);
	addContact = initMenu(addContact, MenuKontaktHinzufuegen);
	editContact = initMenu(editContact, MenuKontaktBearbeiten);
	editName = initMenu(editName, MenuNameBearbeiten);
	addAddress = initMenu(addAddress, MenuAnschriftHinzufuegen);
	editAddress = initMenu(editAddress, MenuAnschriftBearbeiten);
	addMailAddress = initMenu(addMailAddress, MenuMailAdresseHinzufuegen);
	editMailAddress = initMenu(editMailAddress, MenuMailAdresseBearbeiten);
	addTelephoneNumber = initMenu(addTelephoneNumber, MenuTelefonnummerHinzufuegen);
	editTelephoneNumber = initMenu(editTelephoneNumber, MenuTelefonnummerBearbeiten);
	searchContact = initMenu(searchContact, MenuKontaktSuchen);

	Kontakt* meineKontaktliste = NULL;
	meineKontaktliste = dbLaden(meineKontaktliste, "default.xml");
	printMenu(mainMenu, meineKontaktliste);

	return 0;
}
