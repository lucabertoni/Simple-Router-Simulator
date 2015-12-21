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

/*=====  End of PROTOTIPI  ======*/

#endif