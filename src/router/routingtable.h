#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H
/*=================================
=            PROTOTIPI            =
=================================*/

/*----------  Struct  ----------*/

// Struct che definisce una singola riga della routing table
struct routing_table_row
{
	int ip;			// Ip corrente
	int next_hop;	// Passo successivo
	int peso;		// Peso per raggiungere il nodo successivo
};

// Struct che definisce l'intera tabella di routing basandosi sulle singole righe della routing table
struct routing_table
{
	struct routing_table_row* table_rows;
};

/*----------  Funzioni  ----------*/
/*=====  End of PROTOTIPI  ======*/
#endif