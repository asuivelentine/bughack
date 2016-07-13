/*
 * functions.h
 *
 *  Created on: 12.01.2015
 *      Author: DEDE
 */

#ifndef UEB9_DYNAMISCH_FUNCTIONS_H_
#define UEB9_DYNAMISCH_FUNCTIONS_H_

Kontakt* MenuMainMenu(Kontakt* pAktuellerKontakt);
Kontakt* MenuPrintContacts(Kontakt* pAktuellerKontakt);
Kontakt* MenuImport(Kontakt* pAktuellerKontakt);
Kontakt* MenuExport(Kontakt* pAktuellerKontakt);
Kontakt* MenuPrintContact(Kontakt* pAktuellerKontakt);
Kontakt* MenuAddContact(Kontakt* pAktuellerKontakt);
Kontakt* MenuEditContact(Kontakt* pAktuellerKontakt);
Kontakt* MenuEditName(Kontakt* pAktuellerKontakt);
Kontakt* MenuAddAddress(Kontakt* pAktuellerKontakt);
Kontakt* MenuEditAddress(Kontakt* pAktuellerKontakt);
Kontakt* MenuAddMail(Kontakt* pAktuellerKontakt);
Kontakt* MenuEditMail(Kontakt* pAktuellerKontakt);
Kontakt* MenuAddPhone(Kontakt* pAktuellerKontakt);
Kontakt* MenuEditPhone(Kontakt* pAktuellerKontakt);
Kontakt* MenuFindContact(Kontakt* pAktuellerKontakt);
Kontakt* MenuAdresseLoeschen(Kontakt* pAktuellerKontakt);
Kontakt* MenuMailLoeschen(Kontakt* pAktuellerKontakt);
Kontakt* MenuTelefonLoeschen(Kontakt* pAktuellerKontakt);
Kontakt* MenuKontaktLoeschen(Kontakt* pAktuellerKontakt);
Kontakt* MenuAlleKontakteLoeschen(Kontakt* pAktuellerKontakt);

void SelectionWrong();
void Quit(Kontakt* pAktuellerKontakt);

#endif /* UEB9_DYNAMISCH_FUNCTIONS_H_ */
