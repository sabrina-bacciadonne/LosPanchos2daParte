/*
 * tad_consola.h
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#ifndef TAD_CONSOLA_H_
#define TAD_CONSOLA_H_

#include "consola.h"
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {

	FILE* archivo;
	char* ruta;

} t_datos_hilo_programa;


void* consola_hiloPrograma(void* arg);
int consola_reconocerComando();


typedef enum {INIT_PROGRAM = 65, FIN_PROGRAM, DISCONNECT, CLEAN} comandos;


#endif /* TAD_CONSOLA_H_ */
