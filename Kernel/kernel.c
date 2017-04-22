//
// Created by Martin Gauna on 4/2/17.
//

#include "kernel.h"
#include "tad_kernel.h"

int main (int argc, char *argv[]) {
	t_log* logger = log_create("log_kernel", "KERNEL", 1, LOG_LEVEL_TRACE);
	configKernel* conf = (configKernel*)cargarConfiguracion("./config", 14, KERNEL, logger);
	int socketMemoria,socketFS,socketListen,newSocket,socketCPU=0,socketConsola=0;
	int conectados;
	uint16_t codigoHandshake;
	t_package pkg;
	puts("Kernel.\n");
	printf("ALGORITMO: %s\n",conf->algoritmo);
	printf("GRADO MULTIPROGRAMACION: %d\n",conf->gradoMultiprog);
	printf("IP_FILESYSTEM: %s\n",conf->ipFS);
	printf("IP_MEMORIA: %s\n",conf->ipMemoria);
	printf("PUERTO_CPU: %d\n",conf->puertoCPU);
	printf("PUERTO_FS: %d\n",conf->puertoFS);
	printf("PUERTO_MEMORIA: %d\n",conf->puertoMemoria);
	printf("PUERTO_PROG: %d\n",conf->puerto_prog);
	printf("QUANTUM: %d\n",conf->quantum);
	printf("QUANTUM SLEEP: %d\n",conf->quantumSleep);
	printf("SEM IDS: %s\n",conf->semIds);
	printf("SEM INITS%s\n",conf->semInits);
	printf("SHARED_VARS: %s\n",conf->sharedVars);
	printf("STACK_SIZE: %d\n",conf->stackSize);


	imprimirConsola(KERNEL);
	consola_reconocerComando();

//	if(cargarSoket(conf->puertoMemoria, conf->ipMemoria, &socketMemoria, logger)){
//		//ERROR
//		return EXIT_FAILURE;
//	}
//	if(enviarHandshake(socketMemoria, KERNEL_HSK, MEMORIA_HSK,logger)){
//		//ERROR
//		return EXIT_FAILURE;
//	}
//	log_debug(logger, "Conectado con la memoria.");
//
//	if(cargarSoket(conf->puertoFS, conf->ipFS, &socketFS, logger)){
//		//ERROR
//		return EXIT_FAILURE;
//	}
//	if(enviarHandshake(socketFS, KERNEL_HSK, FILESYSTEM_HSK,logger)){
//		//ERROR
//		return EXIT_FAILURE;
//	}
//	log_debug(logger, "Conectado con el FileSystem.");
//
//	if(escuchar(conf->puerto_prog, &socketListen, logger)){
//		//ERROR
//		return EXIT_FAILURE;
//	}
//
//	for(conectados=0;conectados<2;conectados++){
//
//		if(aceptar(socketListen, &newSocket, logger)){
//			//ERROR
//			return EXIT_FAILURE;
//		}
//		if(recibirHandshake(newSocket, KERNEL_HSK, &codigoHandshake, logger)){
//			//ERROR
//			return EXIT_FAILURE;
//		}
//		if(!socketConsola && codigoHandshake == CONSOLA_HSK){
//			socketConsola = newSocket;
//		}else if(!socketCPU && codigoHandshake == CPU_HSK){
//			socketCPU = newSocket;
//		}else{
//			close(newSocket); //No se reconoce el codigo del Handshake.
//		}
//	}
//
//	while(1){
//		if(recibir(socketConsola, &pkg, logger)){
//			//ERROR
//			closeConections(socketCPU, socketFS, socketMemoria, socketConsola);
//			return EXIT_FAILURE;
//		}
//		printf("Mensaje recibido de la consola: %s\n",pkg.data);
//
//		log_debug(logger, "se envia el mensaje a la CPU");
//		if(enviar(socketCPU, HOLA, pkg.data, pkg.size, logger)){
//			//ERROR
//			closeConections(socketCPU, socketFS, socketMemoria, socketConsola);
//			return EXIT_FAILURE;
//		}
//		log_debug(logger, "se envia el mensaje al File System");
//		if(enviar(socketFS, HOLA, pkg.data, pkg.size, logger)){
//			//ERROR
//			closeConections(socketCPU, socketFS, socketMemoria, socketConsola);
//			return EXIT_FAILURE;
//		}
//		log_debug(logger, "se envia el mensaje a la Memoria");
//		if(enviar(socketMemoria, HOLA, pkg.data, pkg.size, logger)){
//			//ERROR
//			closeConections(socketCPU, socketFS, socketMemoria, socketConsola);
//			return EXIT_FAILURE;
//		}
//		free(pkg.data);
//	}
//	printf("Ingrese una tecla para finalizar.\n");
//	getchar();
	return EXIT_SUCCESS;
}

void liberar_memoria(t_log* logger, configKernel* config) {
	free(logger);
	free(config);
}

void closeConections(int socketCPU, int socketFS, int socketMemoria, int socketConsola){
	close(socketCPU);
	close(socketFS);
	close(socketMemoria);
	close(socketConsola);
}
