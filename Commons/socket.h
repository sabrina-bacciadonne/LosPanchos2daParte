/*
 * socket.h
 *
 *  Created on: 7/4/2017
 *      Author: utnso
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <commons/log.h>
#include <commons/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>

#define packageHeaderSize sizeof(uint32_t) + sizeof(uint16_t);

enum codigoID {CONSOLA, CPU, KERNEL, MEMORIA, FILESYSTEM};

typedef struct {
	uint16_t code;
	uint32_t size;
	char*	data;
}t_package;


int cargarEstructuras(int puerto,char* ip, t_log* logger);
int EnviarHandshake (int socket, uint16_t codigoMio,uint16_t codigoOtro, t_log* logger);
int enviar(int socket,t_package package, t_log* logger);

#endif /* SOCKET_H_ */
