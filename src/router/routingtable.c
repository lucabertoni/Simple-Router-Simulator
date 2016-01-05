/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdlib.h>
#include <string.h>

#include <stdio.h> // TODO: DA TOGLIERE
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
	int ctr,bRet;
	char riga_file[MAX_BUFFER_SIZE];
	char **aRow;

	ctr = bRet = 0;
	
	// Apro il collegamento verso il file dell routing table
	fd = fopen(ROUTING_TABLE_FILE,"r");
	if(fd <= 0){
		return bRet;
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
		        return bRet;	// Errore, ritorno 0
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
	table->table_size = ctr;
	
	free(aRow);

	fclose(fd);
	
	return (!bRet);	// Ritorno 1, tutto ok
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
 * starting_node_ip		:			int, indirizzo ip del primo nodo (nodo radice)
 * node				:			t_node, puntatore al nodo di rete radice(che contiene dei sottonodi)
 * peso_destinazione		:			intero, peso per raggiungere il nodo, di default il primo dovrebbe essere 0 dato che si tratta del nodo corrente
 * Ritorna			:			bRet -> intero, 0 = Errore | 1 = Tutto ok
 *
 * N.B.				:			Passare una copia della tabella (table) perchè man mano che viene scansionata se vengono trovate delle corrispondenze i valori(ip,next_hop,peso) delle righe vengono impostate a -1
 *
 */
int routingtable_parse_table(routing_table *table,int starting_node_ip,t_node **node, int peso_destinazione){
	int bRet,i,table_size,ctr,bError;
	t_node *app_node;			// Nodo di rete di appoggio estratto dalla ricorsione
	int ip,next_hop,peso;

	// TODO: Togliere queste definizioni e i print associati
	char sApp[255];
	char sApp1[255];
	char sApp2[255];
	int iapp;
	
	bRet = ctr = 0;				// ctr è il counter degli elementi inseriti in next_nodes, è necessario per il realloc della memoria
	table_size = table->table_size;
        
	// Inserisco come nodo radice, l'ip del nodo corrente e il peso per raggiungere il nodo corrente
	(*node)->ip = starting_node_ip;
	(*node)->peso_nodo = peso_destinazione;

	// Alloco la memoria necessaria per il nodo di appoggio
	/**
	 *
	 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo t_node
	 * table			:			t_node *, puntatore alla struct di tipo t_node
	 * Ritorna			:			bRet -> intero, 0 = Ok | 1 = Errore
	 *
	 */
        bError = initialize_node_memory(&app_node);
	if(bError){
		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct del grafo di rete
		 * node				:			t_node, puntatore all'area di memoria della struct che identifica il grafo (primo nodo)
		 *
		 */
		release_node_memory(app_node);
	        
		return 0;	// Ritorno 0, Errore
	}

	// TODO: Cancellare
	netlib_ntoa(starting_node_ip,sApp1);
	printf("CERCO|%s|\n",sApp1);

	// Aggiungo i figli del nodo corrente all'array di next_nodes, estraendoli dalla tabella
	for(i = 0;i<table_size;i++){
		ip = table->table_rows[i].ip;
		netlib_ntoa(ip,sApp1);
		printf("IP|%s|i|%d|\n",sApp1,i);
	        next_hop = table->table_rows[i].next_hop;
		peso = table->table_rows[i].peso;
		
		// Cerco le righe della tabella nelle quali è presente l'ip corrente (starting_node_ip) ed estrapolo gli ip di destinazione. Da essi estrapolo i loro figli nello stesso modo
		// Se l'ip del next_hop corrisponde all'ip corrente (starting_node_ip), estraggo l'ip di destinazione e lo inserisco nell'array di next_nodes, e lo passo al setaccio in ricorsione
		if(table->table_rows[i].next_hop == starting_node_ip){
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
			printf("RICORSIONE\n");
			routingtable_parse_table(table,ip,&app_node,peso);
			/*
		        if(routingtable_parse_table(table,ip,&app_node,peso)){	// Ricorsione sull'ip estratto
				(*node)->next_nodes = realloc((*node)->next_nodes,sizeof(t_node) * (ctr + 1));
				
				netlib_ntoa(app_node->ip,sApp);	// TODO: Togliere, anche riga sotto
				netlib_ntoa((*node)->ip,sApp1);
				printf("PADRE|%15s|FIGLIO|%15s|\n",sApp1,sApp);
				for(iapp = 0;app_node->next_nodes[iapp].ip != 0;iapp++){
					netlib_ntoa(app_node->next_nodes[iapp].ip,sApp1);
					printf("\tPADRE|%15s|FIGLIO|%15s|\n",sApp,sApp1);
				}
				
				(*node)->next_nodes[ctr] = *app_node;
				ctr++;
			}
			*/
		}
	}
	
	// L'ultimo elemento dell'array ha come ip 0, in modo da sapere quando termina la lista
	(*node)->next_nodes = realloc((*node)->next_nodes,sizeof(t_node) * (ctr + 1));
	(*node)->next_nodes[ctr++].ip = 0;
	if(ctr <= 1){
		printf("NON TROVATO\n");
	}
	// TODO: Togliere questo ciclo, solo per test
	/*	
	for(i = 0;i<ctr, (*node)->next_nodes[i].ip != 0;i++){
		netlib_ntoa((*node)->next_nodes[i].ip,sApp);
		netlib_ntoa((*node)->ip,sApp1);
		printf("PADRE|%15s|FIGLIO|%15s|PESO|%d|\n",sApp1,sApp,(*node)->next_nodes[i].peso_nodo);
	}
	*/
	return (!bRet); // Ritorno 1, tutto ok
}

/*=====  End of IMPLEMENTAZIONI FUNZIONI  ======*/
