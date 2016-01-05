/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdlib.h>
#include <signal.h>

#include <stdio.h> // TODO: Togliere!!!
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

// TODO: Cancellare questa funzione!
void router_print_node(t_node node,int nTab){
	int i,i2;
	char sApp[255];
	char sApp1[255];

        netlib_ntoa(node.ip,sApp);
        for(i = 0;i<(nTab-1);i++)	printf("\t");
	printf("PADRE|%s|\n",sApp);
	for(i = 0;node.next_nodes[i].ip != 0;i++){
		netlib_ntoa(node.next_nodes[i].ip,sApp1);
		for(i2 = 0;i2<nTab;i2++)	printf("\t");
		printf("FIGLIO|%s|%d|\n",sApp1,node.next_nodes[i].peso_nodo);
		router_print_node(node.next_nodes[i],nTab + 1);
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
	routing_table *table,*app_table;// Tabella di routing e tabella di routing di appoggio per il parse
	t_node *node;			// Nodo di rete di partenza con referenza ai nodi direttamente collegati

	// Di default è in errore
	bError = 1;
	
	// Setto il signale SIGINT in modo che punti alla funzione che termina correttamente l'esecuzione del programma
	signal(SIGINT,router_stop);
	
	/**
	 *
	 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo routing_table
	 * table			:			routing_table *, puntatore alla struct di tipo routing_table
	 * Ritorna			:			bRet -> intero, 0 = Ok | 1 = Errore
	 *
	 */
        bError = initialize_table_memory(&table);
	if(bError){
		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
		 * table			:			routing_table, puntatore all'area di memoria della struct che identifica la tabella di routing
		 *
		 */
		release_table_memory(table);
		print(1,"Errore durante l'inizializzazione della memoria necessaria per contenere la tabella di routing.\n");
		return bError;
	}

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
		print(1,"Errore durante il caricamento della tabella di routing dal file.\n");
		return bError;
	}

	/**
	 *
	 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo t_node
	 * table			:			t_node *, puntatore alla struct di tipo t_node
	 * Ritorna			:			bRet -> intero, 0 = Ok | 1 = Errore
	 *
	 */
        bError = initialize_node_memory(&node);
	if(bError){
		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
		 * table			:			routing_table, puntatore all'area di memoria della struct che identifica la tabella di routing
		 *
		 */
		release_table_memory(table);
		
		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct del grafo di rete
		 * node				:			t_node, puntatore all'area di memoria della struct che identifica il grafo (primo nodo)
		 *
		 */
		release_node_memory(node);
		
		print(1,"Errore durante l'inizializzazione della memoria necessaria per contenere il grafo di rete.\n");
		return bError;
	}
	
	////////////////////
	// TODO: Cancellare questo blocco
	int i;
	char sApp[255];
	char sApp1[255];
	for(i = 0;i<table->table_size;i++){
		netlib_ntoa(table->table_rows[i].ip,sApp);
		netlib_ntoa(table->table_rows[i].next_hop,sApp1);
		printf("IPTABLE|%s|%s|%d|\n",sApp,sApp1,table->table_rows[i].peso);
	}
	////////////////////

	/**
	 *
	 * Cosa fa			:			Esegue un parse della tabella di routing trasformandola in un insieme di nodi e collegamenti con annessi pesi, senza però cicli
	 * table			:			routing_table, puntatore alla definizione della tabella di routing
	 * starting_node_ip		:			int, indirizzo ip del primo nodo (nodo radice)
	 * node				:			t_node, puntatore al nodo di rete radice(che contiene dei sottonodi)
	 * peso_destinazione		:			intero, peso per raggiungere il nodo, di default il primo dovrebbe essere 0 dato che si tratta del nodo corrente
	 * Ritorna			:			bRet -> intero, 0 = Errore | 1 = Tutto ok
	 *
	 * N.B.				:			Passare una copia della tabella (table) perchè man mano che viene scansionata se vengono trovate delle corrispondenze i valori(ip,next_hop,peso) delle righe vengono impostate a -1
	 *
	 */
	bError = !(routingtable_parse_table(table,router->ip,&node,0));
	if(bError){
		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
		 * table			:			routing_table, puntatore all'area di memoria della struct che identifica la tabella di routing
		 *
		 */
		release_table_memory(table);

		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct del grafo di rete
		 * node				:			t_node, puntatore all'area di memoria della struct che identifica il grafo (primo nodo)
		 *
		 */
		release_node_memory(node);
		
		print(1,"Errore durante il parsing della tabella di routing.\n");
		return bError;
	}

	// TODO: Togliere questa chiamata a funzione e funzione
	// router_print_node(*node,1);
	netlib_ntoa(node->next_nodes[0].next_nodes[0].ip,sApp);
	printf("SOTTONODO|%s|\n",sApp);
	/**
	 *
	 * Cosa fa			:			Mette il router in modalità listen in attesa di una connessione da parte di un host
	 * router			:			t_router, definizione del router da utilizzare
	 * node				:			t_node, definizione della rete sotto forma di nodi e collegamenti con annessi pesi
	 *
	 */
	//router_listen(router,node);

	/**
	 *
	 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
	 * table			:			routing_table, puntatore all'area di memoria della struct che identifica la tabella di routing
	 *
	 */
	release_table_memory(table);

	/**
	 *
	 * Cosa fa			:			Libera la memoria occupata dalla struct del grafo di rete
	 * node				:			t_node, puntatore all'area di memoria della struct che identifica il grafo (primo nodo)
	 *
	 */
	release_node_memory(node);
		
	return bError;	// Se sono arrivato qui senza problemi ritorno 0, ovvero Tutto ok!
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

/**
 *
 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo t_node
 * table			:			t_node *, puntatore alla struct di tipo t_node
 * Ritorna			:			bRet -> intero, 0 = Ok | 1 = Errore
 *
 */
int initialize_node_memory(t_node **node){
	int bRet;
	bRet = 1;	// Di default stabilisco che ci sia un errore
	
	// Alloco la memoria per la struct
	*node = malloc(sizeof(t_node));
	// Se c'è stato un errore durante l'allocazione, termino la funzione
	if(*node == NULL){
		return bRet;
	}

	// Alloco la memoria per l'array di struct delle righe della tabella
	(*node)->next_nodes = malloc(sizeof(t_node));
	if((*node)->next_nodes == NULL){
		return bRet;
	}

	return (!bRet);	// Ritorno 0 nel caso sia arrivato correttamente fino qui  
}

/**
 *
 * Cosa fa			:			Libera la memoria occupata dalla struct del grafo di rete
 * node				:			t_node, puntatore all'area di memoria della struct che identifica il grafo (primo nodo)
 *
 */
void release_node_memory(t_node *node){
	if (node->next_nodes != 0){
		free(node->next_nodes);
		node->next_nodes = NULL;
	}

	if(node != 0){
		free(node);
		node = NULL;
	}

	return;
}

/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/
