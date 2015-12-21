#ifndef DIJKTRA_H
#define DIJKTRA_H

struct net_node
{
	int ip;							// Ip del nodo di rete corrente
	int peso_nodo;					// Peso del nodo
	struct net_node* next_nodes;	// Array di nodi successivi
};

#endif