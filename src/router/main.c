/*
*	
*/

/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdio.h>

/*----------  Librerie definite dall'utente  ----------*/
#include "router.h"

/*=====  End of INCLUSIONI  ======*/


int main(int argc, char *argv[]){
	t_router router;

	/**
	 *
	 * Cosa fa			:			Imposta il router per l'avvio
	 * router			:			t_router, Riferimento alla struct che contiene le impostazioni del router
	 * argv				:			array di stringhe, così formato:
	 *									[0] => "nome programma"
	 *									[1] => "192.168.0.1" (ip router)
	 *
	 */	
	router_setup(&router,argv);

	/**
	
		TODO:
		- Da defire la funzione che gestisce tutto il funzionamento del router: router_start
	
	 */
	// router_start();
	return 0;
}