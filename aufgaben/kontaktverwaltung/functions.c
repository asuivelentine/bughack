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

Kontakt* MenuMainMenu(Kontakt* pAktuellerKontakt) {
	int anzKontakte;

	if(pAktuellerKontakt != NULL) {
		pAktuellerKontakt = ersterKontakt(pAktuellerKontakt);
	}

	anzKontakte = anzahlKontakte(pAktuellerKontakt);

	if(anzKontakte != 0) {
		printf("Die Kontaktliste enthaelt %d Kontakte", anzKontakte);
	} else {
		printf("Es sind noch keine Kontakte vorhanden");
	}

	return pAktuellerKontakt;
}

Kontakt* MenuPrintContacts(Kontakt* pAktuellerKontakt) {
	if(pAktuellerKontakt != NULL) {
		if(pAktuellerKontakt->prev != NULL) {
			pAktuellerKontakt = ersterKontakt(pAktuellerKontakt);

			int anzKontakte = anzahlKontakte(pAktuellerKontakt);
			printf("Die Kontaktliste enthaelt %d Kontakte\n\n", anzKontakte);
		}
		AlleKontakteAnzeigen(pAktuellerKontakt);
	} else {
		printf("Es sind noch keine Kontakte vorhanden");
	}

	return pAktuellerKontakt;
}

Kontakt* MenuImport(Kontakt* pAktuellerKontakt) {
	char* dateiname;

	printf("Geben Sie einen Dateinamen zum Importieren ein (Leer fuer default.xml): ");
	fflush(stdout);
	dateiname = readStr();

	if(strcmp(dateiname,"") == 0) {
		dateiname = "default.xml";
	}

	pAktuellerKontakt = dbLaden(pAktuellerKontakt, dateiname);

	return pAktuellerKontakt;
}

Kontakt* MenuExport(Kontakt* pAktuellerKontakt) {
	char* dateiname;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie einen Dateinamen zum Exportieren ein (Leer fuer default.xml): ");
		fflush(stdout);
		dateiname = readStr();

		if(strcmp(dateiname,"") == 0) {
			dateiname = "default.xml";
		}

		if(dbSpeichern(pAktuellerKontakt,dateiname) == 1) {
			printf("Kontakte erfolgreich exportiert");
		} else {
			printf("Fehler beim Exportieren der Kontakte");
		}
	}

	return pAktuellerKontakt;
}

Kontakt* MenuPrintContact(Kontakt* pAktuellerKontakt) {
	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Kontakt-Nr ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt != NULL) {
			pAktuellerKontakt = ersterKontakt(pAktuellerKontakt);
		}

		pAktuellerKontakt = findeKontaktDurchID(pAktuellerKontakt,id);

		if(pAktuellerKontakt != NULL) {
			KontaktAnzeigen(pAktuellerKontakt);
		} else {
			printf("Kontakt wurde nicht gefunden");
			SLEEP
		}
	} else {
		printf("Es sind keine Kontakte vorhanden");
	}

	return pAktuellerKontakt;
}

Kontakt* MenuAddContact(Kontakt* pAktuellerKontakt) {
	char* vorname;
	char* nachname;

	printf("Geben Sie einen Vornamen ein: ");
	fflush(stdout);
	vorname = readStr();
	printf("Geben Sie einen Nachnamen ein: ");
	fflush(stdout);
	nachname = readStr();
	fflush(stdout);

	/* Fallunterscheidung ob erstes Element der Liste oder nicht, ansonsten Kontakt anlegen */
	if(pAktuellerKontakt == NULL) {
		pAktuellerKontakt = KontaktHinzufuegen(pAktuellerKontakt,NULL,vorname,nachname);
	} else {
		pAktuellerKontakt = letzterKontakt(pAktuellerKontakt);
		pAktuellerKontakt = KontaktHinzufuegen(pAktuellerKontakt->next,pAktuellerKontakt,vorname,nachname);
	}

	return pAktuellerKontakt;
}

Kontakt* MenuEditContact(Kontakt* pAktuellerKontakt) {
	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Kontakt-Nr ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt != NULL) {
			pAktuellerKontakt = ersterKontakt(pAktuellerKontakt);
		}

		pAktuellerKontakt = findeKontaktDurchID(pAktuellerKontakt,id);

		if(pAktuellerKontakt != NULL) {
			KontaktAnzeigen(pAktuellerKontakt);
		} else {
			printf("Kontakt wurde nicht gefunden");
			SLEEP
		}
	} else {
		printf("Es sind keine Kontakte vorhanden");
	}

	return pAktuellerKontakt;
}

