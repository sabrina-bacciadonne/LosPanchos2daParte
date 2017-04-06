/*
 * archivo_configuracion.c
 *
 *  Created on: 3/4/2017
 *      Author: utnso
 */

#include "configuracion.h"

void* cargarConfiguracion(char* path,int configParamAmount,processType configType, t_log* logger){
	t_config* configFile;
	void* config;


	configFile = config_create(path);
	if (!configFile) {
		log_error(logger, "No se encontro el archivo de configuracion.\n");
		exit(NULL);
	}

	if (config_keys_amount(configFile) != configParamAmount) {
		log_error(logger, "No se encuentran inicializados todos los parametros de configuracion requeridos.");
		exit(NULL);
	}

	switch(configType){
	case CONSOLA:
		config = (configConsole*)malloc(sizeof(configConsole));
		config->puerto = leerPuerto(configFile, "PUERTO_KERNEL", logger);
		config->ip = leerIP(configFile, "IP_KERNEL", logger);
		break;
	case CPU:
		config = (configCPU*)malloc(sizeof(configCPU));
		config->puertoKernel = leerPuerto(configFile, "PUERTO_KERNEL", logger);
		config->ipKernel = leerIP(configFile, "IP_KERNEL", logger);
		config->puertoMemoria = leerPuerto(configFile, "PUERTO_MEMORIA", logger);
		config->ipMemoria = leerIP(configFile, "IP_MEMORIA", logger);
		break;
	case FILESYSTEM:
		config = (configFileSystem*)malloc(sizeof(configFileSystem));
		config->puerto = leerPuerto(configFile, "PUERTO", logger);
		break;
	case KERNEL:
		config = (configKernel*)malloc(sizeof(configKernel));
		break;
	case MEMORIA:
		config = (configMemoria*)malloc(sizeof(configMemoria));
		break;
	}

	return config;
}

int leerPuerto (void* configFile, char* parametro, t_log* logger){
	int puerto = 0;
	if (config_has_property(configFile, parametro)) {
		puerto = config_get_int_value(configFile, parametro);
		validar_puerto(puerto, logger);
	} else {
		log_error(logger, "No se encuentra el parametro puerto programa en el archivo.");
		exit(EXIT_FAILURE);
	}
	return puerto;
}

char* leerIP (void* configFile, char* parametro, t_log* logger){
	char* ip = NULL;
	if (config_has_property(configFile, "IP_KERNEL")) {
		ip = config_get_string_value(configFile, "IP_KERNEL");
		validar_ip(ip, logger);
	} else {
		log_error(logger, "No se encuentra el parametro IP programa en el archivo.");
		exit(EXIT_FAILURE);
	}
	return ip;
}

char* leerString (void* configFile, char* parametro, t_log* logger){
	char* string = NULL;
	if (config_has_property(configFile, "IP_KERNEL")) {
		string = config_get_string_value(configFile, "IP_KERNEL");
		//TODO: Valida que no sea vacio
	} else {
		log_error(logger, "No se encuentra el parametro IP programa en el archivo.");
		exit(EXIT_FAILURE);
	}
	return string;
}

void validar_puerto(int puerto, t_log* logger){
	if (puerto < PUERTO_MAX) {
		log_error(logger, "El numero de puerto indicado se encuentra reservado para el sistema.");
		exit(EXIT_FAILURE);
	}
	return;
}

void validar_ip(char* ip, t_log* logger) {
	char* messType;
	regex_t regex;
	int regres;
	char msgbuf[100];

	regres = regcomp(&regex, "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$",
					REG_EXTENDED);		//REVISAR LA EXPRESION REGULAR
	if (regres) {
		log_error(logger,"Error al generar la regex para validar IP.");
		exit(1);
	}

	regres = regexec(&regex, ip, 0, NULL, 0);

	if (regres == REG_NOMATCH) {
		log_error(logger,"IP invalida.");
		exit(EXIT_FAILURE);
	} else {
//		log_info(logger, "IP del Kernel valida.");
	    regerror(regres, &regex, msgbuf, sizeof(msgbuf));
//	    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	}
}

void* validar_archivo_config(t_log* logger) {

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





