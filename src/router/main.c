/*
*	
*/

/*==================================
=            INCLUSIONI            =
==================================*/

/*----------  Librerie di sistema  ----------*/
#include <stdio.h>
#include <stdlib.h>

/*----------  Librerie definite dall'utente  ----------*/
#include "router.h"
#include "../lib/common.h"

/*=====  End of INCLUSIONI  ======*/

int main(int argc, char *argv[]){
	t_router *router;
	int bError;

	// Se il numero di parametri è sbagliato, termino l'esecuzione
	if(argc < 2){
		return 1;
	}

	/**
	 *
	 * Cosa fa			:			Alloca la memoria necessaria per una struct di tipo t_router
	 * Ritorna			:			router -> struct t_router, Struct contenente la definizione del router
	 *
	 */
	router = initialize_router_memory();

	print(0,"/=====================================/\n");
	print(0,"Impostazione del router...\n");
	/**
	 *
	 * Cosa fa			:			Imposta il router per l'avvio
	 * router			:			t_router, Riferimento alla struct che contiene le impostazioni del router
	 * argv				:			array di stringhe, così formato:
	 *									[0] => "nome programma"
	 *									[1] => "192.168.0.1" (ip router)
	 *
	 */	
	router_setup(router,argv);

	if(router->ip <= 0){
		print(1,"Errore inizializzazione router\n");

		/**
		 *
		 * Cosa fa			:			Libera la memoria occupata dalla struct del router
		 * router			:			t_router*, puntatore all'area di memoria della struct che identifica il router
		 *
		 */
		release_router_memory(router);
		return 1;
	}

	print(0,"Router impostato. Indirizzo ip: ");
	print(0,argv[1]);


	/**
	
		TODO:
		- Da defire la funzione che gestisce tutto il funzionamento del router: router_start
	
	 */
	print(0,"\nAvvio il router...\n");

	/**
	 *
	 * Cosa fa			:			Avvia il router
	 * router			:			t_router, Struct contente le informazioni del router necessarie per il suo avvio
	 * Ritorna			:			bRet -> intero, 0 = Ok | 1 = Errore
	 *
	 */
	bError = router_start(router);

	// Terminata l'esecuzione del router, libero la memoria
	/**
	 *
	 * Cosa fa			:			Libera la memoria occupata dalla struct del router
	 * router			:			t_router*, puntatore all'area di memoria della struct che identifica il router
	 *
	 */
	release_router_memory(router);

	if(bError){
		print(1, "Attenzione: Esecuzione del router terminata con un errore!\n");
	}else{
		print(0,"Esecuzione del router terminata correttamente.\n");	
	}

	print(0,"/=====================================/\n");

	return bError;
}