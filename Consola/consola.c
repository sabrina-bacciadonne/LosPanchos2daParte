//
// Created by Martin Gauna on 4/2/17.
//

#include "consola.h"

t_log* logger;
t_list* hilos;
configConsole* conf;
pthread_mutex_t mutex_log;

void agregar_hilo_lista(pthread_mutex_t* semaforo, t_list* lista, pthread_t* hilo) {
	pthread_mutex_lock(semaforo);
	list_add(lista,hilo);
	pthread_mutex_unlock(semaforo);
}

int main(int argc, char *argv[]) {
	logger = log_create("log_consola", "CONSOLA", 1, LOG_LEVEL_TRACE);
	conf = (configConsole*) cargarConfiguracion("./config", 2, CONSOLA, logger);
	hilos = list_create();

	printf("IP_KERNEL: %s\n", conf->ip);
	printf("PUERTO KERNEL: %d\n", conf->puerto);
	printf("\n");
	printf("\n");
	printf("\n");


	imprimirConsola(CONSOLA);
	while ((consola_reconocerComando() == 0)) {
		imprimirConsola(CONSOLA);
	}

	liberar_memoria();
	return EXIT_SUCCESS;
}

void liberar_memoria() {
	free(logger);
	free(conf);
}

