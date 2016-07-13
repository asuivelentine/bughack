/*
 * kontakt.h
 *
 *  Created on: 11.01.2015
 *      Author: DEDE
 */

#ifndef UEB9_DYNAMISCH_KONTAKT_H_
#define UEB9_DYNAMISCH_KONTAKT_H_

typedef enum adressenTyp{
	privateAdresse = 0,
	geschaeftlicheAdresse = 1
} AdressenTyp;

typedef enum mailAdressenTyp{
	privateMail = 0,
	geschaeftlicheMail = 1
} MailAdressenTyp;

typedef enum telefonNummerTyp{
	festnetzPrivat = 0,
	festnetzGeschaeftlich = 1,
	mobilfunkPrivat = 2,
	mobilfunkGeschaeftlich = 3,
	faxPrivat = 4,
	faxGeschaeftlich = 5
} TelefonNummerTyp;

typedef struct addresse{
	int id;
	AdressenTyp typ;
	char* strasse;
	char* hausnummer;
	char* plz;
	char* stadt;
	char* land;

	struct addresse* prev;
	struct addresse* next;
} Adresse;

typedef struct mail{
	int id;
	MailAdressenTyp typ;
	char* mailadresse;

	struct mail* prev;
	struct mail* next;
} Mail;

typedef struct telefon{
	int id;
	TelefonNummerTyp typ;
	char* telefonnummer;

	struct telefon* prev;
	struct telefon* next;
} Telefon;

typedef struct kontakt{
	int id;
	char* vorname;
	char* nachname;

	Adresse* adressen;
	Mail* mailadressen;
	Telefon* telefonnummern;

	struct kontakt* prev;
	struct kontakt* next;
} Kontakt;

Adresse* AdresseHinzufuegen(Adresse* pCurrent, Adresse* pPrev, AdressenTyp pTyp, char* pStrasse, char* pHausnummer, char* pPlz, char* pStadt, char* pLand);
void AdresseAnzeigen(Adresse* pCurrent);
void AlleAdressenAnzeigen(Adresse* pCurrent);
Adresse* AdresseLoeschen(Adresse* pCurrent);
Adresse* AlleAdressenLoeschen(Adresse* pCurrent);

Mail* MailAdresseHinzufuegen(Mail* pCurrent, Mail* pPrev, char* pMail, MailAdressenTyp pTyp);
void MailAdresseAnzeigen(Mail* pCurrent);
void AlleMailAdressenAnzeigen(Mail* pCurrent);
Mail* MailAdresseLoeschen(Mail* pCurrent);
Mail* AlleMailAdressenLoeschen(Mail* pCurrent);

Telefon* TelefonnummerHinzufuegen(Telefon* pCurrent, Telefon* pPrev, char* pTelefonnummer, TelefonNummerTyp pTyp);
void TelefonnummerAnzeigen(Telefon* pCurrent);
void AlleTelefonnummernAnzeigen(Telefon* pCurrent);
Telefon* TelefonnummerLoeschen(Telefon* pCurrent);
Telefon* AlleTelefonnummernLoeschen(Telefon* pCurrent);

Kontakt* KontaktHinzufuegen(Kontakt* pCurrent, Kontakt* pPrev, char* pVorname, char* pNachname);
void KontaktAnzeigen(Kontakt* pCurrent);
void AlleKontakteAnzeigen(Kontakt* pCurrent);
Kontakt* KontaktLoeschen(Kontakt* pCurrent);
Kontakt* AlleKontakteLoeschen(Kontakt* pCurrent);

Adresse* findeAdresseDurchID(Adresse* pCurrent, int pID);
Mail* findeMailDurchID(Mail* pCurrent, int pID);
Telefon* findeTelefonDurchID(Telefon* pCurrent, int pID);
Kontakt* findeKontaktDurchNamen(Kontakt* pCurrent, char* pVorname, char* pNachname);
Kontakt* findeKontaktDurchID(Kontakt* pCurrent, int pID);

Adresse* ersteAdresse(Adresse* pCurrent);
Adresse* letzteAdresse(Adresse* pCurrent);
int anzahlAdressen(Adresse* pCurrent);

Mail* ersteMailAdresse(Mail* pCurrent);
Mail* letzteMailAdresse(Mail* pCurrent);
int anzahlMailAdressen(Mail* pCurrent);

Telefon* ersteTelefonnummer(Telefon* pCurrent);
Telefon* letzteTelefonnummer(Telefon* pCurrent);
int anzahlTelefonnummern(Telefon* pCurrent);

Kontakt* ersterKontakt(Kontakt* pCurrent);
Kontakt* letzterKontakt(Kontakt* pCurrent);
int anzahlKontakte(Kontakt* pCurrent);

#endif /* UEB9_DYNAMISCH_KONTAKT_H_ */
