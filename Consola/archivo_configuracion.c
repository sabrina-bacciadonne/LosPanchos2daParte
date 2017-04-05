/*
 * archivo_configuracion.c
 *
 *  Created on: 3/4/2017
 *      Author: utnso
 */

#include <stdio.h>
#include <commons/config.h>
#include <regex.h>
#include <stdlib.h>
#include "archivo_configuracion.h"

t_datos_config* validar_archivo_config(t_datos_config* datos_config,t_log* logger) {

	t_config* config;

	config = config_create(
			"/home/utnso/workspace/tp-2017-1c--LosPanchos/Consola/config");

	if (!config) {
		log_error(logger, "No se encontro el archivo de configuracion.\n");
		exit(EXIT_FAILURE);
	}

	int cantidad_claves = config_keys_amount(config);

	if (cantidad_claves != 2) {
		log_error(logger,
				"No se encuentran inicializados todos los parametros de configuracion requeridos.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "IP_KERNEL")) {
		datos_config->ip_kernel = config_get_string_value(config, "IP_KERNEL");	//FALTA VALIDACION DE IP, INVESTIGAR REGEX
		validar_ip(datos_config->ip_kernel,logger);
	} else {
		log_error(logger,
				"No se encuentra el parametro ip kernel en el archivo.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "PUERTO_KERNEL")) {
		datos_config->puerto_kernel = config_get_int_value(config,
				"PUERTO_KERNEL");
		if (datos_config->puerto_kernel < 1024) {//FALTA VALIDACION DE PUERTO VACIO
			log_error(logger,
					"El numero de puerto indicado se encuentra reservado para el sistema.");
			exit(EXIT_FAILURE);
		}
	} else {
		log_error(logger,
				"No se encuentra el parametro puerto kernel en el archivo.");
		exit(EXIT_FAILURE);
	}

	return datos_config;

}

void validar_ip(char* ip, t_log* logger) {

	char* messType;

	regex_t regex;
	int regres;
	char msgbuf[100];


	regres =
			regcomp(&regex,
					"^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$",
					REG_EXTENDED);		//REVISAR LA EXPRESION REGULAR

	if (regres) {
		fprintf(stderr, "Could not compile regex\n");
		exit(1);
	}

	regres = regexec(&regex, ip, 0, NULL, 0);

	if (regres == REG_NOMATCH) {
		log_error(logger,"IP invalida.");
//		exit(EXIT_FAILURE);
	} else {
//		log_info(logger, "IP del Kernel valida.");
	    regerror(regres, &regex, msgbuf, sizeof(msgbuf));
	    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	}
}

