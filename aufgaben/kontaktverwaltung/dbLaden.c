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

Kontakt* dbLaden(Kontakt* pAktuellerKontakt, char* pDateiname) {
	FILE* datei;

	if(pAktuellerKontakt != NULL) {	//Liste ist leer
		pAktuellerKontakt = letzterKontakt(pAktuellerKontakt);
	}

	if ((datei = fopen(pDateiname, "r")) != NULL) {
		if(dbCheck(pDateiname) == 1) {
			char puffer[BUF];
			char* tag;
			int len;

			int openKontakte = 0;
			int openKontakt = 0;
			int openAdressen = 0;
			int openMailadressen = 0;
			int openTelefonnummern = 0;

			char* adressTyp;
			char* vorname;
			char* nachname;
			char* strasse;
			char* hausnummer;
			char* plz;
			char* stadt;
			char* land;
			char* mailTyp;
			char* mail;
			char* telefonTyp;
			char* telefon;

			while(fgets(puffer, BUF, datei) != NULL ) {
				tag = realloc(tag,BUF*sizeof(char));
				strcpy(tag,puffer);

				/*
				 * Speichert ab, welche Ebene auf bzw. zu geht
				 * Überprüft, ob eine Ebene geöffnet ist, z.B. dürfen Adressen nur innerhalb von <kontakt> sein
				 * Speichert die eingelesenen Werte
				 */
				if(strstr(puffer,"<kontakte>") != 0) {
					openKontakte = 1;
				}

				if(strstr(puffer,"</kontakte>") != 0) {
					openKontakte = 0;
				}

				if(strstr(puffer,"<kontakt>") != 0 && openKontakte == 1) {
					if(pAktuellerKontakt == NULL) {
						pAktuellerKontakt = KontaktHinzufuegen(pAktuellerKontakt,NULL,"","");
					} else {
						pAktuellerKontakt = letzterKontakt(pAktuellerKontakt);
						pAktuellerKontakt = KontaktHinzufuegen(pAktuellerKontakt->next,pAktuellerKontakt,"","");
					}

					openKontakt = 1;
				}

				if(strstr(puffer,"</kontakt>") != 0 && openKontakte == 1) {
					pAktuellerKontakt->vorname = vorname;
					pAktuellerKontakt->nachname = nachname;

					openKontakt = 0;
				}

				if(strstr(puffer,"<adressen>") != 0 && openKontakte == 1 && openKontakt == 1 && openAdressen == 0) {
					openAdressen = 1;
				}

				if(strstr(puffer,"</adressen>") != 0) {
					openAdressen = 0;
				}

				if(strstr(puffer,"<mailadressen>") != 0 && openKontakte == 1 && openKontakt == 1) {
					openMailadressen = 1;
				}

				if(strstr(puffer,"</mailadressen>") != 0 && openKontakte == 1 && openKontakt == 1) {
					openMailadressen = 0;
				}

				if(strstr(puffer,"<telefonnummern>") != 0 && openKontakte == 1 && openKontakt == 1) {
					openTelefonnummern = 1;
				}

				if(strstr(puffer,"</telefonnummern>") != 0 && openKontakte == 1 && openKontakt == 1) {
					openTelefonnummern = 0;
				}


				/*
				 * Listen anlegen
				 */
				if(strstr(puffer,"</adresse>") != 0) {
					AdressenTyp aTyp;

					if(strcmp(adressTyp,"privateAdresse") == 0) {
						aTyp = privateAdresse;
					} else if(strcmp(adressTyp,"geschaeftlicheAdresse") == 0) {
						aTyp = geschaeftlicheAdresse;
					} else { //Fehler -> Programm beenden, da sonst Abstürze nicht vermeidbar
						Quit(pAktuellerKontakt);
					}

					if(pAktuellerKontakt->adressen == NULL) {
						pAktuellerKontakt->adressen = AdresseHinzufuegen(pAktuellerKontakt->adressen,NULL,aTyp,strasse,hausnummer,plz,stadt,land);
					} else {
						pAktuellerKontakt->adressen = letzteAdresse(pAktuellerKontakt->adressen);
						pAktuellerKontakt->adressen = AdresseHinzufuegen(pAktuellerKontakt->adressen->next,pAktuellerKontakt->adressen,aTyp,strasse,hausnummer,plz,stadt,land);
					}
				}

				if(strstr(puffer,"</mailadresse>") != 0 && openKontakte == 1 && openKontakt == 1) {
					MailAdressenTyp mTyp;

					if(strcmp(mailTyp,"privateMail") == 0) {
						mTyp = privateMail;
					} else if(strcmp(mailTyp,"geschaeftlicheMail") == 0) {
						mTyp = geschaeftlicheMail;
					} else { //Fehler -> Programm beenden, da sonst Abstürze nicht vermeidbar
						Quit(pAktuellerKontakt);
					}

					if(pAktuellerKontakt->mailadressen == NULL) {
						pAktuellerKontakt->mailadressen = MailAdresseHinzufuegen(pAktuellerKontakt->mailadressen,NULL,mail,mTyp);
					} else {
						pAktuellerKontakt->mailadressen = letzteMailAdresse(pAktuellerKontakt->mailadressen);
						pAktuellerKontakt->mailadressen = MailAdresseHinzufuegen(pAktuellerKontakt->mailadressen->next,pAktuellerKontakt->mailadressen,mail,mTyp);
					}
				}

				if(strstr(puffer,"</telefonnummer>") != 0 && openKontakte == 1 && openKontakt == 1) {
					TelefonNummerTyp tTyp;

					if(strcmp(telefonTyp,"festnetzPrivat") == 0) {
						tTyp = festnetzPrivat;
					} else if(strcmp(telefonTyp,"festnetzGeschaeftlich") == 0) {
						tTyp = festnetzGeschaeftlich;
					} else if(strcmp(telefonTyp,"mobilfunkPrivat") == 0) {
						tTyp = mobilfunkPrivat;
					} else if(strcmp(telefonTyp,"mobilfunkGeschaeftlich") == 0) {
						tTyp = mobilfunkGeschaeftlich;
					} else if(strcmp(telefonTyp,"faxPrivat") == 0) {
						tTyp = faxPrivat;
					} else if(strcmp(telefonTyp,"faxGeschaeftlich") == 0) {
						tTyp = faxGeschaeftlich;
					} else { //Fehler -> Programm beenden, da sonst Abstürze nicht vermeidbar
						Quit(pAktuellerKontakt);
					}

					if(pAktuellerKontakt->telefonnummern == NULL) {
						pAktuellerKontakt->telefonnummern = TelefonnummerHinzufuegen(pAktuellerKontakt->telefonnummern,NULL,telefon,tTyp);
					} else {
						pAktuellerKontakt->telefonnummern = letzteTelefonnummer(pAktuellerKontakt->telefonnummern);
						pAktuellerKontakt->telefonnummern = TelefonnummerHinzufuegen(pAktuellerKontakt->telefonnummern->next,pAktuellerKontakt->telefonnummern,telefon,tTyp);
					}
				}

				/*
				 * String ermitteln und speichern, aber nur, wenn Tag an richtiger Stelle
				 */

				if(strstr(puffer,"<vorname>") != 0 && openKontakt == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<vorname>","");
					tag = replaceStr(tag,"</vorname>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					vorname = malloc(len*sizeof(char));
					strcpy(vorname,tag);
				}

				if(strstr(puffer,"<nachname>") != 0 && openKontakt == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<nachname>","");
					tag = replaceStr(tag,"</nachname>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					nachname = malloc(len*sizeof(char));
					strcpy(nachname,tag);
				}

				if(strstr(puffer,"<adressTyp>") != 0 && openAdressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<adressTyp>","");
					tag = replaceStr(tag,"</adressTyp>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					adressTyp = malloc(len*sizeof(char));
					strcpy(adressTyp,tag);
				}

				if(strstr(puffer,"<strasse>") != 0 && openAdressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<strasse>","");
					tag = replaceStr(tag,"</strasse>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					strasse = malloc(len*sizeof(char));
					strcpy(strasse,tag);
				}

				if(strstr(puffer,"<hausnummer>") != 0 && openAdressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<hausnummer>","");
					tag = replaceStr(tag,"</hausnummer>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					hausnummer = malloc(len*sizeof(char));
					strcpy(hausnummer,tag);
				}

				if(strstr(puffer,"<plz>") != 0 && openAdressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<plz>","");
					tag = replaceStr(tag,"</plz>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					plz = malloc(len*sizeof(char));
					strcpy(plz,tag);
				}

				if(strstr(puffer,"<stadt>") != 0 && openAdressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<stadt>","");
					tag = replaceStr(tag,"</stadt>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					stadt = malloc(len*sizeof(char));
					strcpy(stadt,tag);
				}

				if(strstr(puffer,"<land>") != 0 && openAdressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<land>","");
					tag = replaceStr(tag,"</land>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					land = malloc(len*sizeof(char));
					strcpy(land,tag);
				}

				if(strstr(puffer,"<mailTyp>") != 0 && openMailadressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<mailTyp>","");
					tag = replaceStr(tag,"</mailTyp>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					mailTyp = malloc(len*sizeof(char));
					strcpy(mailTyp,tag);
				}

				if(strstr(puffer,"<mail>") != 0 && openMailadressen == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<mail>","");
					tag = replaceStr(tag,"</mail>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					mail = malloc(len*sizeof(char));
					strcpy(mail,tag);
				}

				if(strstr(puffer,"<telefonTyp>") != 0 && openTelefonnummern == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<telefonTyp>","");
					tag = replaceStr(tag,"</telefonTyp>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					telefonTyp = malloc(len*sizeof(char));
					strcpy(telefonTyp,tag);
				}

				if(strstr(puffer,"<telefon>") != 0 && openTelefonnummern == 1) {
					tag = replaceStr(tag,"\t","");
					tag = replaceStr(tag,"<telefon>","");
					tag = replaceStr(tag,"</telefon>","");
					tag = replaceStr(tag,"\n","");
					len = strlen(tag);
					telefon = malloc(len*sizeof(char));
					strcpy(telefon,tag);
				}
			}

			fclose(datei);
			return pAktuellerKontakt; //bisherige Kontakte mit neuen Kontakten
		} else {

			return pAktuellerKontakt; //bisherige Kontakte mit neuen Kontakten
		}
	} else { //Fehler beim Laden der Datei
		return pAktuellerKontakt; //bisherige Kontakte oder NULL
	}
}

int dbCheck(char* dateiname) {
	FILE* datei;

	if ((datei = fopen(dateiname, "r")) != NULL) {
		char puffer[BUF];
		/*
		 * oName = openTagNameDesTags
		 * cName = closeTagNameDesTags
		 */
		int oKontakte = 0;
		int cKontakte = 0;
		int oKontakt = 0;
		int cKontakt = 0;
		int oKontaktID = 0;
		int cKontaktID = 0;
		int oVorname = 0;
		int cVorname = 0;
		int oNachname = 0;
		int cNachname = 0;
		int oAdressen = 0;
		int cAdressen = 0;
		int oAdresse = 0;
		int cAdresse = 0;
		int oAdressID = 0;
		int cAdressID = 0;
		int oAdressTyp = 0;
		int cAdressTyp = 0;
		int oStrasse = 0;
		int cStrasse = 0;
		int oHausnummer = 0;
		int cHausnummer = 0;
		int oPLZ = 0;
		int cPLZ = 0;
		int oStadt = 0;
		int cStadt = 0;
		int oLand = 0;
		int cLand = 0;
		int oMailadressen = 0;
		int cMailadressen = 0;
		int oMailadresse = 0;
		int cMailadresse = 0;
		int oMailID = 0;
		int cMailID = 0;
		int oMailTyp = 0;
		int cMailTyp = 0;
		int oMail = 0;
		int cMail = 0;
		int oTelefonnummern = 0;
		int cTelefonnummern = 0;
		int oTelefonnummer = 0;
		int cTelefonnummer = 0;
		int oTelefonID = 0;
		int cTelefonID = 0;
		int oTelefonTyp = 0;
		int cTelefonTyp = 0;
		int oTelefon = 0;
		int cTelefon = 0;

		//Anzahl Open- und Close-Tags zählen
		while(fgets(puffer, BUF, datei) != NULL ) {
			if(strstr(puffer,"<kontakte>") != 0)
				oKontakte++;
			if(strstr(puffer,"</kontakte>") != 0)
				cKontakte++;
			if(strstr(puffer,"<kontakt>") != 0)
				oKontakt++;
			if(strstr(puffer,"</kontakt>") != 0)
				cKontakt++;
			if(strstr(puffer,"<kontaktID>") != 0)
				oKontaktID++;
			if(strstr(puffer,"</kontaktID>") != 0)
				cKontaktID++;
			if(strstr(puffer,"<vorname>") != 0)
				oVorname++;
			if(strstr(puffer,"</vorname>") != 0)
				cVorname++;
			if(strstr(puffer,"<nachname>") != 0)
				oNachname++;
			if(strstr(puffer,"</nachname>") != 0)
				cNachname++;
			if(strstr(puffer,"<adressen>") != 0)
				oAdressen++;
			if(strstr(puffer,"</adressen>") != 0)
				cAdressen++;
			if(strstr(puffer,"<adresse>") != 0)
				oAdresse++;
			if(strstr(puffer,"</adresse>") != 0)
				cAdresse++;
			if(strstr(puffer,"<adressID>") != 0)
				oAdressID++;
			if(strstr(puffer,"</adressID>") != 0)
				cAdressID++;
			if(strstr(puffer,"<adressTyp>") != 0)
				oAdressTyp++;
			if(strstr(puffer,"</adressTyp>") != 0)
				cAdressTyp++;
			if(strstr(puffer,"<strasse>") != 0)
				oStrasse++;
			if(strstr(puffer,"</strasse>") != 0)
				cStrasse++;
			if(strstr(puffer,"<hausnummer>") != 0)
				oHausnummer++;
			if(strstr(puffer,"</hausnummer>") != 0)
				cHausnummer++;
			if(strstr(puffer,"<plz>") != 0)
				oPLZ++;
			if(strstr(puffer,"</plz>") != 0)
				cPLZ++;
			if(strstr(puffer,"<stadt>") != 0)
				oStadt++;
			if(strstr(puffer,"</stadt>") != 0)
				cStadt++;
			if(strstr(puffer,"<land>") != 0)
				oLand++;
			if(strstr(puffer,"</land>") != 0)
				cLand++;
			if(strstr(puffer,"<mailadressen>") != 0)
				oMailadressen++;
			if(strstr(puffer,"</mailadressen>") != 0)
				cMailadressen++;
			if(strstr(puffer,"<mailadresse>") != 0)
				oMailadresse++;
			if(strstr(puffer,"</mailadresse>") != 0)
				cMailadresse++;
			if(strstr(puffer,"<mailID>") != 0)
				oMailID++;
			if(strstr(puffer,"</mailID>") != 0)
				cMailID++;
			if(strstr(puffer,"<mailTyp>") != 0)
				oMailTyp++;
			if(strstr(puffer,"</mailTyp>") != 0)
				cMailTyp++;
			if(strstr(puffer,"<mail>") != 0)
				oMail++;
			if(strstr(puffer,"</mail>") != 0)
				cMail++;
			if(strstr(puffer,"<telefonnummern>") != 0)
				oTelefonnummern++;
			if(strstr(puffer,"</telefonnummern>") != 0)
				cTelefonnummern++;
			if(strstr(puffer,"<telefonnummer>") != 0)
				oTelefonnummer++;
			if(strstr(puffer,"</telefonnummer>") != 0)
				cTelefonnummer++;
			if(strstr(puffer,"<telefonID>") != 0)
				oTelefonID++;
			if(strstr(puffer,"</telefonID>") != 0)
				cTelefonID++;
			if(strstr(puffer,"<telefonTyp>") != 0)
				oTelefonTyp++;
			if(strstr(puffer,"</telefonTyp>") != 0)
				cTelefonTyp++;
			if(strstr(puffer,"<telefon>") != 0)
				oTelefon++;
			if(strstr(puffer,"</telefon>") != 0)
				cTelefon++;
		}

		if(oKontakte != 1 && cKontakte != 1) { //Prüfen ob Wurzelelement nur einmal vorkommt und korrekt geschlossen wurde
			printf("Die XML-Datei ist fehlerhaft: Das Wurzelelement fehlt oder ist nicht korrekt\n");
			fclose(datei);
			return 0;
		} else {
			/*
			 * 1. Überprüfen ob die Anzahl openTags der Anzahl closeTags entspricht
			 * 2. Überprüfen, ob die Anzahl der Kontakte auch der Anzahl KontaktID, Vornamen und Nachnamen entspricht, da jeder Kontakt diese benötigt
			 * 3. Überprüfen, ob die Anzahl der Adressen auch der Anzahl AdressID, AdressTyp, Strasse, Hausnummer, PLZ, Stadt und Land entspricht
			 * 4. Überprüfen, ob die Anzahl der Mail-Adressen auch der Anzahl MailID, MailTyp, Mail entspricht
			 * 5. Überprüfen, ob die Anzahl der Telefonnummern auch der Anzahl TelefonID, TelefonTyp, Telefon entspricht
			 */
			if(oKontakt != cKontakt || oKontaktID != cKontaktID || oVorname != cVorname || oNachname != cNachname || oAdressen != cAdressen || cAdresse != oAdresse || oAdressID != cAdressID || oAdressTyp != cAdressTyp || oStrasse != cStrasse || oHausnummer != cHausnummer || oPLZ != cPLZ || oStadt != cStadt || oLand != cLand || oMailadressen != cMailadressen || oMailadresse != cMailadresse || oMailID != cMailID || oMailTyp != cMailTyp || oMail != cMail || oTelefonnummern != cTelefonnummern || oTelefonnummer != cTelefonnummer || oTelefonID != cTelefonID || oTelefonTyp != cTelefonTyp || oTelefon != cTelefon) {
				printf("Die XML-Datei ist fehlerhaft: Die Syntax ist nicht korrekt, da die Anzahl geoeffneter Tags nicht mit der Anzahl geschlossener Tags uebereinstimmt\n");
				fclose(datei);
				return 0;
			} else if(oKontakt != 0 && cKontakt != 0) {
				if(oKontakt != oKontaktID || oKontakt != oVorname || oKontakt != oNachname) { //closeTags entsprechen bereits den openTags und müssen nicht mehr geprüft werden
					printf("Die XML-Datei ist fehlerhaft: Die Syntax ist nicht korrekt, da die DTD nicht eingehalten wurde\n");
					fclose(datei);
					return 0;
				} else if(oAdresse != oAdressID || oAdresse != oAdressTyp || oAdresse != oStrasse || oAdresse != oHausnummer || oAdresse != oPLZ|| oAdresse != oStadt|| oAdresse != oLand) {
					printf("Die XML-Datei ist fehlerhaft: Die Syntax ist nicht korrekt, da die DTD nicht eingehalten wurde\n");
					fclose(datei);
					return 0;
				} else if(oMailadresse != oMailID || oMailadresse != oMailTyp || oMailadresse != oMail) {
					printf("Die XML-Datei ist fehlerhaft: Die Syntax ist nicht korrekt, da die DTD nicht eingehalten wurde\n");
					fclose(datei);
					return 0;
				} else if(oTelefonnummer != oMailID || oTelefonnummer != oTelefonTyp || oTelefonnummer != oTelefon) {
					printf("Die XML-Datei ist fehlerhaft: Die Syntax ist nicht korrekt, da die DTD nicht eingehalten wurde\n");
					fclose(datei);
					return 0;
				} else {
					printf("Es sind %d Kontakte vorhanden", oKontakt);
					fclose(datei);
					return 1;
				}
			} else {
				printf("Die XML-Datei ist fehlerhaft: Es muss mindestens ein Kontakt vorhanden sein");
				fclose(datei);
				return 0;
			}
		}
	} else {
		printf("Fehler beim Oeffnen der Datei!!!\n\n");
		return 0;
	}
}
