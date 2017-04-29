/*
 * tad_consola.c
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#include "tad_consola.h"


void consola_terminarPrograma() {
	puts("Terminar programa");
}

void* consola_hiloPrograma() {

	int socketKernel;
	//Me conecto Al Kernel
	if (cargarSoket(conf->puerto,conf.ip,&socketKernel, logger)) {
		//ERROR
	}
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


	pthread_t hilo = pthread_self();
//	list_remove(hilos,hilo);
	return NULL;
}

int consola_crearPrograma() {

	pthread_attr_t attr;
	pthread_t hilo;
	char *arg1 = "hilo1: ";


	char ruta[100];
	FILE* archivo;

	puts("Por favor, ingrese la ruta del script Ansisop:");
	scanf("%s", ruta);

	if ((archivo = fopen(ruta, "r")) == NULL) {
		puts("El archivo indicado no existe. Intente nuevamente");
		return -1;
	}

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&hilo,NULL,consola_hiloPrograma(), arg1);		//CREAR HILO PASANDOLE ARCHIVO PARA QUE LEA Y ENVIE POR SOCKET

	list_add(hilos,&hilo);					//AGREGAR SINCRONIZACION

	pthread_attr_destroy(&attr);

	return EXIT_SUCCESS;



}

int consola_desconectarConsola() {
	return 0;

}

int consola_reconocerComando() {

	int opcion = toupper(getchar());

	while (opcion < INIT_PROGRAM || opcion > CLEAN) {
		puts("La opción ingresada es incorrecta. Intente nuevamente.");
		opcion = toupper(getchar());
	}

	switch (opcion) {
	case INIT_PROGRAM:
		consola_crearPrograma();
		return -1;
		break;
	case FIN_PROGRAM:
		consola_terminarPrograma();
		break;
	case DISCONNECT:
		consola_desconectarConsola();
		break;
	case CLEAN:
		system("clear");
		break;
	}



}

