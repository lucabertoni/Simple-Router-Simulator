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
 * arr_ptr						:			array, puntatore all'array di stringhe
 * stringa_da_esplodere			:			stringa, stringa da esplodere sul carattere
 * separatore					:			carattere, carattere sul quale esplodere la stringa
 *
 */
int explode(char ***arr_ptr, char *str, char delimiter){
  char *src = str, *end, *dst;
  char **arr;
  int size = 1, i;
  while ((end = strchr(src, delimiter)) != NULL)
    {
      ++size;
      src = end + 1;
    }

  arr = malloc(size * sizeof(char *) + (strlen(str) + 1) * sizeof(char));

  src = str;
  dst = (char *) arr + size * sizeof(char *);
  for (i = 0; i < size; ++i){
      if ((end = strchr(src, delimiter)) == NULL)
        end = src + strlen(src);
      arr[i] = dst;
      strncpy(dst, src, end - src);
      dst[end - src] = '\0';
      dst += end - src + 1;
      src = end + 1;
  }
  *arr_ptr = arr;

  return size;
}  
/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/