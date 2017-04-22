/*
 * tad_kernel.h
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#ifndef TAD_KERNEL_H_
#define TAD_KERNEL_H_

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void consola_reconocerComando();

typedef enum {
	PRINT_PROC = 65,
	PRINT_PROC_X_STAT,
	CANT_RAF,
	CANT_OP_PRIV,
	PRINT_FILE_TABLE,
	PRINT_HEAP_PAGES,
	PRINT_ALLOC_AMOUNT,
	PRINT_FREE_AMOUNT,
	PRINT_SYSCALLS_AMOUNT,
	PRINT_HEAP_AMOUNT,
	PRINT_GLOBAL_FILE_TABLE,
	MODIFY_MULTIPROG,
	END_PROC,
	STOP_PLANIF
} comandos;

#endif /* TAD_KERNEL_H_ */
