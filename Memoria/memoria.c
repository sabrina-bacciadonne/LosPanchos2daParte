
#include "memoria.h"

  void liberar_memoria(t_log* logger,configMemoria* config) {
  	free(logger);
  	free(config);
  }

int main () {
	t_log* logger = log_create("log_memoria", "MEMORIA", 1, LOG_LEVEL_TRACE);
	t_mem_server* conf = (t_mem_server*) cargarConfiguracion( "./config", 7, MEMORIA, logger);
	int socketEscucha, socketKernel;
//	int flag = 1;
	uint16_t codigoHandshake;
	t_package pkg;

	printf("PUERTO: %d\n",conf->puerto);
	printf("MARCOS: %d\n",conf->marcos);
	printf("MARCOS SIZE: %d\n",conf->marcos_size);
	printf("ENTRADAS CACHE: %d\n",conf->entradas_cache);
	printf("CACHE X PROC: %d\n",conf->cache_x_proc);
	printf("RETARDO MEMORIA: %d\n",conf->retardo_memoria);
	puts("\n");

	imprimirConsola(MEMORIA);
	consola_reconocerComando();
	//memoriaInit(conf);


	if(escuchar(conf->puerto, &socketEscucha, logger)){
		//ERROR
		//TODO LIBERAR MEM
		return EXIT_FAILURE;
	}
	if(aceptar(socketEscucha, &socketKernel, logger )){
		//ERROR
		return EXIT_FAILURE;
	}
	if(recibirHandshake(socketKernel, MEMORIA_HSK, &codigoHandshake, logger)){
		//ERROR
		return EXIT_FAILURE;
	}
	if(codigoHandshake != CPU_HSK){ // XXX: KERNEL_HSK
		//Checkear que sea el kernel el proceso al que me conecto
		log_error(logger, "Codigo incorrecto de Handshake.");
		return EXIT_FAILURE;
	}

//	while(flag){
//		if(aceptar(socketEscucha, &socketKernel, logger )){
//			//ERROR
//			return EXIT_FAILURE;
//		}
//		if(recibirHandshake(socketKernel, MEMORIA_HSK, &codigoHandshake, logger)){
//			//ERROR
//			close(socketKernel);
//			return EXIT_FAILURE;
//		}
//		printf("Mensaje recibido del kernels: %s\n",pkg.data);
//		free(pkg.data);
//	}

	while(1){
		printf("Esperando mensaje del CPU.\n"); // XXX: KERNEL
		if(recibir(socketKernel, &pkg, logger)){
			//ERROR
			close(socketKernel);
			return EXIT_FAILURE;
		}
		printf("Mensaje recibido del CPU: %s\n",pkg.data); // XXX: KERNEL
		char * dato = "0xbfc7c1fc\0";
		switch(pkg.code) {
			case CPU_MEM_DEFVAR: // Me pide reservar memoria para una variable
				enviar(socketKernel, MEM_CPU_POS, dato, strlen(dato), logger);
				break;
			default:
				close(socketKernel);
				return EXIT_FAILURE;
		}
		free(pkg.data);
	}

	printf("Ingrese una tecla para finalizar.\n");
	getchar();
	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}

