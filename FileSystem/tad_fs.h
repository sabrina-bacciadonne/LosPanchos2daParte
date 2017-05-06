/*
 * tad_fs.h
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#ifndef TAD_FS_H_
#define TAD_FS_H_


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void consola_reconocerComando();

typedef enum {INIT_PROGRAM = 49, FIN_PROGRAM, DISCONNECT, CLEAN} comandos;

#endif /* TAD_FS_H_ */
