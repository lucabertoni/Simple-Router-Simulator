#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H

/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/

/*----------  Librerie definite dal programmatore  ----------*/
#include "router.h"

/*=====  End of INCLUSIONI  ======*/

#define ROUTING_TABLE_FILE	"./routingtable.txt"
#define MAX_BUFFER_SIZE		100
/*=================================
=            PROTOTIPI            =
=================================*/

/*----------  Definizione tipi/struct  ----------*/

// Struct che definisce una singola riga della routing table
typedef struct routing_table_row
{
	unsigned long ip;			// Ip destinazione
	unsigned long next_hop;		// Passo successivo
	int peso;					// Peso per raggiungere il nodo successivo
}routing_table_row;

// Struct che definisce l'intera tabella di routing basandosi sulle singole righe della routing table
typedef struct routing_table
{
	routing_table_row *table_rows;
}routing_table;

/*----------  Funzioni  ----------*/

/**
 *
 * Cosa fa			:			Carica la tabella di routing dal file ROUTING_TABLE_FILE
 * table			:			routing_table, Tabella di routing nel quale caricare il file della tabella di routing
 * Ritorna			:			bRet -> intero, >=1 = Tutto ok | 0 = Errore, numero di elementi che contiene la tabella
 *
 */
int routingtable_load_table(routing_table *table);

/**
 *
 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo routing_table
 * table			:			routing_table *, puntatore alla struct di tipo routing_table
 * Ritorna			:			bRet -> intero, 0 = Ok | 1 = Errore
 *
 */
int initialize_table_memory(routing_table **table);

/**
 *
 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
 * table			:			table*, puntatore all'area di memoria della struct che identifica la tabella di routing
 *
 */
void release_table_memory(routing_table *table);

/**
 *
 * Cosa fa			:			Esegue un parse della tabella di routing trasformandola in un insieme di nodi e collegamenti con annessi pesi, senza però cicli
 * table			:			routing_table, puntatore alla definizione della tabella di routing
 * table_size			:			int, numero di elementi nella tabella di routing
 * starting_node_ip		:			int, indirizzo ip del primo nodo (nodo radice)
 * node				:			t_node, puntatore al nodo di rete (che contiene dei sottonodi)
 * Ritorna			:			bRet -> intero, 0 = Tutto ok | 1 = Errore
 *
 */
int routingtable_parse_table(routing_table *table,int table_size,int router_ip,t_node **node);
/*=====  End of PROTOTIPI  ======*/
#endif
