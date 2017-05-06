/*
 * tad_memoria.h
 *
 *  Created on: 22/4/2017
 *      Author: utnso
 */

#ifndef TAD_MEMORIA_H_
#define TAD_MEMORIA_H_

void consola_reconocerComando();

typedef enum {
	RETARDO = 65,
	DUMP,
	FLUSH,
	SIZE
} comandos;

#endif /* TAD_MEMORIA_H_ */
