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
 * arr_ptr						:			array, puntatore all'array di stringhe
 * stringa_da_esplodere			:			stringa, stringa da esplodere sul carattere
 * separatore					:			carattere, carattere sul quale esplodere la stringa
 *
 */
int explode(char ***arr_ptr, char *str, char delimiter);

/*=====  End of PROTOTIPI  ======*/
#endif