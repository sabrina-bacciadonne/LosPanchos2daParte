/*
 * archivo_configuracion.h
 *
 *  Created on: 3/4/2017
 *      Author: utnso
 */

#ifndef ARCHIVO_CONFIGURACION_H_
#define ARCHIVO_CONFIGURACION_H_



#endif /* ARCHIVO_CONFIGURACION_H_ */

#include <commons/log.h>
#include <stdio.h>
#include <stdlib.h>

	typedef struct {
		int puerto_prog;
		int puerto_cpu;
		char* ip_memoria;
		char* ip_fs;
		int puerto_fs;
		int quantum;
		int quantum_sleep;
		char* algoritmo;
		int grado_multiprog;
		//SEMS_ID
		//SEMS_INIT
		//SHARED_VARS
		int stack_size;
	} t_datos_config;

t_datos_config* validar_archivo_config(t_datos_config* datos,t_log* logger);
void cerrar_archivo_config();
void validar_ip(char* ip, t_log* logger);
