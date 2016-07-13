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

Menu* initMenu(Menu* pCurrent, MenuTyp pTyp) {
	pCurrent = malloc(sizeof(Menu));
	pCurrent->type = pTyp;

	if(pTyp == Hauptmenu) {
		pCurrent->ueberschrift = "Hauptmenue\n\n";
		pCurrent->inhalt = "Herzlich Willkommen im Kontaktverwaltungsprogramm";
		pCurrent->eintraege = "\t<K> Kontakte ansehen"
				"\n\t<I> Kontakte importieren"
				"\n\t<E> Kontakte exportieren"
				"\n\t<Q> Programm beenden";
	} else if (pTyp == MenuKontakteAnsehen) {
		pCurrent->ueberschrift = "Kontakte anzeigen\n\n";
		pCurrent->inhalt = "Hier sehen Sie eine Liste aller Kontakte";
		pCurrent->eintraege = "\t<P> Kontakt ansehen"
				"\n\t<A> Kontakt hinzufuegen"
				"\n\t<E> Kontakt bearbeiten"
				"\n\t<R> Kontakt loeschen"
				"\n\t<L> Alle Kontakte loeschen"
				"\n\t<B> Zurueck"
				"\n\t<Q> Programm beenden";
	} else if (pTyp == MenuKontakteImportieren) {
		pCurrent->ueberschrift = "Kontakte importieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte aus einer Datei importieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Programm beenden";
	} else if (pTyp == MenuKontakteExportieren) {
		pCurrent->ueberschrift = "Kontakte exportieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte in eine Datei exportieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Programm beenden";
	} else if (pTyp == MenuKontaktAnsehen) {
		pCurrent->ueberschrift = "Kontakt anzeigen\n\n";
		pCurrent->inhalt = "Hier sehen Sie den ausgewaehlten Kontakt";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Programm beenden";
	} else if (pTyp == MenuKontaktHinzufuegen) {
		pCurrent->ueberschrift = "Kontakte hinzufuegen\n\n";
		pCurrent->inhalt = "Hier koennen Sie einen Kontakt Ihrer Kontaktliste hinzufuegen";
		pCurrent->eintraege = "\t<0> Name bearbeiten"
				"\n\t<1> Anschrift hinzufuegen"
				"\n\t<2> Anschrift bearbeiten"
				"\n\t<3> Anschrift loeschen"
				"\n\t<4> Mail-Adresse hinzufuegen"
				"\n\t<5> Mail-Adresse bearbeiten"
				"\n\t<6> Mail-Adresse loeschen"
				"\n\t<7> Telefonnummer hinzufuegen"
				"\n\t<8> Telefonnummer bearbeiten"
				"\n\t<9> Telefonnummer loeschen"
				"\n\t<B> Zurueck"
				"\n\t<Q> Programm beenden";
	} else if (pTyp == MenuKontaktBearbeiten) {
		pCurrent->ueberschrift = "Kontakt bearbeiten\n\n";
		pCurrent->inhalt = "Hier koennen Sie einen Kontakt bearbeiten";
		pCurrent->eintraege = "\t<0> Name bearbeiten"
				"\n\t<1> Anschrift hinzufuegen"
				"\n\t<2> Anschrift bearbeiten"
				"\n\t<3> Anschrift loeschen"
				"\n\t<4> Mail-Adresse hinzufuegen"
				"\n\t<5> Mail-Adresse bearbeiten"
				"\n\t<6> Mail-Adresse loeschen"
				"\n\t<7> Telefonnummer hinzufuegen"
				"\n\t<8> Telefonnummer bearbeiten"
				"\n\t<9> Telefonnummer loeschen"
				"\n\t<B> Zurueck"
				"\n\t<Q> Programm beenden";
	} else if (pTyp == MenuNameBearbeiten) {
		pCurrent->ueberschrift = "Name bearbeiten\n\n";
		pCurrent->inhalt = "Hier koennen Sie den Namen des Kontakts bearbeiten";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Beenden";
	} else if (pTyp == MenuAnschriftHinzufuegen) {
		pCurrent->ueberschrift = "Kontakte exportieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte in eine Datei exportieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Beenden";
	} else if (pTyp == MenuAnschriftBearbeiten) {
		pCurrent->ueberschrift = "Kontakte exportieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte in eine Datei exportieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Beenden";
	} else if (pTyp == MenuMailAdresseHinzufuegen) {
		pCurrent->ueberschrift = "Kontakte exportieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte in eine Datei exportieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Beenden";
	} else if (pTyp == MenuMailAdresseBearbeiten) {
		pCurrent->ueberschrift = "Kontakte exportieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte in eine Datei exportieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Beenden";
	} else if (pTyp == MenuTelefonnummerHinzufuegen) {
		pCurrent->ueberschrift = "Kontakte exportieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte in eine Datei exportieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Beenden";
	} else if (pTyp == MenuTelefonnummerBearbeiten) {
		pCurrent->ueberschrift = "Kontakte exportieren\n\n";
		pCurrent->inhalt = "Hier koennen Sie Kontakte in eine Datei exportieren";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Beenden";
	} else if (pTyp == MenuKontaktSuchen) {
		pCurrent->ueberschrift = "Kontakt suchen\n\n";
		pCurrent->inhalt = "Hier koennen Sie einen Kontakt anhand des Namens suchen";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<P> Vorheriger Kontakt"
				"\n\t<N> Naechster Kontakt"
				"\n\t<Q> Beenden";
	} else {
		pCurrent->ueberschrift = "Nicht gefunden\n\n";
		pCurrent->inhalt = "Das Menu konnte nicht gefunden werden";
		pCurrent->eintraege = "\t<B> Zurueck"
				"\n\t<Q> Programm beenden";
	}

	return pCurrent;
}

