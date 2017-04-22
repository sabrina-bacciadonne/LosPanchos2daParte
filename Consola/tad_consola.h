/*
 * tad_consola.h
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#ifndef TAD_CONSOLA_H_
#define TAD_CONSOLA_H_

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void consola_reconocerComando();

typedef enum {INIT_PROGRAM = 65, FIN_PROGRAM, DISCONNECT, CLEAN} comandos;


#endif /* TAD_CONSOLA_H_ */
