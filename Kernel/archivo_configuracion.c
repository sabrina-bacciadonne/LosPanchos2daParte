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
#include <string.h>
#include "archivo_configuracion.h"

t_datos_config* validar_archivo_config(t_datos_config* datos_config,t_log* logger) {

	t_config* config;

	config = config_create(
			"/home/utnso/workspace/tp-2017-1c--LosPanchos/Kernel/config");

	if (!config) {
		log_error(logger, "No se encontro el archivo de configuracion.\n");
		exit(EXIT_FAILURE);
	}

	if (config_keys_amount(config) != 14) {
		log_error(logger,
				"No se encuentran inicializados todos los parametros de configuracion requeridos.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "PUERTO_PROG")) {
		datos_config->puerto_prog = config_get_int_value(config, "PUERTO_PROG");	//FALTA VALIDACION DE IP, INVESTIGAR REGEX
		if (datos_config->puerto_prog < 1024) {	//FALTA VALIDACION DE PUERTO VACIO
			log_error(logger,
					"El numero de puerto indicado se encuentra reservado para el sistema.");
			exit(EXIT_FAILURE); }
	} else {
		log_error(logger,
				"No se encuentra el parametro puerto programa en el archivo.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "PUERTO_CPU")) {
		datos_config->puerto_cpu = config_get_int_value(config,"PUERTO_CPU");
		if (datos_config->puerto_cpu < 1024) {	//FALTA VALIDACION DE PUERTO VACIO
			log_error(logger,
					"El numero de puerto indicado se encuentra reservado para el sistema.");
			exit(EXIT_FAILURE);
		}
	}

	if (config_has_property(config, "IP_MEMORIA")) {
			datos_config->ip_memoria = config_get_string_value(config, "IP_MEMORIA");	//FALTA VALIDACION DE IP, INVESTIGAR REGEX
			validar_ip(datos_config->ip_memoria,logger);
		}


	if (config_has_property(config, "IP_FS")) {
			datos_config->ip_fs = config_get_string_value(config, "IP_FS");	//FALTA VALIDACION DE IP, INVESTIGAR REGEX
			validar_ip(datos_config->ip_fs,logger);
		}

	if (config_has_property(config, "PUERTO_FS")) {
		datos_config->puerto_fs = config_get_int_value(config,"PUERTO_FS");
		if (datos_config->puerto_fs < 1024) {//FALTA VALIDACION DE PUERTO VACIO
			log_error(logger,
					"El numero de puerto indicado se encuentra reservado para el sistema.");
			exit(EXIT_FAILURE);
		}
	}

	if (config_has_property(config, "QUANTUM")) {
			datos_config->quantum = config_get_int_value(config, "QUANTUM");
			if (datos_config->quantum < 0){
				log_error(logger,"El quantum debe ser mayor que 0.");
				exit(EXIT_FAILURE);
			}
		}

	if (config_has_property(config, "QUANTUM_SLEEP")) {
			datos_config->quantum_sleep = config_get_int_value(config, "QUANTUM_SLEEP");
			if (datos_config->quantum_sleep < 0){
				log_error(logger,"El quantum sleep debe ser mayor que 0.");
				exit(EXIT_FAILURE);
			}
		}

	if (config_has_property(config, "ALGORITMO")) {
			datos_config->algoritmo= config_get_string_value(config, "ALGORITMO");

			int comp = 0;
			int compa = 0;

			comp = strcmp(datos_config->algoritmo,"FF");
			compa = strcmp(datos_config->algoritmo,"RR");

			if (comp != 0 && compa != 0) {
				log_error(logger,"El algoritmo indicado es invalido.");
				exit(EXIT_FAILURE);
			}
		}

	if (config_has_property(config, "GRADO_MULTIPROG")) {
			datos_config->grado_multiprog = config_get_int_value(config, "GRADO_MULTIPROG");
			if (datos_config->grado_multiprog < 0){
				log_error(logger,"El grado de multiprogramacion debe ser mayor que 0.");
				exit(EXIT_FAILURE);
			}
		}

	if (config_has_property(config, "STACK_SIZE")) {
			datos_config->stack_size = config_get_int_value(config, "STACK_SIZE");
			if (datos_config->stack_size < 0){
				log_error(logger,"El grado de multiprogramacion debe ser mayor que 0.");
				exit(EXIT_FAILURE);
			}
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
//	    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	}
}



