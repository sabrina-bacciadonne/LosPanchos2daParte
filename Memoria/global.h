/*
 * global.h
 *
 *  Created on: 7/5/2017
 *      Author: utnso
 */

#ifndef SRC_GLOBAL_H_
#define SRC_GLOBAL_H_

typedef struct {
	t_config * config;
	int32_t puerto;
	char *ip;
	int32_t marcos;
	int32_t marcos_size;
	int32_t entradas_cache;
	int32_t cache_x_proc;
	char *reemplazo_cache;
	int32_t retardo_memoria;
} t_mem_server;


#endif /* SRC_GLOBAL_H_ */
