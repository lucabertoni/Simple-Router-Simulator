/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------  Librerie definite dal programmatore  ----------*/
#include "common.h"

/*=====  End of INCLUSIONI  ======*/


/*================================================
=            IMPLEMENTAZIONI FUNZIONI            =
================================================*/
/**
 *
 * Cosa fa			:			Stampa un messaggio nello stdout o stderr
 * output			:			intero, 0 = stdout | 1 = stderror
 *
 */
void print(int output,char* message){
	fprintf(output == 0 ? stdout : stderr,message);
}

/**
 *
 * Cosa fa						:			Esplode una stringa su un carattere
 * stringa_da_esplodere			:			stringa, stringa da esplodere sul carattere
 * separatore					:			carattere, carattere sul quale esplodere la stringa
 * Ritorna						:			aRet -> array di stringhe, stringhe estratte dall'explode sul carattere
 *
 */
char **explode(char *stringa_da_esplodere,int separatore){
	char **aRet;		// Array di stringhe estratto con l'explode
	char carattere;		// Carattere estratto dalla stringa
	char *app;			// Variabile di appoggio
	int ctr;

	aRet	= malloc(sizeof(char**));
	*aRet	= malloc(sizeof(char*));
	app 	= malloc(sizeof(char*));	// Stringa di appoggio per l'estrazione temporanea di una sottostringa dalla stringa da esplodere

	if (strchr(stringa_da_esplodere,separatore) == NULL){
		return aRet;
	}

	ctr = 0;
	app = strtok (stringa_da_esplodere,"|");
	while (app != NULL)
	{
		aRet[ctr] = malloc(sizeof(char*));
		strcpy(aRet[ctr++],app);
		//printf ("%s\n",app);
		app = strtok (NULL, "|");
	}

	return aRet;
}

/**
 *
 * Cosa fa			:			Prende in input dallo stdin un carattere
 * Ritorna			:			int, codice ascii carattere inserito
 *
 */
int get_commandline_char(){
	return fgetc(stdin);;
}
/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/