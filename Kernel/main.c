/*
 * main.c
 *
 *  Created on: 3/4/2017
 *      Author: utnso
 */


#include "archivo_configuracion.h"

int main () {

	t_datos_config* datos_config = malloc(sizeof(t_datos_config));
	t_log* logger = log_create("log_kernel", "KERNEL", 1, LOG_LEVEL_TRACE);

	datos_config = validar_archivo_config(&datos_config,&logger);


	//en datos_config están los datos para conectarse al kernel!!!!

//	consola_imprimir_menu();


	liberar_memoria(logger,datos_config);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,t_datos_config* config) {
	free(logger);
	free(config);
}
