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

int dbSpeichern(Kontakt* pAktuellerKontakt, char* pDateiname) {
	FILE* datei;
	int anzZeichen;

	int openKontakte = 0;
	int openKontakt = 0;
	int openAdressen = 0;
	int openMailadressen = 0;
	int openTelefonnummern = 0;

	Adresse* bufferAdresse;
	Mail* bufferMail;
	Telefon* bufferTelefon;

	if ((datei = fopen(pDateiname, "w")) != NULL) {
		if(pAktuellerKontakt != NULL) {
			if(dtdSpeichern() == 1) {
				pAktuellerKontakt = ersterKontakt(pAktuellerKontakt);
				fprintf(datei, "<?xml version=\"1.0\"?>\n");
				fprintf(datei, "<!DOCTYPE kontakte SYSTEM \"kontakte.dtd\">\n");
				fprintf(datei, "<kontakte>\n");
				openKontakte = 1;
			} else { //DTD konnte nicht erstellt werden
				return 0;
			}
		} else {
			return 0;
		}

		while(pAktuellerKontakt != NULL && openKontakte == 1) {
			fprintf(datei, "\t<kontakt>\n");
			openKontakt = 1;

			fprintf(datei, "\t\t<kontaktID>");
			fprintf(datei, "%d", pAktuellerKontakt->id);
			fprintf(datei, "</kontaktID>\n");

			anzZeichen = strlen(pAktuellerKontakt->vorname);
			fprintf(datei, "\t\t<vorname>");
			fwrite(pAktuellerKontakt->vorname,anzZeichen,1,datei);
			fprintf(datei, "</vorname>\n");

			anzZeichen = strlen(pAktuellerKontakt->nachname);
			fprintf(datei, "\t\t<nachname>");
			fwrite(pAktuellerKontakt->nachname,anzZeichen,1,datei);
			fprintf(datei, "</nachname>\n");

			if(pAktuellerKontakt->adressen != NULL && openKontakt == 1 && openAdressen == 0) {
				fprintf(datei, "\t\t<adressen>\n");
				pAktuellerKontakt->adressen = ersteAdresse(pAktuellerKontakt->adressen);
				bufferAdresse = pAktuellerKontakt->adressen;
				openAdressen = 1;
			}

			while(pAktuellerKontakt->adressen != NULL) {
				fprintf(datei, "\t\t\t<adresse>\n");
				fprintf(datei, "\t\t\t\t<adressID>");
				fprintf(datei, "%d", pAktuellerKontakt->adressen->id);
				fprintf(datei, "</adressID>\n");

				if(pAktuellerKontakt->adressen->typ == privateAdresse) {
					fprintf(datei, "\t\t\t\t<adressTyp>privateAdresse</adressTyp>\n");

				} else if(pAktuellerKontakt->adressen->typ == geschaeftlicheAdresse) {
					fprintf(datei, "\t\t\t\t<adressTyp>geschaeftlicheAdresse</adressTyp>\n");
				} else {
					return 0;
				}

				anzZeichen = strlen(pAktuellerKontakt->adressen->strasse);
				fprintf(datei, "\t\t\t\t<strasse>");
				fwrite(pAktuellerKontakt->adressen->strasse,anzZeichen,1,datei);
				fprintf(datei, "</strasse>\n");

				anzZeichen = strlen(pAktuellerKontakt->adressen->hausnummer);
				fprintf(datei, "\t\t\t\t<hausnummer>");
				fwrite(pAktuellerKontakt->adressen->hausnummer,anzZeichen,1,datei);
				fprintf(datei, "</hausnummer>\n");

				anzZeichen = strlen(pAktuellerKontakt->adressen->plz);
				fprintf(datei, "\t\t\t\t<plz>");
				fwrite(pAktuellerKontakt->adressen->plz,anzZeichen,1,datei);
				fprintf(datei, "</plz>\n");

				anzZeichen = strlen(pAktuellerKontakt->adressen->stadt);
				fprintf(datei, "\t\t\t\t<stadt>");
				fwrite(pAktuellerKontakt->adressen->stadt,anzZeichen,1,datei);
				fprintf(datei, "</stadt>\n");

				anzZeichen = strlen(pAktuellerKontakt->adressen->land);
				fprintf(datei, "\t\t\t\t<land>");
				fwrite(pAktuellerKontakt->adressen->land,anzZeichen,1,datei);
				fprintf(datei, "</land>\n");

				fprintf(datei, "\t\t\t</adresse>\n");
				pAktuellerKontakt->adressen = pAktuellerKontakt->adressen->next;
			}

			if(openKontakt == 1 && openAdressen == 1) {
				fprintf(datei, "\t\t</adressen>\n");
				pAktuellerKontakt->adressen = bufferAdresse;
				openAdressen = 0;
			}

			if(pAktuellerKontakt->mailadressen != NULL && openKontakt == 1 && openMailadressen == 0) {
				fprintf(datei, "\t\t<mailadressen>\n");
				pAktuellerKontakt->mailadressen = ersteMailAdresse(pAktuellerKontakt->mailadressen);
				bufferMail = pAktuellerKontakt->mailadressen;
				openMailadressen = 1;
			}

			while(pAktuellerKontakt->mailadressen != NULL) {
				fprintf(datei, "\t\t\t<mailadresse>\n");
				fprintf(datei, "\t\t\t\t<mailID>");
				fprintf(datei, "%d", pAktuellerKontakt->mailadressen->id);
				fprintf(datei, "</mailID>\n");

				if(pAktuellerKontakt->mailadressen->typ == privateMail) {
					fprintf(datei, "\t\t\t\t<mailTyp>privateMail</mailTyp>\n");
				} else if(pAktuellerKontakt->mailadressen->typ == geschaeftlicheMail) {
					fprintf(datei, "\t\t\t\t<mailTyp>geschaeftlicheMail</mailTyp>\n");
				} else {
					return 0;
				}

				anzZeichen = strlen(pAktuellerKontakt->mailadressen->mailadresse);
				fprintf(datei, "\t\t\t\t<mail>");
				fwrite(pAktuellerKontakt->mailadressen->mailadresse,anzZeichen,1,datei);
				fprintf(datei, "</mail>\n");

				fprintf(datei, "\t\t\t</mailadresse>\n");
				pAktuellerKontakt->mailadressen = pAktuellerKontakt->mailadressen->next;
			}

			if(openKontakt == 1 && openMailadressen == 1) {
				fprintf(datei, "\t\t</mailadressen>\n");
				pAktuellerKontakt->mailadressen = bufferMail;
				openMailadressen = 0;
			}

			if(pAktuellerKontakt->mailadressen != NULL && openKontakt == 1 && openTelefonnummern == 0) {
				fprintf(datei, "\t\t<telefonnummern>\n");
				pAktuellerKontakt->telefonnummern = ersteTelefonnummer(pAktuellerKontakt->telefonnummern);
				bufferTelefon = pAktuellerKontakt->telefonnummern;
				openTelefonnummern = 1;
			}

			while(pAktuellerKontakt->telefonnummern != NULL) {
				fprintf(datei, "\t\t\t<telefonnummer>\n");
				fprintf(datei, "\t\t\t\t<telefonID>");
				fprintf(datei, "%d", pAktuellerKontakt->telefonnummern->id);
				fprintf(datei, "</telefonID>\n");

				if(pAktuellerKontakt->telefonnummern->typ == festnetzPrivat) {
					fprintf(datei, "\t\t\t\t<telefonTyp>festnetzPrivat</telefonTyp>\n");
				} else if(pAktuellerKontakt->telefonnummern->typ == festnetzGeschaeftlich) {
					fprintf(datei, "\t\t\t\t<telefonTyp>festnetzGeschaeftlich</telefonTyp>\n");
				} else if(pAktuellerKontakt->telefonnummern->typ == mobilfunkPrivat) {
					fprintf(datei, "\t\t\t\t<telefonTyp>mobilfunkPrivat</telefonTyp>\n");
				} else if(pAktuellerKontakt->telefonnummern->typ == mobilfunkGeschaeftlich) {
					fprintf(datei, "\t\t\t\t<telefonTyp>mobilfunkGeschaeftlich</telefonTyp>\n");;
				} else if(pAktuellerKontakt->telefonnummern->typ == faxPrivat) {
					fprintf(datei, "\t\t\t\t<telefonTyp>faxPrivat</telefonTyp>\n");
				} else if(pAktuellerKontakt->telefonnummern->typ == faxGeschaeftlich) {
					fprintf(datei, "\t\t\t\t<telefonTyp>faxGeschaeftlich</telefonTyp>\n");;
				} else {
					return 0;
				}

				anzZeichen = strlen(pAktuellerKontakt->telefonnummern->telefonnummer);
				fprintf(datei, "\t\t\t\t<telefon>");
				fwrite(pAktuellerKontakt->telefonnummern->telefonnummer,anzZeichen,1,datei);
				fprintf(datei, "</telefon>\n");

				fprintf(datei, "\t\t\t</telefonnummer>\n");
				pAktuellerKontakt->telefonnummern = pAktuellerKontakt->telefonnummern->next;
			}

			if(openKontakt == 1 && openTelefonnummern == 1) {
				fprintf(datei, "\t\t</telefonnummern>\n");
				pAktuellerKontakt->telefonnummern = bufferTelefon;
				openTelefonnummern = 0;
			}

			fprintf(datei, "\t</kontakt>\n");
			pAktuellerKontakt = pAktuellerKontakt->next;
			openKontakt = 0;
		}
		fprintf(datei, "</kontakte>");
		openKontakte = 0;
		fclose(datei);

		//Überprüfen ob auch alle Tags wieder geschlossen wurden, sonst ist die Syntax falsch gewesen
		if(openKontakte == 0 || openKontakt == 0 || openAdressen == 0 || openMailadressen == 0 || openTelefonnummern == 0) {
			return 1;
		} else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

int dtdSpeichern() {
	FILE* datei;

	if ((datei = fopen("kontakte.dtd", "w")) != NULL) {
		fprintf(datei, "<!ELEMENT kontakte (\n");
		fprintf(datei, "\t<!ELEMENT kontakt (\n");
		fprintf(datei, "\t\t<!ELEMENT kontaktID ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t<!ELEMENT vorname ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t<!ELEMENT nachname ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t<!ELEMENT adressen (\n");
		fprintf(datei, "\t\t\t<!ELEMENT adresse (\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT adressID ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT adressTyp ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT strasse ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT hausnummer ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT plz ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT stadt ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT land ( #PCDATA ) >\n");
		fprintf(datei, "\t\t\t) >\n");
		fprintf(datei, "\t\t) >,\n");
		fprintf(datei, "\t\t<!ELEMENT mailadressen (\n");
		fprintf(datei, "\t\t\t<!ELEMENT mailadresse (\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT mailID ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT mailTyp ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT mail ( #PCDATA ) >\n");
		fprintf(datei, "\t\t\t) >\n");
		fprintf(datei, "\t\t) >,\n");
		fprintf(datei, "\t\t<!ELEMENT telefonnummern (\n");
		fprintf(datei, "\t\t\t<!ELEMENT telefonnummer (\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT telefonID ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT telefonTyp ( #PCDATA ) >,\n");
		fprintf(datei, "\t\t\t\t<!ELEMENT telefon ( #PCDATA ) >\n");
		fprintf(datei, "\t\t\t) >\n");
		fprintf(datei, "\t\t) >\n");
		fprintf(datei, "\t) >\n");
		fprintf(datei, ") >");

		fclose(datei);
		return 1;
	} else {
		return 0;
	}
}