Kontakt* MenuEditName(Kontakt* pAktuellerKontakt) {
	char* vorname;
	char* nachname;

	printf("Aktueller Vorname: %s\n", pAktuellerKontakt->vorname);
	printf("Geben Sie einen neuen Vornamen ein (leer = unveraendert): ");
	fflush(stdout);
	vorname = readStr();
	printf("Aktueller Nachname: %s\n", pAktuellerKontakt->vorname);
	printf("Geben Sie einen neuen Nachnamen ein (leer = unveraendert): ");
	fflush(stdout);
	nachname = readStr();
	fflush(stdout);

	if(strcmp(vorname,"") != 0) {
		pAktuellerKontakt->vorname = vorname;
	}

	if(strcmp(nachname,"") != 0) {
		pAktuellerKontakt->nachname = nachname;
	}

	return pAktuellerKontakt;
}

Kontakt* MenuAddAddress(Kontakt* pAktuellerKontakt) {
	AdressenTyp aTyp;
	char* strasse;
	char* hausnummer;
	char* plz;
	char* stadt;
	char* land;
	int typ;
	char buffer;

	printf("Handelt es sich um eine private oder geschaeftliche Adresse? (0 oder 1):\n");
	fflush(stdout);
	scanf("%d%c",&typ,&buffer);

	if(typ == 0) {
		aTyp = privateAdresse;
	} else if (typ == 1) {
		aTyp = geschaeftlicheAdresse;
	} else {
		return NULL;
	}

	printf("Strasse: ");
	fflush(stdout);
	strasse = readStr();
	printf("Hausnummer: ");
	fflush(stdout);
	hausnummer = readStr();
	printf("PLZ: ");
	fflush(stdout);
	plz = readStr();
	printf("Stadt: ");
	fflush(stdout);
	stadt = readStr();
	printf("Land: ");
	fflush(stdout);
	land = readStr();

	/* Fallunterscheidung ob erstes Element der Liste oder nicht, ansonsten Kontakt anlegen */
	if(pAktuellerKontakt->adressen == NULL) {
		pAktuellerKontakt->adressen = AdresseHinzufuegen(pAktuellerKontakt->adressen,NULL,aTyp,strasse,hausnummer,plz,stadt,land);
	} else {
		pAktuellerKontakt->adressen = letzteAdresse(pAktuellerKontakt->adressen);
		pAktuellerKontakt->adressen = AdresseHinzufuegen(pAktuellerKontakt->adressen->next,pAktuellerKontakt->adressen,aTyp,strasse,hausnummer,plz,stadt,land);
	}

	return pAktuellerKontakt;
}

Kontakt* MenuEditAddress(Kontakt* pAktuellerKontakt) {
	AdressenTyp aTyp;
	char* strasse;
	char* hausnummer;
	char* plz;
	char* stadt;
	char* land;
	int typ;

	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Adress-Nr ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt->adressen != NULL) {
			pAktuellerKontakt->adressen = ersteAdresse(pAktuellerKontakt->adressen);
		}

		pAktuellerKontakt->adressen = findeAdresseDurchID(pAktuellerKontakt->adressen,id);

		if(pAktuellerKontakt->adressen != NULL) {
			AdresseAnzeigen(pAktuellerKontakt->adressen);

			printf("Handelt es sich um eine private oder geschaeftliche Adresse? (0 oder 1):\n");
			fflush(stdout);
			scanf("%d%c",&typ,&buffer);

			if(typ == 0) {
				aTyp = privateAdresse;
				pAktuellerKontakt->adressen->typ = aTyp;
			} else if (typ == 1) {
				aTyp = geschaeftlicheAdresse;
				pAktuellerKontakt->adressen->typ = aTyp;
			}

			printf("Geben Sie einen neue Strasse ein (leer = unveraendert): ");
			fflush(stdout);
			strasse = readStr();
			printf("Geben Sie einen neue Hausnummer ein (leer = unveraendert): ");
			fflush(stdout);
			hausnummer = readStr();
			printf("Geben Sie einen neue PLZ ein (leer = unveraendert): ");
			fflush(stdout);
			plz = readStr();
			printf("Geben Sie einen neue Stadt ein (leer = unveraendert): ");
			fflush(stdout);
			stadt = readStr();
			printf("Geben Sie einen neue Land ein (leer = unveraendert): ");
			fflush(stdout);
			land = readStr();

			if(strcmp(strasse,"") != 0) {
				pAktuellerKontakt->adressen->strasse = strasse;
			}

			if(strcmp(hausnummer,"") != 0) {
				pAktuellerKontakt->adressen->hausnummer = hausnummer;
			}

			if(strcmp(plz,"") != 0) {
				pAktuellerKontakt->adressen->plz = plz;
			}

			if(strcmp(stadt,"") != 0) {
				pAktuellerKontakt->adressen->stadt = stadt;
			}

			if(strcmp(land,"") != 0) {
				pAktuellerKontakt->adressen->land = land;
			}

		} else {
			printf("Adresse wurde nicht gefunden");
			SLEEP
		}
	}

	return pAktuellerKontakt;
}

