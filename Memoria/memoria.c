//
// Created by Martin Gauna on 4/2/17.
//

#include "memoria.h"


int main () {
	t_log* logger = log_create("log_memoria", "MEMORIA", 1, LOG_LEVEL_TRACE);
	processType process = MEMORIA;
	configMemoria* conf = (configMemoria*) cargarConfiguracion( "./config", 7, process, logger);

	puts("MEMORIA.");
	printf("%d",conf->puerto);

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configMemoria* config) {
	free(logger);
	free(config);
}
