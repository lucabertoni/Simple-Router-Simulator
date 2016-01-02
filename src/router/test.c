#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include "../lib/netlib.h"

int main (void){
    struct t_node node1, node2, node3_dir, node3b, node4;
    /* *
        node1       ->      192.168.0.1     0        
        node2       ->      192.168.0.2     3
        node3_dir   ->      192.168.0.3     6
        node3b      ->      192.168.0.3     2
        node4       ->      192.168.0.4     4
    */

    node3_dir.ip = netlib_aton("192.168.0.3");
    node3_dir.peso_nodo = 6;
    node3_dir.next_nodes = NULL;

    node3b.ip = netlib_aton("192.168.0.3");
    node3b.peso_nodo = 2;
    node3b.next_nodes = NULL;

    node2.ip = netlib_aton("192.168.0.2");
    node2.peso_nodo = 3;
    node2.next_nodes = malloc(sizeof(t_node));
    node2.next_nodes[0] = node3b;
    
    node4.ip = netlib_aton("192.168.0.4");
    node4.peso_nodo = 4;
    node4.next_nodes = malloc(sizeof(t_node));
    node4.next_nodes[0] = node3b;

    node1.ip = netlib_aton("192.168.0.1");
    node1.peso_nodo = 0;

    node1.next_nodes = malloc(sizeof(t_node) * 3);
    node1.next_nodes[0] = node2;
    node1.next_nodes[1] = node3_dir;
    node1.next_nodes[2] = node4;

    int* sequenza_nodi;
    int destination = netlib_aton("192.168.0.3");
    dijkstra_shortest_path(&node1, sequenza_nodi, destination);

    while(sequenza_nodi != 0){
        printf("NODO -> %d \n\t", *sequenza_nodi++);
    }
    return 1;
}