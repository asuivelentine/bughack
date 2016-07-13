#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "kontakt.h"
#include "menu.h"
#include "functions.h"
#include "readStr.h"
#include "replaceStr.h"
#include "dbLaden.h"
#include "dbSpeichern.h"
#include "main.h"

/*
 * Verwendung: test = replaceStr(test, "suchstring", "ersetzung");
 * Bsp:
 * char* test = "Dies ist der Text";
 * test = replaceStr(test, "Dies", "Das");
 * ==> test = "Das ist der Text";
 */

char* replaceStr(const char* str, const char* searchstring, const char* replacement) {
	char *ret, *r;
	const char *p, *q;
	size_t oldlen = strlen(searchstring);
	size_t count, retlen, newlen = strlen(replacement);

	if (oldlen != newlen) {
		for (count = 0, p = str; (q = strstr(p, searchstring)) != NULL; p = q + oldlen)
			count++;
		retlen = p - str + strlen(p) + count * (newlen - oldlen);
	} else
		retlen = strlen(str);

	if ((ret = malloc(retlen + 1)) == NULL)
		return NULL;

	for (r = ret, p = str; (q = strstr(p, searchstring)) != NULL; p = q + oldlen) {
		ptrdiff_t l = q - p;
		memcpy(r, p, l);
		r += l;
		memcpy(r, replacement, newlen);
		r += newlen;
	}
	strcpy(r, p);

	return ret;
}
