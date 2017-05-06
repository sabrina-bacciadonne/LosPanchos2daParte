//
// Created by Martin Gauna on 4/2/17.
//

#ifndef TP_2017_1C_LOSPANCHOS_CONSOLA_H
#define TP_2017_1C_LOSPANCHOS_CONSOLA_H

#include "../Commons/configuracion.h"
#include "../Commons/socket.h"
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <stdio.h>
#include "tad_consola.h"

extern t_log* logger;
extern t_list* hilos;
extern configConsole* conf;
extern pthread_mutex_t mutex_log;

void consola_imprimir_encabezado();
void consola_imprimir_menu();
void liberar_memoria();

void agregar_hilo_lista(pthread_mutex_t* semaforo, t_list* lista, pthread_t* hilo);
void imprimirConsola();

#endif //TP_2017_1C_LOSPANCHOS_CONSOLA_C_H




