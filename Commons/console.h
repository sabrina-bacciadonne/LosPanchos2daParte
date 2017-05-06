/*
 * console.h
 *
 *  Created on: 8/4/2017
 *      Author: utnso
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "commons.h"



typedef struct {
	char* instruccion;
	char* parametro;
}t_comando;

typedef enum {INIT_PROG,FIN_PROG,DISC_CONSOLE,CLEAR} comandosConsola;



int imprimirConsola(processType proceso);

#endif /* CONSOLE_H_ */
