//
// Created by Martin Gauna on 4/2/17.
//

#include "consola.h"
#include <stdio.h>

void consola_imprimir_encabezado(){
	printf("*********** BIENVENIDO A LA CONSOLA ***********\n");
	printf("\n");
}

void consola_imprimir_menu(){
	printf("Por favor seleccione la opcion correspondiente:\n");
	printf("\n");
	printf("1) Iniciar programa\n");
	printf("2) Finalizar programa\n");
	printf("3) Desconectar consola\n");
	printf("4) Limpiar mensajes\n");
}
