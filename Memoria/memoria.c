//
// Created by Martin Gauna on 4/2/17.
//

#include "memoria.h"
#include "tad_memoria.h"

  void liberar_memoria(t_log* logger,configMemoria* config) {
  	free(logger);
  	free(config);
  }

int main () {
	t_log* logger = log_create("log_memoria", "MEMORIA", 1, LOG_LEVEL_TRACE);
	configMemoria* conf = (configMemoria*) cargarConfiguracion( "./config", 7, MEMORIA, logger);
	int socketEscucha, socketKernel;
//	int flag = 1;
	uint16_t codigoHandshake;
	t_package pkg;

	printf("PUERTO: %d\n",conf->puerto);
	printf("MARCOS: %d\n",conf->marcos);
	printf("MARCOS SIZE: %d\n",conf->marcoSize);
	printf("ENTRADAS CACHE: %d\n",conf->entradasCache);
	printf("CACHE X PROC: %d\n",conf->cacheXProc);
	printf("RETARDO MEMORIA: %d\n",conf->retardoMemoria);
	puts("\n");

	imprimirConsola(MEMORIA);
	consola_reconocerComando();


//	if(escuchar(conf->puerto, &socketEscucha, logger)){
//		//ERROR
//		//TODO LIBERAR MEM
//		return EXIT_FAILURE;
//	}
//	if(aceptar(socketEscucha, &socketKernel, logger )){
//		//ERROR
//		return EXIT_FAILURE;
//	}
//	if(recibirHandshake(socketKernel, MEMORIA_HSK, &codigoHandshake, logger)){
//		//ERROR
//		return EXIT_FAILURE;
//	}
//	if(codigoHandshake != KERNEL_HSK){//Checkear que sea el kernel el proceso al que me conecto
//		log_error(logger, "Codigo incorrecto de Handshake.");
//		return EXIT_FAILURE;
//	}
//
////	while(flag){
////		if(aceptar(socketEscucha, &socketKernel, logger )){
////			//ERROR
////			return EXIT_FAILURE;
////		}
////		if(recibirHandshake(socketKernel, MEMORIA_HSK, &codigoHandshake, logger)){
////			//ERROR
////			return EXIT_FAILURE;
////		}
////		if(codigoHandshake == KERNEL_HSK){//Checkear que sea el kernel el proceso al que me conecto
////			flag = 0;
////		}else{
////			close(socketKernel);
////		}
////	}
//
//
//	while(1){
//		printf("Esperando mensaje del Kernel.\n");
//		if(recibir(socketKernel, &pkg, logger)){
//			//ERROR
//			close(socketKernel);
//			return EXIT_FAILURE;
//		}
//		printf("Mensaje recibido del kernels: %s\n",pkg.data);
//		free(pkg.data);
//	}
//
//	printf("Ingrese una tecla para finalizar.\n");
//	getchar();
	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

