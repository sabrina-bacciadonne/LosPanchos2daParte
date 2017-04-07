//
// Created by Martin Gauna on 4/2/17.
//

#include "filesystem.h"

int main () {
	t_log* logger = log_create("log_kernel", "FILESYSTEM", 1, LOG_LEVEL_TRACE);
	processType process = FILESYSTEM;
	configFileSystem* conf = (configFileSystem*) cargarConfiguracion( "./config", 2, process, logger);

	puts("FileSystem.");
	printf("%d\n",conf->puerto);
	puts(conf->puntoMontaje);

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configMemoria* config) {
	free(logger);
	free(config);
}
