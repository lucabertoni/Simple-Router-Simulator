/*==================================
=            INCLUSIONI            =
==================================*/
#include <stdlib.h>
#include <stdio.h>

/*----------  Librerie definite dal programmatore  ----------*/
#include "dijkstra.h"

/*=====  End of INCLUSIONI  ======*/

/*================================================
=            IMPLEMENTAZIONI FUNZIONI            =
================================================*/


/**
 *
 * Cosa fa            :            Estrapola il nodo con peso inferiore dalla lista di nodi passati come parametri
 * nodes              :            struct t_node*, array di nodi
 * less_weight        :            struct t_node, nodo che ha il peso minore
 *
 */
void get_less_weight(t_node* nodes, t_node less_weight)
{
    int tmp = nodes->peso_nodo;
    less_weight = *nodes;
    while(nodes != NULL){
        if (tmp > nodes->peso_nodo){
            less_weight = *nodes;
        }
        printf("NODO|%u|\n",nodes);
        nodes++;
    }
}

/**
 *
 * Cosa fa          :           Calcola il percorso minimo da nodo di Partenza a nodo di Fine
 * graph            :           t_node, Nodo di partenza
 * sequenza_nodo    :           array di interi, contiene la sequenza dei nodi del percorso più corto [...]
 * destination      :           int, indirizzo di destinazione, nodo Fine
 * return           :           weight -> int; ritorna il peso totale del percorso fatto
 *
 *
 */
int dijkstra_shortest_path(t_node* graph, int *sequenza_nodi, int destination)
{
    int weight = 0; 
    t_node node_less_weight;
    if (graph->ip == destination){
        return weight;
    }
    else{
        while (graph->next_nodes != 0){
            printf("lol\n");
            get_less_weight(graph->next_nodes, node_less_weight);
            printf("lol2\n");
            sequenza_nodi = realloc(sequenza_nodi, sizeof(sequenza_nodi) + sizeof(int));
            *sequenza_nodi = graph->ip; // Mi sa che è sbagliato, credo ci vada "node_less_weight->ip", verifica, Luca
            sequenza_nodi++;
            weight += node_less_weight->peso_nodo;

            dijkstra_shortest_path(node_less_weight, sequenza_nodi, destination);
        }
    }

    return weight;
}