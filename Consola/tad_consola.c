/*
 * tad_consola.c
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#include "tad_consola.h"
#include <ctype.h>

void consola_terminarPrograma() {
	puts ("Terminar programa");
}

void* consola_ejecutarPrograma() {
	return NULL;
}

void consola_crearHiloDePrograma() {

	pthread_t hilo;
	char* ruta;
	puts ("Por favor, ingrese la ruta del script Ansisop");		//VA LA LOGICA DE CONEXION AL KERNEL

}


void consola_desconectarConsola() {

}

void consola_reconocerComando() {


	pthread_t* hilo;
	int opcion = toupper(getchar());

	while (opcion < INIT_PROGRAM || opcion > CLEAN) {
		puts("Error");
		opcion = toupper(getchar());
	}

	switch (opcion) {
	case INIT_PROGRAM:
		consola_crearHiloDePrograma();
		break;
	case FIN_PROGRAM:
		consola_terminarPrograma();
		break;
	case DISCONNECT:
		consola_desconectarConsola();
		break;
	case CLEAN:
		system("clear");
		break;
	}

}

