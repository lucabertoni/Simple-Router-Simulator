#include "routingtable.h"

#ifndef ROUTER_H
#define ROUTER_H

/*=================================
=            PROTOTIPI            =
=================================*/

/*----------  Struct  ----------*/

typedef struct t_router			// Router header description
{
	unsigned long ip;			// Router ip
}t_router;

/*----------  Funzioni  ----------*/

/**
 *
 * Cosa fa			:			Imposta il router per l'avvio
 * router			:			t_router, Riferimento alla struct che contiene le impostazioni del router
 *
 */
void router_setup(t_router *router, char *argv[]);

/**
 *
 * Cosa fa			:			Imposta l'ip del router
 * router			:			t_router, struct che identifica il router
 * ip				:			intero, ip del router da settare
 *
 */
void router_set_ip(t_router *router, unsigned long ip);

/**
 *
 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo t_router
 * Ritorna			:			router -> struct t_router, Struct contenente la definizione del router
 *
 */
t_router *initialize_router_memory();

/**
 *
 * Cosa fa			:			Libera la memoria occupata dalla struct del router
 * router			:			t_router*, puntatore all'area di memoria della struct che identifica il router
 *
 */
void release_router_memory(t_router *router);

/**
 *
 * Cosa fa			:			Avvia il router
 * router			:			t_router, Struct contente le informazioni del router necessarie per il suo avvio
 * Ritorna			:			bError -> intero, 0 = Ok | 1 = Errore
 *
 */
int router_start(t_router *router);

/**
 *
 * Cosa fa			:			Termina l'esecuzione del router
 *
 */
void router_stop();
/*=====  End of PROTOTIPI  ======*/

#endif