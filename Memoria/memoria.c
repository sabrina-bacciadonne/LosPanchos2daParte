//
// Created by Martin Gauna on 4/2/17.
//

#include "memoria.h"

  void consolaMem_imprimir_encabezado(){
     printf("**** BIENVENIDO A LA CONSOLA MEMORIA****\n");
     printf("\n");
  }
  void consolaMem_imprimir_menu(){
     printf("Por favor seleccione la opcion correspondiente:\n");
     printf("\n");
     printf("1) Retardo\n");
     printf("2) Dump\n");
     printf("3) Flush\n");
     printf("4) Size\n");
  }

  void validar_archivo_configMemoria(configMemoria* datos_config,t_log* logger) {
     t_config* config;
     config = config_create(
     "/home/utnso/git/tp-2017-1c--LosPanchos/Memoria/config");

  }

  void liberar_memoria(t_log* logger,configMemoria* config) {
  	free(logger);
  	free(config);
  }

int main () {
	t_log* logger = log_create("log_memoria", "MEMORIA", 1, LOG_LEVEL_TRACE);
	configMemoria* conf = (configMemoria*) cargarConfiguracion( "./config", 7, MEMORIA, logger);

	consolaMem_imprimir_encabezado();
	consolaMem_imprimir_menu();

	puts("\n");
	puts("MEMORIA:\n");
	printf("PUERTO: %d\n",conf->puerto);
	printf("MARCOS: %d\n",conf->marcos);
	printf("MARCOS SIZE: %d\n",conf->marcoSize);
	printf("ENTRADAS CACHE: %d\n",conf->entradasCache);
	printf("CACHE X PROC: %d\n",conf->cacheXProc);
	printf("RETARDO MEMORIA: %d\n",conf->retardoMemoria);

	liberar_memoria(logger, conf);
	return EXIT_SUCCESS;
}
