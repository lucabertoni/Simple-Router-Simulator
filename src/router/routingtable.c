/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdlib.h>
#include <string.h>

#include <stdio.h> // DA TOGLIERE
/*----------  Librerie definite dal programmatore  ----------*/
#include "routingtable.h"
#include "../lib/common.h"
#include "../lib/netlib.h"

/*=====  End of INCLUSIONI  ======*/


/*================================================
=            IMPLEMENTAZIONI FUNZIONI            =
================================================*/

/**
 *
 * Cosa fa			:			Carica la tabella di routing dal file ROUTING_TABLE_FILE
 * table			:			routing_table, Tabella di routing nel quale caricare il file della tabella di routing
 * Ritorna			:			bRet -> intero, 1 = Tutto ok | 0 = Errore
 *
 */
int routingtable_load_table(routing_table *table){
	FILE *fd;
	int bRet = 0;
	char riga_file[MAX_BUFFER_SIZE];
	char **aRow;
	int ctr;
	routing_table_row *app;

	// Apro il collegamento verso il file dell routing table
	fd = fopen(ROUTING_TABLE_FILE,"r");
	if(fd <= 0){
		return bRet;
	}

	(*table->table_rows) = malloc(sizeof(routing_table_row));
	app = *table->table_rows;
	ctr = 0;

	// Leggo le righe della tabella
	while(!feof(fd)){
		fgets(riga_file,MAX_BUFFER_SIZE,fd);

		// Esplodo la stringa sulla |
		// aRow sarà così formata:
		// aRow[0] => 192.168.0.10 (Ip destinazione)
		// aRow[1] => 192.168.0.11 (Next Hop)
		// aRow[2] => 1 (Peso)
		explode(&aRow,riga_file,'|');

		// Aggiungo gli elementi estratti alla struct
		/**
		 *
		 * Cosa fa			:			Converte un indirizzo ip da stringa (192.168.0.1) a intero
		 * char_ip			:			stringa, ip in formato stringa, es: 192.168.0.1
		 * Ritorna			:			unsigned long, ip convertito. 0 = errore
		 *
		 */
		(*table->table_rows)->ip 		= netlib_aton(aRow[0]);
		(*table->table_rows)->next_hop 	= netlib_aton(aRow[1]);
		(*table->table_rows)->peso		= atoi(aRow[2]);

		printf("IND|%u|IP|%d|\n",*table->table_rows,(*table->table_rows)->ip);
		(*table->table_rows)++;
		//(*table->table_rows) = malloc(sizeof(routing_table_row));
		ctr++;
	}
	// Riporto il puntatore a puntare al primo elemento della tabella d routing

	if(ctr > 0 ){
/*		
		(*table->table_rows)--;
		ctr--;
*/		
	}

	*table->table_rows = app;
	printf("============================================\n");
	printf("IND|%u|IP|%d|\n",*table->table_rows,(*table->table_rows)->ip);
	printf("IND|%u|IP|%d|\n",*table->table_rows,(*table->table_rows)->next_hop);
	printf("IND|%u|IP|%d|\n",*table->table_rows,(*table->table_rows)->peso);
	free(aRow);

	fclose(fd);
	printf("RETURN\n");
	return 1;
}

/**
 *
 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo routing_table
 * Ritorna			:			table -> puntatore a struct routing_table, Struct contenente la definizione della tabella di routing
 *
 */
routing_table *initialize_table_memory(){
	routing_table *table;

	// Alloco la memoria per la struct
	table = malloc(sizeof(routing_table));

	// Alloco la memoria per l'array di struct delle righe della tabella
	table->table_rows = malloc(sizeof(routing_table_row*));

	return table;
}

/**
 *
 * Cosa fa			:			Libera la memoria occupata dalla struct della tabella di routing
 * table			:			routing_table, puntatore all'area di memoria della struct che identifica la tabella di routing
 *
 */
void release_table_memory(routing_table *table){
	// Se la tabella non è già stata rilasciata, la rilascio
	if (table->table_rows != 0){
		release_table_row_memory(*table->table_rows);

		free(table->table_rows);
		table->table_rows = NULL;
	}

	if(table !=0){
		free(table);
		table = NULL;
	}
}

/**
 *
 * Cosa fa			:			Esegue un parse della tabella di routing trasformandola in un insieme di nodi e collegamenti con annessi pesi, senza però cicli
 * table			:			routing_table, puntatore alla definizione della tabella di routing
 * starting_node_ip	:			int, indirizzo ip del primo nodo (nodo radice)
 * Ritorna			:			node -> t_node, puntatore al nodo di rete (che contiene dei sottonodi)
 *
 */
t_node *routingtable_parse_table(routing_table *table, int starting_node_ip){
	routing_table_row *first_table_row;
	t_node *node;

	return node;
}

/**
 *
 * Cosa fa			:			Libera la memoria occupata dalla struct della singola riga tabella di routing
 * table_row		:			routing_table_row*, puntatore all'area di memoria della struct che identifica la singola riga tabella di routing
 *
 */
void release_table_row_memory(routing_table_row *table_row){
	for(table_row;table_row != 0;table_row++){
printf("RELEASE IP|%d|\n", table_row->ip);	// Da togliere
		free(table_row);
	}
}
/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/