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
		char* ip_kernel;
		int puerto_kernel;
	} t_datos_config;

int validar_archivo_config(t_datos_config* datos,t_log* logger);
void cerrar_archivo_config();
void validar_ip(char* ip, t_log* logger);
