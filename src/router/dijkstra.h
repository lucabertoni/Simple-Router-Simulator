#ifndef DIJKSTRA_H
#define DIJKSTRA_H

/*==================================
=            INCLUSIONI            =
==================================*/
/*----------  Librerie di sistema  ----------*/

/*----------  Librerie definite dal programmatore  ----------*/
#include "router.h"

/*=====  End of INCLUSIONI  ======*/


/*=================================
=            PROTOTIPI            =
=================================*/

/*----------  Definizione tipi/struct  ----------*/

/*----------  Funzioni  ----------*/
void get_less_weight(struct t_node* nodes, struct t_node* less_weight);
int dijkstra_shortest_path(struct t_node*, int*, int);

/*=====  End of PROTOTIPI  ======*/
#endif