/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <arpa/inet.h>

/*=====  End of INCLUSIONI  ======*/

#ifndef NETLIB_H
#define NETLIB_H

/*=================================
=            PROTOTIPI            =
=================================*/

/*----------  Funzioni  ----------*/

/**
 *
 * Cosa fa			:			Converte un indirizzo ip da stringa (192.168.0.1) a intero
 * char_ip			:			stringa, ip in formato stringa, es: 192.168.0.1
 * Ritorna			:			unsigned long, ip convertito
 *
 */
unsigned long netlib_aton(char *char_ip);

/**

	TODO:
	- Implementare netlib_ntoa

 */
char *netlib_ntoa(unsigned long ip_address);

/*=====  End of PROTOTIPI  ======*/

#endif