/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <string.h>

/*----------  Librerie definite dal programmatore  ----------*/
#include "netlib.h"
/*=====  End of INCLUSIONI  ======*/

/*================================================
=            IMPLEMENTAZIONI FUNZIONI            =
================================================*/

/**
 *
 * Cosa fa			:			Converte un indirizzo ip da stringa (192.168.0.1) a intero
 * char_ip			:			stringa, ip in formato stringa, es: 192.168.0.1
 * Ritorna			:			unsigned long, ip convertito. 0 = errore
 *
 */
unsigned long netlib_aton(char *char_ip){
	struct in_addr ip_address;
	int bOk;

	bOk = inet_aton(char_ip,&ip_address);

	// Se non ci sono stati errori ritorno l'ip, altrimenti ritorno 0
	return bOk > 0 ? ip_address.s_addr : 0;
}

/**
 *
 * Cosa fa			:			Converte un indirizzo ip da intero al suo corrispondente stringa (192.168.0.1)
 * ip_address		:			unsigned long, indirizzo ip
 * string_ip_address:			stringa, indirizzo ip convertito in stringa
 *
 */
void netlib_ntoa(unsigned long ip_address, char *string_ip_address){
	struct in_addr struct_ip;

	struct_ip.s_addr = ip_address;
	strcpy(string_ip_address,inet_ntoa(struct_ip));
}
/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/