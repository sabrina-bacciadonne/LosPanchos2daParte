/*
 * tad_memoria.c
 *
 *  Created on: 22/4/2017
 *      Author: utnso
 */

#include "tad_memoria.h"
#include <ctype.h>
#include <stdio.h>

void consola_imprimirRetardo(){

}

void consola_imprimirDump(){

}

void consola_ejecutarFlush(){

}

void consola_imprimirTamanio(){

}


void consola_reconocerComando() {

	int opcion = toupper(getchar());

	while (opcion < RETARDO || opcion > SIZE) {
		puts("Error");
		opcion = toupper(getchar());
	}

	switch (opcion) {
	case RETARDO:
		consola_imprimirRetardo();
		break;
	case DUMP:
		consola_imprimirDump();
		break;
	case FLUSH:
		consola_ejecutarFlush();
		break;
	case SIZE:
		consola_imprimirTamanio();
		break;
	}

}