Kontakt* printMenu(Menu* pCurrent, Kontakt* pAktuellerKontakt) {
	char select;
	char buffer;
	int read = 1;

	while(1) {
		CLEAR
		printf("%s",pCurrent->ueberschrift);
		SEPARATION_LINE
		printf("%s",pCurrent->inhalt);
		SEPARATION_LINE
		fflush(stdout);

		if(pCurrent->type == Hauptmenu) {
			pAktuellerKontakt = MenuMainMenu(pAktuellerKontakt);
		} else if(pCurrent->type == MenuKontakteAnsehen) {
			pAktuellerKontakt = MenuPrintContacts(pAktuellerKontakt);
		} else if(pCurrent->type == MenuKontakteImportieren) {
			pAktuellerKontakt = MenuImport(pAktuellerKontakt);
		} else if(pCurrent->type == MenuKontakteExportieren) {
			pAktuellerKontakt = MenuExport(pAktuellerKontakt);
		} else if(pCurrent->type == MenuKontaktAnsehen) {
			pAktuellerKontakt = MenuPrintContact(pAktuellerKontakt);
		} else if(pCurrent->type == MenuKontaktHinzufuegen) {
			if(read == 1) {
				pAktuellerKontakt = MenuAddContact(pAktuellerKontakt);
				read = 0;
			} else if(read == 0) {
				KontaktAnzeigen(pAktuellerKontakt);
			}
		} else if(pCurrent->type == MenuKontaktBearbeiten) {
			if(read == 1) {
				pAktuellerKontakt = MenuEditContact(pAktuellerKontakt);
				read = 0;
			} else if(read == 0) {
				KontaktAnzeigen(pAktuellerKontakt);
			}
		} else if(pCurrent->type == MenuNameBearbeiten) {
			pAktuellerKontakt = MenuEditName(pAktuellerKontakt);
		} else if(pCurrent->type == MenuAnschriftHinzufuegen) {
			pAktuellerKontakt = MenuAddAddress(pAktuellerKontakt);
		} else if(pCurrent->type == MenuAnschriftBearbeiten) {
			pAktuellerKontakt = MenuEditAddress(pAktuellerKontakt);
		} else if(pCurrent->type == MenuMailAdresseHinzufuegen) {
			pAktuellerKontakt = MenuAddMail(pAktuellerKontakt);
		} else if(pCurrent->type == MenuMailAdresseBearbeiten) {
			pAktuellerKontakt = MenuEditMail(pAktuellerKontakt);
		} else if(pCurrent->type == MenuTelefonnummerHinzufuegen) {
			pAktuellerKontakt = MenuAddPhone(pAktuellerKontakt);
		} else if(pCurrent->type == MenuTelefonnummerBearbeiten) {
			pAktuellerKontakt = MenuEditPhone(pAktuellerKontakt);
		} else if(pCurrent->type == MenuKontaktSuchen) {
			pAktuellerKontakt = MenuFindContact(pAktuellerKontakt);
		}

		SEPARATION_LINE
		printf("%s",pCurrent->eintraege);
		SEPARATION_LINE
		printf("Bitte geben Sie Ihre Auswahl ein: ");
		fflush(stdout);
		scanf("%c%c",&select,&buffer);

		/* Auswahl */
		if(select == '0') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(editName, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '1') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(addAddress, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '2') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(editAddress, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '3') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = MenuAdresseLoeschen(pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '4') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(addMailAddress, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '5') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(editMailAddress, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '6') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = MenuMailLoeschen(pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '7') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(addTelephoneNumber, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '8') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(editTelephoneNumber, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == '9') {
			if(pCurrent->type == MenuKontaktHinzufuegen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = MenuTelefonLoeschen(pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == 'K' || select == 'k') {
			if(pCurrent->type == Hauptmenu) {
				pAktuellerKontakt = printMenu(showContacts, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == 'I' || select == 'i') {
			if(pCurrent->type == Hauptmenu) {
				pAktuellerKontakt = printMenu(importContacts, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == 'E' || select == 'e') {
			if(pCurrent->type == Hauptmenu) {
				pAktuellerKontakt = printMenu(exportContacts, pAktuellerKontakt);
			} else if(pCurrent->type == MenuKontakteAnsehen || pCurrent->type == MenuKontaktBearbeiten) {
				pAktuellerKontakt = printMenu(editContact, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == 'L' || select == 'l') {
			if(pCurrent->type == MenuKontakteAnsehen) {
				pAktuellerKontakt = MenuAlleKontakteLoeschen(pAktuellerKontakt);					/* Alle Kontakte loeschen */
			} else {
				SelectionWrong();
			}
		} else if(select == 'P' || select == 'p') {
			if(pCurrent->type == MenuKontakteAnsehen) {
				pAktuellerKontakt = printMenu(showContact, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == 'A' || select == 'a') {
			if(pCurrent->type == MenuKontakteAnsehen) {
				pAktuellerKontakt = printMenu(addContact, pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == 'R' || select == 'r') {
			if(pCurrent->type == MenuKontakteAnsehen) {
				pAktuellerKontakt = MenuKontaktLoeschen(pAktuellerKontakt);
			} else {
				SelectionWrong();
			}
		} else if(select == 'B' || select == 'b') {
			if(pCurrent->type != Hauptmenu) {
				break;
			} else {
				SelectionWrong();
			}
		} else if(select == 'Q' || select == 'q') {
			Quit(pAktuellerKontakt);
		} else { /* Falls eine andere Eingabe getroffen wurde */
			SelectionWrong();
		}
	}

	return pAktuellerKontakt;
}
