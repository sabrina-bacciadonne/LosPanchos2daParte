/*
 * console.c
 *
 *  Created on: 8/4/2017
 *      Author: utnso
 */

#include "console.h"

int imprimirConsola(processType proceso){

	switch (proceso) {
		case CONSOLA:
			printf("******* MENU PRINCIPAL - CONSOLA *******\n");
			printf("\n");
			printf("\n");
			printf("A) Iniciar programa\n");
			printf("B) Finalizar programa\n");
			printf("C) Desconectar consola\n");
			printf("D) Limpiar mensajes\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		case CPU:
			printf("******* MENU PRINCIPAL - CPU *******\n");
			printf("\n");
			printf("\n");
			printf("1) Iniciar programa	\n");
			printf("2) Finalizar programa	\n");
			printf("3) Desconectar consola\n");
			printf("4) Limpiar mensajes	\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		case FILESYSTEM:
			printf("******* MENU PRINCIPAL - FILESYSTEM *******\n");
			printf("\n");
			printf("\n");
			printf("A) Iniciar programa	\n");
			printf("B) Finalizar programa\n");
			printf("C) Desconectar	consola\n");
			printf("D) Limpiar mensajes	\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		case KERNEL:
			printf("******* MENU PRINCIPAL - KERNEL *******\n");
			printf("\n");
			printf("\n");
			printf("A) Imprimir procesos del sistema\n");
			printf("B) Imprimir procesos del sistema en un determinado estado\n");
			printf("C) Cantidad de rafagas para un proceso\n");
			printf("D) Cantidad de operaciones privilegiadas para un proceso\n");
			printf("E) Imprimir tabla de archivos abiertos para un proceso\n");
			printf("F) Cantidad de paginas de Heap utilizadas para un proceso\n");
			printf("G) Cantidad de acciones alocar para un proceso\n");
			printf("H) Cantidad de acciones liberar para un proceso\n");
			printf("J) Cantidad de syscall ejecutadas para un proceso\n");
			printf("K) Cantidad de paginas de Heap utilizadas para un proceso\n");
			printf("L) Imprimir tabla global de archivos\n");
			printf("M) Modificar grado de multiprogramacion del sistema\n");
			printf("N) Finalizar un proceso\n");
			printf("O) Detener la planificacion del sistema\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		case MEMORIA:
			printf("******* MENU PRINCIPAL - MEMORIA *******\n");
			printf("\n");
			printf("\n");
			printf("A) Modificar retardo \n");
			printf("B) Dump\n");
			printf("C) Flush\n");
			printf("D) Size\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		default:
			return 1;

		}

	return 1;
}


