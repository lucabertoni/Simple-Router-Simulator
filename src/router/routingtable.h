#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H

/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/

/*----------  Librerie definite dal programmatore  ----------*/

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
	int ip;			// Ip corrente
	int next_hop;	// Passo successivo
	int peso;		// Peso per raggiungere il nodo successivo
}routing_table_row;

// Struct che definisce l'intera tabella di routing basandosi sulle singole righe della routing table
typedef struct routing_table
{
	struct routing_table_row *table_rows;
}routing_table;

/*----------  Funzioni  ----------*/

/**
 *
 * Cosa fa			:			Carica la tabella di routing dal file ROUTING_TABLE_FILE
 * table			:			routing_table, Tabella di routing nel quale caricare il file della tabella di routing
 * Ritorna			:			bRet -> intero, 1 = Tutto ok | 0 = Errore
 *
 */
int routingtable_load_table(routing_table *table);

/**
 *
 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo routing_table
 * Ritorna			:			table -> puntatore a struct routing_table, Struct contenente la definizione della tabella di routing
 *
 */
routing_table *initialize_table_memory();

/**
 *
 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
 * table			:			table*, puntatore all'area di memoria della struct che identifica la tabella di routing
 *
 */
void release_table_memory(routing_table *table);
/*=====  End of PROTOTIPI  ======*/
#endif