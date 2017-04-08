//
// Created by Martin Gauna on 4/2/17.
//

#include "memoria.h"

int main () {
	t_log* logger = log_create("log_memoria", "MEMORIA", 1, LOG_LEVEL_TRACE);
	processType process = MEMORIA;
	configMemoria* conf = (configMemoria*) cargarConfiguracion( "./config", 7, process, logger);

	puts("MEMORIA.");
	printf("PUERTO: %d\n",conf->puerto);
	printf("MARCOS: %d\n",conf->marcos);
	printf("MARCOS SIZE: %d\n",conf->marcoSize);
	printf("ENTRADAS CACHE: %d\n",conf->entradasCache);
	printf("CACHE X PROC: %d\n",conf->cacheXProc);
	printf("RETARDO MEMORIA: %d\n",conf->retardoMemoria);

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configMemoria* config) {
	free(logger);
	free(config);
}
