#include <stdio.h>

#include "common.h"

/**
 *
 * Cosa fa			:			Stampa un messaggio nello stdout o stderr
 * output			:			intero, 0 = stdout | 1 = stderror
 *
 */
void print(int output,char* message){
	fprintf(output == 0 ? stdout : stderr,message);
}