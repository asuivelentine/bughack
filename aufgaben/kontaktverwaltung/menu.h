/*
 * menu.h
 *
 *  Created on: 11.01.2015
 *      Author: DEDE
 */

#ifndef UEB9_DYNAMISCH_MENU_H_
#define UEB9_DYNAMISCH_MENU_H_

#ifdef WIN32 /* Wenn Windows 32 & 64-Bit --> WIN32 ist eine symbolische Konstante des Betriebssystems */
	#include <windows.h>
//	#define CLEAR printf("---------------\n");
	#define CLEAR			system("cls");																				/* Leeren des Konsolenfensters in Windows */
	#define SLEEP 			Sleep(3000); 																				/* Verzögert des Programs in Windows (in Millisekunden) */
	#define WARNING_ON		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C );								/* Farbe Rot */
	#define	WARNING_OFF		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07 );								/* Farbe Weiß */
#else /* Wenn Linux --> Linux hat keine symbolische Konstante */
	#include <unistd.h>
	#define CLEAR			system("clear");																			/* Leeren des Terminal-Fensters in Linux */
	#define SLEEP 			sleep(3); 																					/* Verzögert des Programs in Linux (in Sekunden) */
	#define WARNING_ON  	printf("\x1b[31m");																			/* Farbe Rot */
	#define WARNING_OFF		printf("\x1b[0m");																			/* Farbe Weiß */
#endif

#define SEPARATION_LINE printf("\n--------------------------------------------------------------------------------");

typedef enum typMenu {
	Hauptmenu = 0,
	MenuKontakteAnsehen = 1,
	MenuKontakteImportieren = 2,
	MenuKontakteExportieren = 3,
	MenuKontaktAnsehen = 4,
	MenuKontaktHinzufuegen = 5,
	MenuKontaktBearbeiten = 6,
	MenuNameBearbeiten = 7,
	MenuAnschriftHinzufuegen = 8,
	MenuAnschriftBearbeiten = 9,
	MenuMailAdresseHinzufuegen = 10,
	MenuMailAdresseBearbeiten = 11,
	MenuTelefonnummerHinzufuegen = 12,
	MenuTelefonnummerBearbeiten = 13,
	MenuKontaktSuchen = 14
} MenuTyp;

typedef struct menu{
	char* ueberschrift;
	char* inhalt;
	char* eintraege;

	MenuTyp type;
} Menu;

Menu* mainMenu;
Menu* showContacts;
Menu* importContacts;
Menu* exportContacts;
Menu* showContact;
Menu* addContact;
Menu* editContact;
Menu* editName;
Menu* addAddress;
Menu* editAddress;
Menu* addMailAddress;
Menu* editMailAddress;
Menu* addTelephoneNumber;
Menu* editTelephoneNumber;
Menu* searchContact;

Menu* initMenu(Menu* current, MenuTyp typ);
Kontakt* printMenu(Menu* current, Kontakt* contactList);

#endif /* UEB9_DYNAMISCH_MENU_H_ */
