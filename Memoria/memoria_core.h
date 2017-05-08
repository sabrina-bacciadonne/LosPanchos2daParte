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
#include "global.h"

// Codigos de retorno

#define MARCOS_INSUFICIENTES 1001
#define MARCO_INVALIDO 1002
#define MARCO_DEMASIADO_CHICO 1003

#define MARCO_LIBRE 0

// Elemento de la tabla de paginas invertida
typedef struct {
	int pagina;
	int idProceso;
	int marco;
} t_mem;

// cantidad de marcos de la tabla de paginas
int marcosTablaPagina;

// Memoria principal
char *memoria;

// Logger
t_log *logger;

int obtenerMarcosTablaPaginas();
int obtenerMarcosMemoriaFisica();
void generarTablaPaginas();
int asignarPaginaAProceso(int pid, int cantPaginasRequeridas);
void listarTablaPaginas();
int leerMemoria(int processId, int pagina, int offset, char *res);
int escribirMemoria(int processId, int pagina, int offset, char* buffer,
		int tamanio);
int traducirADireccionFisica(int pagina, int processId);
t_mem* buscarPaginaPorMarco(int marco);
int liberarProcesoMemoria(int processId);
void liberarMemoria();
char* getComienzoMemoria();
t_list* obtenerTablaPaginas();
void memoriaInit(t_mem_server* config);
int obtenerIdUltimaPagina(int pid);

//void pruebas(t_log* logger, int marcosTablaPagina, t_mem_server* mem);

#endif /* TEST_H_ */
