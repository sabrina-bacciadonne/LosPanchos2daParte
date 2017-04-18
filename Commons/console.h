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



int imprimirConsola(processType proceso);
void reconocerComando(processType proceso);

#endif /* CONSOLE_H_ */
