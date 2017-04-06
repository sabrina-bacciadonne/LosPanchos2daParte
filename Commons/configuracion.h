/*
 * archivo_configuracion.h
 *
 *  Created on: 3/4/2017
 *      Author: utnso
 */

#ifndef ARCHIVO_CONFIGURACION_H_
#define ARCHIVO_CONFIGURACION_H_

#include <commons/log.h>
#include <commons/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define PUERTO_MAX 1024

////Console
//#define IP_KERNEL "IP_KERNEL"
//#define PUERTO_KERNEL "PUERTO_KERNEL"

	typedef struct {
		char* 	ip;
		int 	puerto;
	}configConsole;

////Kernel
//PUERTO_PROG
//PUERTO_CPU
//IP_MEMORIA
//PUERTO_MEMORIA
//IP_FS
//PUERTO_FS
//QUANTUM
//QUANTUM_SLEEP
//ALGORITMO
//GRADO_MULTIPROG
//SEM_IDS
//SEM_INIT
//SHARED_VARS
//STACK_SIZE
	typedef struct {
		int	puerto_prog;
		int puertoCPU;
		char* ipMemoria;
		int puertoMemoria;
		char* ipFS;
		int puertoFS;
		int quantum;
		int quantumSleep;
		char* algoritmo;
		int gradoMultiprog;
		char* semIds;
		char* semInits;
		char* sharedVars;
		int stackSize;
	} configKernel;

////FileSystem
//PUERTO
//PUNTO_MONTAJE
	typedef struct {
		int 	puerto;
		char*	puntoMontaje;
	}configFileSystem;

////Memoria
//PUERTO
//MARCOS
//MARCO_SIZE
//ENTRADAS_CACHE
//CACHE_X_PROC
//RETARDO_MEMORIA
	typedef struct {
		int	puerto;
		int	marcos;
		int marcoSize;
		int entradasCache;
		int cacheXProc;
		int retardoMemoria;
	}configMemoria;

////CPU
//PUERTO_KERNEL
//IP_KERNEL
//PUERTO_MEMORIA
//IP_MEMORIA
	typedef struct {
		int puertoKernel;
		char* ipKernel;
		int puertoMemoria;
		char* ipMemoria;
	}configCPU;

	typedef enum {CONSOLA, CPU, FILESYSTEM, KERNEL, MEMORIA} processType;

	void* cargarConfiguracion (char* path,int configParamAmount,processType configType, t_log* logger);
	char* leerString (void* configFile, char* parametro, t_log* logger);
	int leerInt (void* configFile, char* parametro, t_log* logger);
	int leerPuerto (void* configFile, char* parametro, t_log* logger);
	char* leerIP (void* configFile, char* parametro, t_log* logger);
	char* leerString (void* configFile, char* parametro, t_log* logger);
	void cerrar_archivo_config ();
	void validar_ip (char* ip, t_log* logger);
	void validar_puerto (int puerto, t_log* logger);

#endif /* ARCHIVO_CONFIGURACION_H_ */

