#ifndef COMMON_H
#define COMMON_H

/*=================================
=            PROTOTIPI            =
=================================*/

/*----------  Funzioni  ----------*/
/**
 *
 * Cosa fa			:			Stampa un messaggio nello stdout o stderror
 * output			:			intero, 0 = stdout | 1 = stderror
 *
 */
void print(int output,char* message);

/**
 *
 * Cosa fa						:			Esplode una stringa su un carattere
 * stringa_da_esplodere			:			stringa, stringa da esplodere sul carattere
 * separatore					:			carattere, carattere sul quale esplodere la stringa
 * Ritorna						:			aRet -> array di stringhe, stringhe estratte dall'explode sul carattere
 *
 */
char **explode(char *stringa_da_esplodere,int separatore);

/*=====  End of PROTOTIPI  ======*/
#endif