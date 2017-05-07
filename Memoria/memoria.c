//
// Created by Martin Gauna on 4/2/17.
//

#include "memoria.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <commons/collections/dictionary.h>
#include "tad_memoria.h"

void consolaMem_imprimir_encabezado() {
	printf("**** BIENVENIDO A LA CONSOLA MEMORIA****\n");
	printf("\n");
}

void consolaMem_imprimir_menu() {
	printf("Por favor seleccione la opcion correspondiente:\n");
	printf("\n");
	printf("1) Retardo\n");
	printf("2) Dump\n");
	printf("3) Flush\n");
	printf("4) Size\n");
	printf("\n");
}

int validar_archivo_configMemoria(configMemoria* datos_config, t_log* logger) {

	t_config* config;

	printf("PUERTO: %d\n", datos_config->puerto);
	printf("MARCOS: %d\n", datos_config->marcos);
	printf("MARCOS SIZE: %d\n", datos_config->marcoSize);
	printf("ENTRADAS CACHE: %d\n", datos_config->entradasCache);
	printf("CACHE X PROC: %d\n", datos_config->cacheXProc);
	printf("RETARDO MEMORIA: %d\n", datos_config->retardoMemoria);
	puts("\n");

	imprimirConsola(MEMORIA);
	consola_reconocerComando();

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
		log_error(logger, "No se encuentra el parametro puerto en el archivo.");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "MARCOS")) {
		datos_config->marcos = config_get_int_value(config, "MARCOS");
		if (datos_config->marcos > 500) {
			log_error(logger, "No se puede ampliar la memoria");
			exit(EXIT_FAILURE);
		}
	} else {
		log_error(logger,
				"No se encuentra el número de marcos disponibles en el sistema");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "MARCO_SIZE")) {
		datos_config->marcoSize = config_get_int_value(config, "MARCO_SIZE");

		if (datos_config->marcoSize > 256) {
			log_error(logger, "No se puede ampliar la memoria");
			exit(EXIT_FAILURE);
		}

	} else {
		log_error(logger,
				"No se encuentra el valor del tamaño de marco del sistema");
		exit(EXIT_FAILURE);
	}
	if (config_has_property(config, "ENTRADAS_CACHE")) {
		datos_config->entradasCache = config_get_int_value(config,
				"ENTRADAS_CACHE");
		if (datos_config->entradasCache == 0) {
			log_error(logger, "La cache se encuentra deshabilitada");
		}
	} else {
		log_error(logger,
				"No se encuentra la cantidad disponible de entradas en la cache");
		exit(EXIT_FAILURE);
	}

	if (config_has_property(config, "CACHE_X_PROC")) {
		datos_config->cacheXProc = config_get_int_value(config, "CACHE_X_PROC");
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

void liberar_memoria(t_log* logger, configMemoria* config) {
	free(logger);
	free(config);
}

//Espera

void sleepAccesoMemoria() {
	t_log* logger;
	configMemoria datos_config;

	log_info(logger, "Retardo de %d segundos.", datos_config.retardoMemoria);
	usleep(datos_config.retardoMemoria);
}

void inicializarMemoria(t_log* logger, configMemoria* datos_config) {

	char** memoria;

	int cant_marcos = datos_config->marcos;
	memoria = malloc(sizeof(char*) * cant_marcos); //Reservo memoria con cantidad de frames disponibles

}

int conexion_kernel(t_log* logger, configMemoria* datos_config) {

	int socketEscucha, socketKernel;
	//	int flag = 1;
	uint16_t codigoHandshake;
	t_package pkg;

	if (escuchar(datos_config->puerto, &socketEscucha, logger)) {
		//ERROR
		//TODO LIBERAR MEM
		return EXIT_FAILURE;

		if (codigoHandshake != CPU_HSK) { // XXX: KERNEL_HSK
			//Checkear que sea el kernel el proceso al que me conecto
			log_error(logger, "Codigo incorrecto de Handshake.");
			return EXIT_FAILURE;
		}

//	while(flag){
//		if(aceptar(socketEscucha, &socketKernel, logger )){
//			//ERROR
//			return EXIT_FAILURE;
//		}
//		if(recibirHandshake(socketKernel, MEMORIA_HSK, &codigoHandshake, logger)){
//			//ERROR
//			close(socketKernel);
//			return EXIT_FAILURE;
//		}
//		printf("Mensaje recibido del kernels: %s\n",pkg.data);
//		free(pkg.data);
//	}

		while (1) {
			printf("Esperando mensaje del CPU.\n"); // XXX: KERNEL
			if (recibir(socketKernel, &pkg, logger)) {
				//ERROR
				close(socketKernel);
				return EXIT_FAILURE;
			}
			printf("Mensaje recibido del CPU: %s\n", pkg.data); // XXX: KERNEL
			char * dato = "0xbfc7c1fc\0";
			switch (pkg.code) {
			case CPU_MEM_DEFVAR: // Me pide reservar memoria para una variable
				enviar(socketKernel, MEM_CPU_POS, dato, strlen(dato), logger);
				break;
			default:
				close(socketKernel);
				return EXIT_FAILURE;
			}
			free(pkg.data);

		}
		if (aceptar(socketEscucha, &socketKernel, logger)) {
			//ERROR
			return EXIT_FAILURE;
		}

		if (recibirHandshake(socketKernel, MEMORIA_HSK, &codigoHandshake,
				logger)) {
			//ERROR
			return EXIT_FAILURE;
		}

		if (codigoHandshake != KERNEL_HSK) { //Checkear que sea el kernel el proceso al que me conecto
			log_error(logger, "Codigo incorrecto de Handshake.");
			return EXIT_FAILURE;
		}

		//	while(flag){
		//	     if(aceptar(socketEscucha, &socketKernel, logger )){
		//	        //ERROR
		//	return EXIT_FAILURE;
		//	}
		//if(recibirHandshake(socketKernel, MEMORIA_HSK, &codigoHandshake, logger)){
		//	  //ERROR
		//return EXIT_FAILURE;
		//}
		//if(codigoHandshake == KERNEL_HSK){//Checkear que sea el kernel el proceso al que me conecto
		//	 flag = 0;
		//	}else{
		//	      close(socketKernel);
		//	}
		//}

		while (1) {
			printf("Esperando mensaje del Kernel.\n");
			if (recibir(socketKernel, &pkg, logger)) {
				//ERROR
				close(socketKernel);
				return EXIT_FAILURE;
			}

			printf("Mensaje recibido del kernel: %s\n", pkg.data);
			free(pkg.data);
		}

		printf("Ingrese una tecla para finalizar.\n");
		getchar();
		liberar_memoria(logger, datos_config);
		return EXIT_SUCCESS;

	}
}

int conexion_cpu(t_log* logger, configMemoria* datos_config) {

	int socketEscucha, socketCPU;
	//	int flag = 1;
	uint16_t codigoHandshake;
	t_package pkg;

	if (escuchar(datos_config->puerto, &socketEscucha, logger)) {
		//ERROR
		//TODO LIBERAR MEM
		return EXIT_FAILURE;
	}
	if (aceptar(socketEscucha, &socketCPU, logger)) {
		//ERROR
		return EXIT_FAILURE;
	}

	if (recibirHandshake(socketCPU, MEMORIA_HSK, &codigoHandshake, logger)) {
		//ERROR
		return EXIT_FAILURE;
	}

	if (codigoHandshake != CPU_HSK) {//Checkear que sea la CPU quien se conecto
		log_error(logger, "Codigo incorrecto de Handshake.");
		return EXIT_FAILURE;
	}

	while (1) {
		printf("Esperando mensaje de la CPU\n");
		if (recibir(socketCPU, &pkg, logger)) {
			//ERROR
			close(socketCPU);
			return EXIT_FAILURE;
		}

		printf("Mensaje recibido de la CPU: %s\n", pkg.data);
		free(pkg.data);
	}

	printf("Ingrese una tecla para finalizar.\n");
	getchar();
	liberar_memoria(logger, datos_config);
	return EXIT_SUCCESS;
}

void funcionesKernel() {

	puts("PROBANDO KERNEL");

}

void funcionesCPU() {

	puts("PROBANDO CPU");

}

void recibir_conexiones(t_log* logger, configMemoria* confM) {

	int socketKernel, socketCPU;

	if (conexion_kernel(logger, confM)) {
		pthread_t hiloKernel;
		pthread_create(&hiloKernel, NULL, (void*) funcionesKernel,
				(void*) socketKernel);
		log_debug(logger, "Conectado con el Kernel");
	}
	if (conexion_cpu(logger, confM)) {
		pthread_t hiloCPU;
		pthread_create(&hiloCPU, NULL, (void*) funcionesCPU, (void*) socketCPU);
		log_debug(logger, "Conectado con la CPU");
		printf("pasamos por aqui");
	}

}
//void conexion_cerrada(socket, ){

//}

int main(int argc, char *argv[]) {

	configMemoria* datos_config;
	t_log* logger;

	logger = log_create("log_memoria", "MEMORIA", 1, LOG_LEVEL_TRACE);
	datos_config = (configMemoria*) cargarConfiguracion("./config", 7, MEMORIA,
			logger);

	inicializarMemoria(logger, datos_config);
	validar_archivo_configMemoria(datos_config, logger);
	consolaMem_imprimir_encabezado();
	consolaMem_imprimir_menu();
	recibir_conexiones(logger, datos_config);

	return 0;
}

