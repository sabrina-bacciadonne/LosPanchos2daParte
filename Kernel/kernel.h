//
// Created by Martin Gauna on 4/2/17.
//

#ifndef TP_2017_1C_LOSPANCHOS_KERNEL_H
#define TP_2017_1C_LOSPANCHOS_KERNEL_H

#include "../Commons/configuracion.h"
#include "../Commons/socket.h"
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>

typedef struct {
	int socket;
	int pid;
	char* ansisop;
}t_proceso;


void liberar_memoria(t_log* logger, configKernel* config);
void closeConections(int socketCPU, int socketFS, int socketMemoria, int socketConsola);
void printConfig(configKernel* conf);
int aceptarConexion(int socketListen,fd_set* readSet,int* nfd, t_dictionary* cpus, t_dictionary* consolas,int* pidCount, t_log* logger);


int atenderConsola(t_proceso* proc, int* pidCount, t_log* logger);
int crearPidSock(int* pidCount);

#endif //TP_2017_1C_LOSPANCHOS_KERNEL_H