Kontakt* MenuAddMail(Kontakt* pAktuellerKontakt) {
	MailAdressenTyp mTyp;
	char* mail;
	int typ;
	char buffer;

	printf("Handelt es sich um eine private oder geschaeftliche Mail-Adresse? (0 oder 1):\n");
	fflush(stdout);
	scanf("%d%c",&typ,&buffer);

	if(typ == 0) {
		mTyp = privateMail;
	} else if (typ == 1) {
		mTyp = geschaeftlicheMail;
	} else {
		return NULL;
	}

	printf("Mail-Adresse: ");
	fflush(stdout);
	mail = readStr();

	/* Fallunterscheidung ob erstes Element der Liste oder nicht, ansonsten Kontakt anlegen */
	if(pAktuellerKontakt->mailadressen == NULL) {
		pAktuellerKontakt->mailadressen = MailAdresseHinzufuegen(pAktuellerKontakt->mailadressen,NULL,mail,mTyp);
	} else {
		pAktuellerKontakt->mailadressen = letzteMailAdresse(pAktuellerKontakt->mailadressen);
		pAktuellerKontakt->mailadressen = MailAdresseHinzufuegen(pAktuellerKontakt->mailadressen->next,pAktuellerKontakt->mailadressen,mail,mTyp);
	}

	return pAktuellerKontakt;
}

Kontakt* MenuEditMail(Kontakt* pAktuellerKontakt) {
	MailAdressenTyp mTyp;
	char* mail;
	int typ;

	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Mail-Adressen-Nr ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt->mailadressen != NULL) {
			pAktuellerKontakt->mailadressen = ersteMailAdresse(pAktuellerKontakt->mailadressen);
		}

		pAktuellerKontakt->mailadressen = findeMailDurchID(pAktuellerKontakt->mailadressen,id);

		if(pAktuellerKontakt->mailadressen != NULL) {
			MailAdresseAnzeigen(pAktuellerKontakt->mailadressen);

			printf("Handelt es sich um eine private oder geschaeftliche Mail-Adresse? (0 oder 1):\n");
			fflush(stdout);
			scanf("%d%c",&typ,&buffer);

			if(typ == 0) {
				mTyp = privateAdresse;
				pAktuellerKontakt->mailadressen->typ = mTyp;
			} else if (typ == 1) {
				mTyp = geschaeftlicheAdresse;
				pAktuellerKontakt->mailadressen->typ = mTyp;
			}

			printf("Geben Sie eine neue Mail ein (leer = unveraendert): ");
			fflush(stdout);
			mail = readStr();

			if(strcmp(mail,"") != 0) {
				pAktuellerKontakt->mailadressen->mailadresse = mail;
			}
		} else {
			printf("Adresse wurde nicht gefunden");
			SLEEP
		}
	}

	return pAktuellerKontakt;
}

