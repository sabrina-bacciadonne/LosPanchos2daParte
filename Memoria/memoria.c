//
// Created by Martin Gauna on 4/2/17.
//

#include "memoria.h"

#include <stdio.h>

void consolaMem_imprimir_encabezado(){
	printf("**** BIENVENIDO A LA CONSOLA MEMORIA****\n");
	printf("\n");
}

void consolaMem_imprimir_menu(){
	printf("Por favor seleccione la opcion correspondiente:\n");
	printf("\n");
	printf("1) Retardo\n");
	printf("2) Dump\n");
	printf("3) Flush\n");
	printf("4) Size\n");
}

int validar_archivo_configMemoria(configMemoria* datos_config,t_log* logger) {

	t_config* config;

	config = config_create(
			"/home/utnso/git/tp-2017-1c--LosPanchos/Memoria/config");

	if (!config) {
		log_error(logger, "No se encontro el archivo de configuracion.\n");
		exit(EXIT_FAILURE);
	}

	if (config_keys_amount(config) != 7) {
		log_error(logger,
				"No se encuentran inicializados todos los parametros de configuracion requeridos.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "PUERTO")) {
		datos_config->puerto = config_get_int_value(config, "PUERTO");
	} else {
		log_error(logger,
				"No se encuentra el parametro puerto en el archivo.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "MARCOS")) {
		datos_config->marcos = config_get_int_value(config,
				"MARCOS");
		if (datos_config->marcos > 500) {
				log_error(logger,"No se puede ampliar la memoria");
				exit(EXIT_FAILURE);
					  }
	} else {
		log_error(logger,
				"No se encuentra el número de marcos disponibles en el sistema");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "MARCO_SIZE")) {
			datos_config->marcoSize = config_get_int_value(config,
					"MARCO_SIZE");

		    if (datos_config->marcoSize > 256) {
		    	log_error(logger,"No se puede ampliar la memoria");
		    	exit(EXIT_FAILURE);
			  }

		} else {
			log_error(logger,
					"No se encuentra el valor del tamaño de marco del sistema");
			exit(EXIT_FAILURE);
		}
	if (config_has_property(config,"ENTRADAS_CACHE")) {
				datos_config->entradasCache = config_get_int_value(config,
						"ENTRADAS_CACHE");
	    if (datos_config->entradasCache == 0) {
				log_error(logger,
						"La cache se encuentra deshabilitada");
		  }
	} else {
			 log_error(logger,
					   "No se encuentra la cantidad disponible de entradas en la cache");
			 exit(EXIT_FAILURE);
		}

	if (config_has_property(config, "CACHE_X_PROC")) {
						datos_config->cacheXProc = config_get_int_value(config,
								"CACHE_X_PROC");
		} else {
			 log_error(logger,
								"No se encuentra la cantidad máxima de entradas de la cache asignables a cada programa");
				exit(EXIT_FAILURE);
				}

	if (config_has_property(config, "RETARDO_MEMORIA")) {
							datos_config->retardoMemoria = config_get_int_value(config,
									"RETARDO_MEMORIA");
			} else {
				 log_error(logger,
									"No se encuentra la cantidad de milisegundos que el sistema debe esperar");
					exit(EXIT_FAILURE);
					}
	return 0;

}

void inicializarMemoria(){

	char** memoria;

	configMemoria datos_config;
	t_log* logger = log_create("LOG_MEMORIA", "MEMORIA", 1, LOG_LEVEL_DEBUG);

	validar_archivo_configMemoria(&datos_config,logger);
	consolaMem_imprimir_encabezado();
	consolaMem_imprimir_menu();

	printf("\n");
	printf("Puerto = %d\n",datos_config.puerto);
	printf("Marco_Size = %d\n",datos_config.marcoSize);
	printf("Marcos = %d\n",datos_config.marcos);
	printf("Entradas_Cache = %d\n",datos_config.entradasCache);
	printf("Cache_X_Proc = %d\n",datos_config.cacheXProc);
	printf("Retardo_Memoria = %d\n",datos_config.retardoMemoria);


	int cant_marcos = datos_config.marcos;
	memoria = malloc(sizeof(char*)*cant_marcos); //Reservo memoria con cantidad de frames disponibles

}


int main(int argc, char **argv) {

	puts("Memoria\n");


        inicializarMemoria();


		return 0;

  }

