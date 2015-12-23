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
 *
 * Cosa fa			:			Converte un indirizzo ip da intero al suo corrispondente stringa (192.168.0.1)
 * ip_address		:			unsigned long, indirizzo ip
 * string_ip_address:			stringa, indirizzo ip convertito in stringa
 *
 */
void netlib_ntoa(unsigned long ip_address, char *string_ip_address);

/*=====  End of PROTOTIPI  ======*/

#endif