Kontakt* MenuAddPhone(Kontakt* pAktuellerKontakt) {
	TelefonNummerTyp tTyp;
	char* telefon;
	int typ;
	char buffer;

	printf("Handelt es sich um eine private oder geschaeftliche Festnetznummer, eine private oder geschaeftliche Mobilfunknummer oder eine private oder geschaeftliche Faxnummer? (0, 1, 2, 3, 4 oder 5):\n");
	fflush(stdout);
	scanf("%d%c",&typ,&buffer);

	if(typ == 0) {
		tTyp = festnetzPrivat;
	} else if (typ == 1) {
		tTyp = festnetzGeschaeftlich;
	} else if (typ == 2) {
		tTyp = mobilfunkPrivat;
	} else if (typ == 3) {
		tTyp = mobilfunkGeschaeftlich;
	} else if (typ == 4) {
		tTyp = faxPrivat;
	} else if (typ == 5) {
		tTyp = faxGeschaeftlich;
	} else {
		return NULL;
	}

	printf("Telefon-/Faxnummer: ");
	fflush(stdout);
	telefon = readStr();

	/* Fallunterscheidung ob erstes Element der Liste oder nicht, ansonsten Kontakt anlegen */
	if(pAktuellerKontakt->telefonnummern == NULL) {
		pAktuellerKontakt->telefonnummern = TelefonnummerHinzufuegen(pAktuellerKontakt->telefonnummern,NULL,telefon,tTyp);
	} else {
		pAktuellerKontakt->telefonnummern = letzteTelefonnummer(pAktuellerKontakt->telefonnummern);
		pAktuellerKontakt->telefonnummern = TelefonnummerHinzufuegen(pAktuellerKontakt->telefonnummern->next,pAktuellerKontakt->telefonnummern,telefon,tTyp);
	}

	return pAktuellerKontakt;
}

Kontakt* MenuEditPhone(Kontakt* pAktuellerKontakt) {
	TelefonNummerTyp tTyp;
	char* telefon;
	int typ;

	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Telefonnummer-ID ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt->telefonnummern != NULL) {
			pAktuellerKontakt->telefonnummern = ersteTelefonnummer(pAktuellerKontakt->telefonnummern);
		}

		pAktuellerKontakt->telefonnummern = findeTelefonDurchID(pAktuellerKontakt->telefonnummern,id);

		if(pAktuellerKontakt->telefonnummern != NULL) {
			TelefonnummerAnzeigen(pAktuellerKontakt->telefonnummern);

			printf("Handelt es sich um eine private oder geschaeftliche Festnetznummer, eine private oder geschaeftliche Mobilfunknummer oder eine private oder geschaeftliche Faxnummer? (0, 1, 2, 3, 4 oder 5):\n");
			fflush(stdout);
			scanf("%d%c",&typ,&buffer);

			if(typ == 0) {
				tTyp = festnetzPrivat;
				pAktuellerKontakt->telefonnummern->typ = tTyp;
			} else if (typ == 1) {
				tTyp = festnetzGeschaeftlich;
				pAktuellerKontakt->telefonnummern->typ = tTyp;
			} else if (typ == 2) {
				tTyp = mobilfunkPrivat;
				pAktuellerKontakt->telefonnummern->typ = tTyp;
			} else if (typ == 3) {
				tTyp = mobilfunkGeschaeftlich;
				pAktuellerKontakt->telefonnummern->typ = tTyp;
			} else if (typ == 4) {
				tTyp = faxPrivat;
				pAktuellerKontakt->telefonnummern->typ = tTyp;
			} else if (typ == 5) {
				tTyp = faxGeschaeftlich;
				pAktuellerKontakt->telefonnummern->typ = tTyp;
			}

			printf("Geben Sie eine neue Telefon-/Faxnummer ein: ");
			fflush(stdout);
			telefon = readStr();

			if(strcmp(telefon,"") != 0) {
				pAktuellerKontakt->telefonnummern->telefonnummer = telefon;
			}
		} else {
			printf("Telefonnummer wurde nicht gefunden");
			SLEEP
		}
	}

	return pAktuellerKontakt;
}

Kontakt* MenuFindContact(Kontakt* pAktuellerKontakt) {
	char* vorname;
	char* nachname;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie einen Vornamen ein: ");
		fflush(stdout);
		vorname = readStr();
		printf("Geben Sie einen Nachnamen ein: ");
		fflush(stdout);
		nachname = readStr();

		if(pAktuellerKontakt != NULL) {
			pAktuellerKontakt = ersterKontakt(pAktuellerKontakt);
		}

		pAktuellerKontakt = findeKontaktDurchNamen(pAktuellerKontakt,vorname,nachname);

		if(pAktuellerKontakt != NULL) {
			KontaktAnzeigen(pAktuellerKontakt);
		} else {
			printf("Kontakt wurde nicht gefunden");
			SLEEP
		}
	} else {
		printf("Es sind keine Kontakte vorhanden");
	}

	return pAktuellerKontakt;
}

