/*==================================
=            INCLUSIONI            =
==================================*/
/*----------  Librerie definite dal programmatore  ----------*/
#include "router.h"
#include "../lib/netlib.h"
/*=====  End of INCLUSIONI  ======*/


/*================================================
=            IMPLEMENTAZIONI FUNZIONI            =
================================================*/

/**
 *
 * Cosa fa			:			Imposta il router per l'avvio
 * router			:			t_router, Riferimento alla struct che contiene le impostazioni del router
 * argv				:			array di stringhe, così formato:
 *									[0] => "nome programma"
 *									[1] => "192.168.0.1" (ip router)
 *
 */
void router_setup(t_router *router, char *argv[]){
	unsigned long ip_address;		// Indirizzo Ip del router

	/**
	 *
	 * Cosa fa			:			Converte un indirizzo ip da stringa (192.168.0.1) a intero
	 * char_ip			:			stringa, ip in formato stringa, es: 192.168.0.1
	 * Ritorna			:			unsigned long, ip convertito
	 *
	 */
	ip_address = netlib_aton(argv[1]);
	
	/**
	 *
	 * Cosa fa			:			Imposta l'ip del router
	 * router			:			t_router, struct che identifica il router
	 *
	 */	
	router_set_ip(router,ip_address);
}

/**
 *
 * Cosa fa			:			Imposta l'ip del router
 * router			:			t_router, struct che identifica il router
 *
 */
void router_set_ip(t_router *router,unsigned long ip){
	router->ip = ip;
}

/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/