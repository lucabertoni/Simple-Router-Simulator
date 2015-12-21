/*==================================
=            INCLUSIONI            =
==================================*/
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
 * Ritorna			:			unsigned long, ip convertito
 *
 */
unsigned long netlib_aton(char *char_ip){
	struct in_addr ip_address;

	inet_aton(char_ip,&ip_address);

	return ip_address.s_addr;
}

/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/