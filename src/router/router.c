/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdlib.h>
#include <signal.h>

/*----------  Librerie definite dal programmatore  ----------*/
#include "router.h"
#include "../lib/netlib.h"
#include "../lib/common.h"
#include "routingtable.h"

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
void release_router_memory(t_router *router){
	// Se non è già stata rilasciata la memoria, la rilascio
	if(router != 0){
		free(router);
		router = NULL;
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
	routing_table *table;	// Tabella di routing
	t_node *node;			// Nodo di rete di partenza con referenza ai nodi direttamente collegati

	// Di default è in errore
	bError = 1;

	/**
	 *
	 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo routing_table
	 * Ritorna			:			table -> struct routing_table, Struct contenente la definizione della tabella di routing
	 *
	 */
	table = initialize_table_memory();

	// Carico la tabella di routing in memoria
	/**
	 *
	 * Cosa fa			:			Carica la tabella di routing dal file ROUTING_TABLE_FILE
	 * table			:			routing_table, Tabella di routing nel quale caricare il file della tabella di routing
	 * Ritorna			:			bRet -> intero, 1 = Tutto ok | 0 = Errore
	 *
	 */
	bError = !(routingtable_load_table(table));
	if(bError){
		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
		 * table			:			routing_table, puntatore all'area di memoria della struct che identifica la tabella di routing
		 *
		 */
		release_table_memory(table);
		return bError;
	}

	// Setto il signale SIGINT in modo che punti alla funzione che termina correttamente l'esecuzione del programma
	signal(SIGINT,router_stop);

	/**
	 *
	 * Cosa fa			:			Esegue un parse della tabella di routing trasformandola in un insieme di nodi e collegamenti con annessi pesi, senza però cicli
	 * table			:			routing_table, puntatore alla definizione della tabella di routing
	 * starting_node_ip	:			int, indirizzo ip del primo nodo (nodo radice)
	 * Ritorna			:			node -> t_node, puntatore al nodo di rete (che contiene dei sottonodi)
	 *
	 */
	node = routingtable_parse_table(table, router->ip);

	/**
	 *
	 * Cosa fa			:			Mette il router in modalità listen in attesa di una connessione da parte di un host
	 * router			:			t_router, definizione del router da utilizzare
	 * node				:			t_node, definizione della rete sotto forma di nodi e collegamenti con annessi pesi
	 *
	 */
	router_listen(router,node);

	/**
	 *
	 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
	 * table			:			routing_table, puntatore all'area di memoria della struct che identifica la tabella di routing
	 *
	 */
	release_table_memory(table);
	bError = 0;
	return bError;
}

/**
 *
 * Cosa fa			:			Termina l'esecuzione del router
 *
 */
void router_stop(){
	print(0,"Esecuzione del router terminata correttamente.\n");
	print(0,"/=====================================/\n");

	exit(0);
}

/**
 *
 * Cosa fa			:			Mette il router in modalità listen in attesa di una connessione da parte di un host
 * router			:			t_router, definizione del router da utilizzare
 * node				:			t_node, definizione della rete sotto forma di nodi e collegamenti con annessi pesi
 *
 */
void router_listen(t_router *router,t_node *node){
	/**
	
		TODO:
		- Implementare funzione
	
	 */
	
}
/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/