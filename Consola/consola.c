//
// Created by Martin Gauna on 4/2/17.
//

#include "consola.h"


int main (int argc, char *argv[]) {
	t_log* logger = log_create("log_consola", "CONSOLA", 1, LOG_LEVEL_TRACE);
	configConsole* conf = (configConsole*) cargarConfiguracion("./config", 2, CONSOLA, logger);
	int socketKernel;

	printf("IP_KERNEL: %s\n",conf->ip);
	printf("PUERTO KERNEL: %d\n",conf->puerto);
	imprimirConsola(CONSOLA);
	reconocerComando(CONSOLA);

//	//Me conecto Al Kernel
//	if(cargarSoket(conf->puerto, conf->ip, &socketKernel, logger)){
//		//ERROR
//	}
//	//Hago el handshake con el Kernel.
//	if(enviarHandshake(socketKernel, CONSOLA_HSK, KERNEL_HSK,logger)){
//		//ERROR
//	}
//	while(1){
////		consola_imprimir_menu();
//		printf("Ingrese una tecla para enviar \"HOLA!\" al Kernel.\n");
//		getchar();
//		if(enviar(socketKernel,HOLA,"HOLA!",strlen("HOLA!"),logger)){
//			//ERROR
//			close(socketKernel);
//			return EXIT_FAILURE;
//		}
//	}

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger,configConsole* config) {
	free(logger);
	free(config);
}

