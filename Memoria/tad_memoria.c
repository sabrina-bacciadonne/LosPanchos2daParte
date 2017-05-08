/*
 * tad_memoria.c
 *
 *  Created on: 22/4/2017
 *      Author: utnso
 */

#include "tad_memoria.h"
#include <ctype.h>
#include <stdio.h>

void modificar_retardo(){

	FILE *fp;
	   printf("Ingrese la cantidad de milisegundos de retardo\n");
	  int leer;
	   scanf("%d", &leer);
	   printf("Nuevo valor de retardo: %d\n",leer);
	   fp = fopen ( "config", "r+" );
	  if (fp==NULL) {
	   fputs ("File error",stderr);
	   exit (1);
	  }else {

	printf ("Acá estamos");

	}

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
