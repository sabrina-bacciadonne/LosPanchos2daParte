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
			printf("1) Iniciar programa\n");
			printf("2) Finalizar programa\n");
			printf("3) Desconectar consola\n");
			printf("4) Limpiar mensajes\n");
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
			printf("1) Iniciar programa	\n");
			printf("2) Finalizar programa\n");
			printf("3) Desconectar	consola\n");
			printf("4) Limpiar mensajes	\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		case KERNEL:
			printf("******* MENU PRINCIPAL - KERNEL *******\n");
			printf("\n");
			printf("\n");
			printf("1) Imprimir procesos del sistema\n");
			printf("2) Imprimir procesos del sistema en un determinado estado\n");
			printf("3) Cantidad de rafagas para un proceso\n");
			printf("4) Cantidad de operaciones privilegiadas para un proceso\n");
			printf("5) Imprimir tabla de archivos abiertos para un proceso\n");
			printf("6) Cantidad de paginas de Heap utilizadas para un proceso\n");
			printf("7) Cantidad de acciones alocar para un proceso\n");
			printf("8) Cantidad de acciones liberar para un proceso\n");
			printf("9) Cantidad de syscall ejecutadas para un proceso\n");
			printf("10) Cantidad de paginas de Heap utilizadas para un proceso\n");
			printf("11) Imprimir tabla global de archivos\n");
			printf("12) Modificar grado de multiprogramacion del sistema\n");
			printf("13) Finalizar un proceso\n");
			printf("14) Detener la planificacion del sistema\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		case MEMORIA:
			printf("******* MENU PRINCIPAL - MEMORIA *******\n");
			printf("\n");
			printf("\n");
			printf("1) Modificar retardo \n");
			printf("2) Dump\n");
			printf("3) Flush\n");
			printf("4) Size\n");
			printf("\n");
			printf("Por favor seleccione la opcion correspondiente: ");
			break;
		default:
			return 1;

		}

	return 1;
}

void reconocerComando(processType proceso) {
	char opcion = getchar();

}


