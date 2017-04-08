//
// Created by Martin Gauna on 4/2/17.
//

#include "cpu.h"

int main (int argc, char *argv[]) {
	t_log* logger = log_create("log_kernel", "CPU", 1, LOG_LEVEL_TRACE);
	processType process = CPU;
	configCPU* conf = (configCPU*) cargarConfiguracion(argv[1], 4, process, logger);

	puts("CPU.");
	printf("IP_KERNEL: %s\n",conf->ipKernel);
	printf("IP_MEMORIA: %s\n",conf->ipMemoria);
	printf("PUERTO_KERNEL: %d\n",conf->puertoKernel);
	printf("PUERTO_MEMORIA %d\n",conf->puertoMemoria);

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configCPU* config) {
	free(logger);
	free(config);
}
