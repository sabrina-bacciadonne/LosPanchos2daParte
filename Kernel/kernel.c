//
// Created by Martin Gauna on 4/2/17.
//

#include "kernel.h"


int main () {
	t_log* logger = log_create("log_kernel", "KERNEL", 14, LOG_LEVEL_TRACE);
	processType process = KERNEL;
	configKernel* conf = (configKernel*) cargarConfiguracion( "./config", 14, process, logger);

	puts("Kernel.");

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configKernel* config) {
	free(logger);
	free(config);
}
