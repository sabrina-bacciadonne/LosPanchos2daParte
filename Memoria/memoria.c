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

int validar_archivo_config(configMemoria* datos_config,t_log* logger) {

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
		datos_config->puerto = config_get_string_value(config, "PUERTO");
		validar_ip(datos_config->puerto,logger);
	} else {
		log_error(logger,
				"No se encuentra el parametro puerto en el archivo.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "MARCOS")) {
		datos_config->marcos = config_get_int_value(config,
				"MARCOS");
	} else {
		log_error(logger,
				"No se encuentra el número de marcos disponibles en el sistema");
		exit(EXIT_FAILURE);
	}

//	if (config_has_property(config, "MARCO_SIZE")) {
//			datos_config->marcoSize = config_get_int_value(config,
//					"MARCO_SIZE");
//		} else {
//			log_error(logger,
//					"");
//			exit(EXIT_FAILURE);
//		}
//	return 0;

//}

	//TERMINAR DE VALIDAR ARCH CONFIG

int main(int argc, char **argv) {

	puts("Memoria\n");
		int res;
		configMemoria datos_config;
		t_log* logger = log_create("LOG_MEMORIA", "MEMORIA", 1, LOG_LEVEL_DEBUG);

		res = validar_archivo_config(&datos_config,logger);
		consolaMem_imprimir_encabezado();
		consolaMem_imprimir_menu();

		printf("%d",datos_config.puerto);
		printf("%d",datos_config.marcos);
		printf("%d",datos_config.marcoSize);
		printf("%d",datos_config.marcos);
		printf("%d",datos_config.entradasCache);
		printf("%d",datos_config.cacheXProc);
		printf("%d",datos_config.retardoMemoria);

		//en datos_config están los datos para conectarse al kernel!!!!

		return 0;

}

