/*
 * dbLaden.h
 *
 *  Created on: 11.01.2015
 *      Author: DEDE
 */

#ifndef UEB9_DYNAMISCH_DBLADEN_H_
#define UEB9_DYNAMISCH_DBLADEN_H_

#define BUF 1000 /* Max. Länge einer Zeile */

Kontakt* dbLaden(Kontakt* pAktuellerKontakt, char* pDateiname);
int dbCheck(char* pDateiname);
int dtdLaden();

#endif /* UEB9_DYNAMISCH_DBLADEN_H_ */
