/*
 * memoria_core.h
 *
 *  Created on: 17/04/2017
 *      Author: epreyes
 */

#ifndef TEST_H_
#define TEST_H_

//#include <stdio.h>
#include <stdlib.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <commons/config.h>
#include "pruebas.h"


// Codigos de retorno

#define MARCOS_INSUFICIENTES 1001
#define MARCO_INVALIDO 1002
#define MARCO_DEMASIADO_CHICO 1003


// Elemento de la tabla de paginas invertida
typedef struct {
	int pagina;
	int idProceso;
	int marco;
} t_mem;

typedef struct {
	t_config * config;
	int32_t puerto;
	char *ip;
	int32_t marcos;
	int32_t marcos_size;
	int32_t entradas_cache;
	int32_t cache_x_proc;
	char *reemplazo_cache;
	int32_t retardo_memoria;
} t_mem_server;



// cantidad de marcos de la tabla de paginas
int marcosTablaPagina;

// Memoria principal
char *memoria;

// Logger
t_log *logger;

// TODO: debe tomarse de la configuracion
#define CANTIDAD_MARCOS 10
#define TAMANIO_MARCO 20

typedef unsigned char bloqueMemoria[TAMANIO_MARCO];

int obtenerMarcosTablaPaginas();
void generarTablaPaginas();
int asignarPaginaAProceso(int pid, int cantPaginasRequeridas);
void listarTablaPaginas();
int leerMemoria(int processId, int pagina, int offset, char *res);
int escribirMemoria(int processId, int pagina, int offset, char* buffer, int tamanio);
int traducirADireccionFisica(int pagina, int processId);
t_mem* buscarPaginaPorMarco(int marco);
int liberarProcesoMemoria(int processId);
void liberarMemoria();
bloqueMemoria* getComienzoMemoria();
t_list* obtenerTablaPaginas();
void memoriaInit(t_mem_server* config);

//void pruebas(t_log* logger, int marcosTablaPagina, t_mem_server* mem);

#endif /* TEST_H_ */