Kontakt* MenuAdresseLoeschen(Kontakt* pAktuellerKontakt) {
	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Adress-Nr ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt->adressen != NULL) {
			pAktuellerKontakt->adressen = ersteAdresse(pAktuellerKontakt->adressen);
		}

		pAktuellerKontakt->adressen = findeAdresseDurchID(pAktuellerKontakt->adressen,id);

		if(pAktuellerKontakt->adressen != NULL) {
			pAktuellerKontakt->adressen = AdresseLoeschen(pAktuellerKontakt->adressen);
		} else {
			printf("Adresse wurde nicht gefunden");
			SLEEP
		}
	} else {
		printf("Es sind keine Adressen vorhanden");
		SLEEP
	}

	return pAktuellerKontakt;
}

Kontakt* MenuMailLoeschen(Kontakt* pAktuellerKontakt) {
	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Mail-Nr ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt->mailadressen != NULL) {
			pAktuellerKontakt->mailadressen = ersteMailAdresse(pAktuellerKontakt->mailadressen);
		}

		pAktuellerKontakt->mailadressen = findeMailDurchID(pAktuellerKontakt->mailadressen,id);

		if(pAktuellerKontakt->mailadressen != NULL) {
			pAktuellerKontakt->mailadressen = MailAdresseLoeschen(pAktuellerKontakt->mailadressen);
		} else {
			printf("Mail-Adresse wurde nicht gefunden");
			SLEEP
		}
	} else {
		printf("Es sind keine Mail-Adressen vorhanden");
		SLEEP
	}

	return pAktuellerKontakt;
}

Kontakt* MenuTelefonLoeschen(Kontakt* pAktuellerKontakt) {
	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Telefon-ID ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		if(pAktuellerKontakt->telefonnummern != NULL) {
			pAktuellerKontakt->telefonnummern = ersteTelefonnummer(pAktuellerKontakt->telefonnummern);
		}

		pAktuellerKontakt->telefonnummern = findeTelefonDurchID(pAktuellerKontakt->telefonnummern,id);

		if(pAktuellerKontakt->telefonnummern != NULL) {
			pAktuellerKontakt->telefonnummern = TelefonnummerLoeschen(pAktuellerKontakt->telefonnummern);
		} else {
			printf("Adresse wurde nicht gefunden");
			SLEEP
		}
	} else {
		printf("Es sind keine Adressen vorhanden");
		SLEEP
	}

	return pAktuellerKontakt;
}

Kontakt* MenuKontaktLoeschen(Kontakt* pAktuellerKontakt) {
	int id;
	char buffer;

	if(pAktuellerKontakt != NULL) {
		printf("Geben Sie die Kontakt-Nr ein: ");
		fflush(stdout);
		scanf("%d%c",&id,&buffer);

		pAktuellerKontakt = findeKontaktDurchID(ersterKontakt(pAktuellerKontakt),id);

		if(pAktuellerKontakt != NULL) {
			pAktuellerKontakt = KontaktLoeschen(pAktuellerKontakt);
		} else {
			printf("Kontakt wurde nicht gefunden");
			SLEEP
		}
	} else {
		printf("Es sind keine Kontakte vorhanden");
		SLEEP
	}

	return pAktuellerKontakt;
}

Kontakt* MenuAlleKontakteLoeschen(Kontakt* pAktuellerKontakt) {
	if(pAktuellerKontakt != NULL) {
		AlleKontakteLoeschen(pAktuellerKontakt);					/* Alle Kontakte loeschen */
	}

	return NULL;
}

void SelectionWrong() {
	WARNING_ON
	printf("\nDiese Funktion steht nicht zur Verfuegung. Bitte wiederholen Sie Ihre Eingabe\n");	/* Fehler, da Auswahl nicht vorhanden */
	WARNING_OFF
	fflush(stdout);
	SLEEP

	return;
}

void Quit(Kontakt* pAktuellerKontakt) {
	pAktuellerKontakt = MenuAlleKontakteLoeschen(pAktuellerKontakt);					/* Alle Kontakte loeschen */
	exit(0);												/* Programm beenden */
}
