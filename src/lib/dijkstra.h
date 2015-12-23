#ifndef DIJKTRA_H
#define DIJKTRA_H

struct net_node
{
	int ip;							// Ip del nodo di rete corrente
	int peso_nodo;					// Peso del nodo
	struct net_node* next_nodes;	// Array di nodi successivi
};

void get_less_weight(struct net_node* nodes, struct net_node* less_weight);
int dijkstra_shortest_path(struct net_node*, int*, int);

#endif