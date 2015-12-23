/*==================================
=            INCLUSIONI            =
==================================*/
#include <stdlib.h>

/*----------  Librerie definite dal programmatore  ----------*/
#include "dijkstra.h"

/*=====  End of INCLUSIONI  ======*/

/*================================================
=            IMPLEMENTAZIONI FUNZIONI            =
================================================*/


/**
 *
 * Cosa fa            :            Estrapola il nodo con peso inferiore dalla lista di nodi passati come parametri
 * nodes              :            struct net_node*, array di nodi
 * less_weight        :            struct net_node, nodo che ha il peso minore
 *
 */
void get_less_weight(struct net_node* nodes, struct net_node* less_weight){

}

/**
 *
 * Cosa fa          :           Calcola il percorso minimo da nodo di Partenza a nodo di Fine
 * graph            :           net_node, Nodo di partenza
 * sequenza_nodo    :           array di interi, contiene la sequenza dei nodi del percorso più corto [...]
 * destination      :           int, indirizzo di destinazione, nodo Fine
 * return           :           weight -> int; ritorna il peso totale del percorso fatto
 *
 *
 */
int dijkstra_shortest_path(struct net_node* graph, int *sequenza_nodi, int destination)
{
    int weight = 0; 
    struct net_node *node_less_weight;
    if (graph->ip == destination){
        return weight;
    }
    else{
        while (graph->next_nodes != 0){
            get_less_weight(graph->next_nodes, node_less_weight);
            sequenza_nodi = (int*)realloc(sequenza_nodi, sizeof(sequenza_nodi) + sizeof(int));
            *sequenza_nodi = graph->ip;
            sequenza_nodi++;
            weight += node_less_weight->peso_nodo;

            dijkstra_shortest_path(node_less_weight, sequenza_nodi, destination);
        }
    }

    return weight;
}