/*
 * tad_memoria.c
 *
 *  Created on: 22/4/2017
 *      Author: utnso
 */

#include "tad_memoria.h"
#include "memoria.h"
#include <ctype.h>
#include <stdio.h>

int nuevo_retardo;

void modificar_retardo(){
	int leer;

	   printf("Ingrese la cantidad de milisegundos de retardo\n");

	   scanf("%d", &leer);
	   printf("Nuevo valor de retardo: %d\n",leer);

	   nuevo_retardo = leer;

	   printf("retardo: %d\n",nuevo_retardo);

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
		modificar_retardo();
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
