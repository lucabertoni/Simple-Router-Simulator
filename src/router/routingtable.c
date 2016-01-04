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
 * Ritorna			:			bRet -> intero, >=1 = Tutto ok | 0 = Errore, numero di elementi che contiene la tabella
 *
 */
int routingtable_load_table(routing_table *table){
	FILE *fd;
	int ctr;
	char riga_file[MAX_BUFFER_SIZE];
	char **aRow;

	ctr = 0;
	
	// Apro il collegamento verso il file dell routing table
	fd = fopen(ROUTING_TABLE_FILE,"r");
	if(fd <= 0){
		return ctr;
	}
	
	// Leggo le righe della tabella
	while(fgets(riga_file,MAX_BUFFER_SIZE,fd) != NULL){
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
		table->table_rows = realloc(table->table_rows,sizeof(routing_table_row) * (ctr + 1));

		// Se la riallocazione di memoria della tabella fallisce termino l'esecuzione
		if(table->table_rows == NULL){
			free(aRow);
			fclose(fd);
		        return 0;	// Errore, ritorno 0
		}
		table->table_rows[ctr].ip	 		= netlib_aton(aRow[0]);
		table->table_rows[ctr].next_hop			= netlib_aton(aRow[1]);
		table->table_rows[ctr].peso			= atoi(aRow[2]);
		
		// TODO: Cancellare questo commento
		// printf("IND|%u|IP|%u|\n",table->table_rows,table->table_rows[ctr].ip);
		ctr++;

	}
	/*	
		TODO: Rimuovere questo commento, era necessario per fare dei test

		printf("============================================\n");
		printf("IND|%u|IP|%u|\n",table->table_rows,table->table_rows[0].ip);
		printf("IND|%u|NEXT HOP|%u|\n",table->table_rows,table->table_rows[0].next_hop);
		printf("IND|%u|PESO|%u|\n",table->table_rows,table->table_rows[0].peso);

		printf("============================================\n");
		printf("IND|%u|IP|%u|\n",table->table_rows,table->table_rows[1].ip);
		printf("IND|%u|NEXT HOP|%u|\n",table->table_rows,table->table_rows[1].next_hop);
		printf("IND|%u|PESO|%u|\n",table->table_rows,table->table_rows[1].peso);
	*/
	free(aRow);

	fclose(fd);
	return ctr;
}
	
/**
 *
 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo routing_table
 * table			:			routing_table *, puntatore alla struct di tipo routing_table
 * Ritorna			:			bRet -> intero, 0 = Ok | 1 = Errore
 *
 */
int initialize_table_memory(routing_table **table){
	int bRet;
	bRet = 1;	// Di default stabilisco che ci sia un errore
	
	// Alloco la memoria per la struct
	*table = malloc(sizeof(routing_table));
	// Se c'è stato un errore durante l'allocazione, termino la funzione
	if(*table == NULL){
		return bRet;
	}

	// Alloco la memoria per l'array di struct delle righe della tabella
	(*table)->table_rows = malloc(sizeof(routing_table_row));
	if((*table)->table_rows == NULL){
		return bRet;
	}

	return (!bRet);	// Ritorno 0 nel caso sia arrivato correttamente fino qui
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
		free(table->table_rows);
		table->table_rows = NULL;
	}

	if(table != 0){
		free(table);
		table = NULL;
	}
	
	return;
}

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
int routingtable_parse_table(routing_table *table,int table_size,int router_ip,t_node **node){
	int bRet,i;
	bRet = 1;

	for(i = 0;i<table_size;i++){
		printf("|%d|\n",table->table_rows[i].ip);
		
	}
	
	return (!bRet); // Ritorno 0, tutto ok
}

/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/
