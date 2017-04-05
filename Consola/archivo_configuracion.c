/*
 * archivo_configuracion.c
 *
 *  Created on: 3/4/2017
 *      Author: utnso
 */

#include <stdio.h>
#include <commons/config.h>
#include <commons/log.h>
#include <regex.h>
#include <stdlib.h>

int validar_archivo_config() {

	t_config* config;
	t_log* logger = log_create("LOG_CONSOLA", "CONSOLA", 1, LOG_LEVEL_TRACE);
//	regex_t regex;
//	int reti;
	int puerto_kernel;
	char* ip_kernel;

	config = config_create("/home/utnso/workspace/tp-2017-1c--LosPanchos/Consola/config");

	if (!config) {
		log_error(logger,"No se encontro el archivo de configuracion.\n");
		exit(EXIT_FAILURE);
	}

	int cantidad_claves = config_keys_amount(config);

	if (cantidad_claves != 2) {
		log_error(logger,"No se encuentran inicializados todos los parametros de configuracion requeridos.");
		exit(EXIT_FAILURE);
	}


	if(config_has_property(config,"IP_KERNEL")){
		ip_kernel = config_get_int_value(config,"IP_KERNEL");	//FALTA VALIDACION DE IP, INVESTIGAR REGEX
	} else {
		log_error(logger, "No se encuentra el parametro ip kernel en el archivo.");
		exit(EXIT_FAILURE);
	}


	if(config_has_property(config,"PUERTO_KERNEL")){
		puerto_kernel = config_get_int_value(config,"PUERTO_KERNEL");
		if (puerto_kernel < 1024) {								//FALTA VALIDACION DE PUERTO VACIO
			log_error(logger, "El numero de puerto indicado se encuentra reservado para el sistema.");
			exit(EXIT_FAILURE);
		}
	} else {
		log_error(logger, "No se encuentra el parametro puerto kernel en el archivo.");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;

}
