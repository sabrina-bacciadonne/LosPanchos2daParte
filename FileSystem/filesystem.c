//
// Created by Martin Gauna on 4/2/17.
//

#include "filesystem.h"


int main (int argc, char *argv[]) {
	t_log* logger = log_create("log_kernel", "FILESYSTEM", 1, LOG_LEVEL_TRACE);
	configFileSystem* conf = (configFileSystem*) cargarConfiguracion(argv[1], 2, FILESYSTEM, logger);

	puts("FileSystem.");
	printf("PUERTO: %d\n",conf->puerto);
	printf("PUNTO MONTAJE: %s\n",conf->puntoMontaje);

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configFileSystem* config) {
	free(logger);
	free(config);
}
