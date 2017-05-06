/*
 * tad_kernel.c
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#include "tad_kernel.h"
#include <ctype.h>

void consola_imprimirTodosLosProcesos() {

}

void consola_imprimirProcesoEnEstado() {

}

void consola_imprimirCantidadRagafas(){

}

void consola_imprimirCantidadOperPriv() {

}

void consola_imprimirTablaArchivosPorProceso() {

}

void consola_imprimirPaginasHeap() {

}

void consola_imprimirCantidadAlocar() {

}

void consola_imprimirCantidadFree() {

}

void consola_imprimirCantidadSysCalls(){

}

void consola_imprimirCantidadHeap() {

}

void consola_imprimirTablaGlobalArchivos() {

}

void consola_detenerPlanificacion() {

}

void consola_reconocerComando() {


	int opcion = toupper(getchar());

	while (opcion < PRINT_PROC || opcion > STOP_PLANIF) {
		puts("Error");
		opcion = toupper(getchar());
	}

	switch (opcion) {
	case PRINT_PROC:
		consola_imprimirTodosLosProcesos();
		break;
	case PRINT_PROC_X_STAT:
		consola_imprimirProcesoEnEstado();
		break;
	case CANT_RAF:
		consola_imprimirCantidadRagafas();
		break;
	case CANT_OP_PRIV:
		consola_imprimirCantidadOperPriv();
		system("clear");
		break;
	case PRINT_FILE_TABLE:
		consola_imprimirTablaArchivosPorProceso();
		break;
	case PRINT_HEAP_PAGES:
		consola_imprimirPaginasHeap();
		break;
	case PRINT_ALLOC_AMOUNT:
		consola_imprimirCantidadAlocar();
		break;
	case PRINT_FREE_AMOUNT:
		consola_imprimirCantidadFree();
		break;
	case PRINT_SYSCALLS_AMOUNT:
		consola_imprimirCantidadSysCalls();
		break;
	case PRINT_HEAP_AMOUNT:
		consola_imprimirCantidadHeap();
		break;
	case PRINT_GLOBAL_FILE_TABLE:
		consola_imprimirTablaGlobalArchivos();
		break;
	case STOP_PLANIF:
		consola_detenerPlanificacion();
		break;
	}

}
