//
// Created by Martin Gauna on 4/2/17.
//

#include "consola.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
	t_log* logger = log_create("log_consola", "CONSOLA", 1, LOG_LEVEL_TRACE);
	processType process = CONSOLA;

	configConsole* conf = (configConsole*) cargarConfiguracion(argv[1], 2, process, logger);

	puts("Consola.");
	printf("IP_KERNEL: %s\n",conf->ip);
	printf("PUERTO KERNEL: %d\n",conf->puerto);

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configConsole* config) {
	free(logger);
	free(config);
}


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

