/*
 * main.c
 *
 *  Created on: 3/4/2017
 *      Author: utnso
 */


#include "archivo_configuracion.h"

int main () {

	t_datos_config* datos_config = malloc(sizeof(t_datos_config));
	t_log* logger = log_create("LOG_CONSOLA", "CONSOLA", 1, LOG_LEVEL_TRACE);

	datos_config = validar_archivo_config(&datos_config,&logger);
	consola_imprimir_encabezado();
	consola_imprimir_menu();

	printf("%s\n",datos_config->ip_kernel);
	printf("%d",datos_config->puerto_kernel);

	//en datos_config están los datos para conectarse al kernel!!!!

	return 0;
}
