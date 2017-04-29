/*
 * tad_consola.c
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#include "tad_consola.h"
#include <sys/stat.h>



void consola_terminarPrograma() {
	puts("Terminar programa");
}

void* consola_hiloPrograma(void* args) {

	t_datos_hilo_programa* argumentos = args;				//ACA ESTAN LOS PARAMETROS DEL HILO
	int socketKernel;
	char* contenido_archivo_ansisop;

//	//Me conecto Al Kernel
//	if (cargarSoket(conf->puerto, conf->ip, &socketKernel, logger)) {
//		//ERROR
//	}
//	//Hago el handshake con el Kernel.
//	if (enviarHandshake(socketKernel, CONSOLA_HSK, KERNEL_HSK, logger)) {
//		//ERROR
//	}

//	puts(argumentos->ruta);

	struct stat prueba;
	stat(argumentos->ruta,&prueba);
	off_t tamanio = prueba.st_size;		//ACA ESTA EL TAMANIO DEL ARCHIVO
	printf("%d",tamanio);

	contenido_archivo_ansisop = malloc(sizeof(char)*tamanio);

	fread(contenido_archivo_ansisop,1,tamanio,argumentos->archivo); //LEO EL CONTENIDO Y GUARDO EN CONTENIDO_ARCHIVO_ANSISOP

//	if(!enviar(socketKernel,INICIAR_PROG,contenido_archivo_ansisop,tamanio,logger)){
//		puts ("NO PUDE ENVIAR NADA\n");
//	}

	//LIBERO MEMORIA

	free(contenido_archivo_ansisop);
	free(argumentos);
	close(socketKernel);

	pthread_t hilo = pthread_self();
//	list_remove(hilos,hilo);
	return NULL;
}

int consola_crearProgramaANSISOP() {

	pthread_attr_t attr;
	pthread_t hilo;
	char ruta[4096];
	FILE* archivo;

	puts("Por favor, ingrese la ruta del script Ansisop:");
	scanf("%s", ruta);

	if ((archivo = fopen(ruta, "r")) == NULL) {
		puts("El archivo indicado no existe. Intente nuevamente");
		return EXIT_FAILURE;
	}

	t_datos_hilo_programa* args = malloc(sizeof(t_datos_hilo_programa)); //ESTRUCTURA CON DATOS DEL HILO
	args->archivo = archivo;
	args->ruta = ruta;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


	if(pthread_create(&hilo, NULL, consola_hiloPrograma, args)) {
		free(args);
	}

//	agregar_hilo_lista(&mutex_log,&hilos,&hilo);


	list_add(hilos, &hilo);					//AGREGAR SINCRONIZACION

	pthread_attr_destroy(&attr);

	free(args);

	return -1;

}

int consola_desconectarConsola() {
	puts("Desconectando consola");
	return EXIT_SUCCESS;

}

int consola_reconocerComando() {

	int leer;
	scanf("%d", &leer);
	int opcion = getchar();

//	while (opcion < INIT_PROGRAM || opcion > CLEAN) {
//		puts("La opción ingresada es incorrecta. Intente nuevamente.");
//		scanf("%d", &leer);
//		opcion = getchar();
//	}
//
//	switch (opcion) {
//	case INIT_PROGRAM:
//		consola_crearProgramaANSISOP();
//		return EXIT_SUCCESS;
//		break;
//	case FIN_PROGRAM:
//		consola_terminarPrograma();
//		return EXIT_SUCCESS;
//		break;
//	case DISCONNECT:
//		consola_desconectarConsola();
//		break;
//	case CLEAN:
//		system("clear");
//		return EXIT_SUCCESS;
//		break;
//	}

	return EXIT_FAILURE;
}
