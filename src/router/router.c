/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdlib.h>

/*----------  Librerie definite dal programmatore  ----------*/
#include "router.h"
#include "../lib/netlib.h"
#include "../lib/common.h"

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


/**
 *
 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo t_router
 * Ritorna			:			router -> struct t_router, Struct contenente la definizione del router
 *
 */
t_router *initialize_router_memory(){
	t_router *router;

	// Alloco la memoria per la struct
	router = malloc(sizeof(t_router));

	return router;
}

/**
 *
 * Cosa fa			:			Libera la memoria occupata dalla struct del router
 * router			:			t_router*, puntatore all'area di memoria della struct che identifica il router
 *
 */
void free_router_memory(t_router *router){
	// Se non è già stata rilasciata la memoria, la rilascio
	if(router != 0){
		free(router);
	}
}

/**
 *
 * Cosa fa			:			Avvia il router
 * router			:			t_router, Struct contente le informazioni del router necessarie per il suo avvio
 * Ritorna			:			bError -> intero, 0 = Ok | 1 = Errore
 *
 */
int router_start(t_router *router){
	int bError;

	// Di default è in errore
	bError = 1;

	return bError;
}
/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/