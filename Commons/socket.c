/*
 * socket.c
 *
 *  Created on: 7/4/2017
 *      Author: utnso
 */

#include "socket.h"


int cargarEstructuras(int puerto,char* ip, t_log* logger){
	int socketFD, errorLength;
	struct addrinfo hints, *servInfo, *p;
	int rv;
	socklen_t addrLen;
	char s[INET_ADDRSTRLEN];

	memset(&hints,0,sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	if(string_is_empty(ip)){		// use my IP
		hints.ai_flags = AI_PASSIVE;
		ip = NULL;
	}

	if ((rv = getaddrinfo(ip, puerto, &hints, &servInfo)) != 0) {
		errorLength = strlen("getaddrinfo: \n") + ) + 1;
		char* addrError = string_from_format("getaddrinfo: %s\n", gai_strerror(rv));
		log_error(logger,addrError);
		free(addrError);
		return EXIT_FAILURE;
	}
	for(p = servInfo; p != NULL; p = p->ai_next) {
		if ((socketFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			log_warning(logger, "Socket error:",strerror(errno));
			continue;
		}
		if(ip == NULL){
			if(bind(socketFD, p->ai_addr, p->ai_addrlen) == -1) {
				close(socketFD);
				log_warning(logger, "Bind error:",strerror(errno));
				continue;
			}
		}
		else{
			if (connect(socketFD, p->ai_addr, p->ai_addrlen) == -1) {
				close(socketFD);
				log_warning(logger, "Connect error:",strerror(errno));
				continue;
			}
		}
		break;
	}
	if(p==NULL){
		log_error(logger, "No Socket could be created");
		freeaddrinfo(servInfo);
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(servInfo);
	return socketFD;
}

int EnviarHandshake (int socket, uint16_t codigoMio,uint16_t codigoOtro, t_log* logger){

	t_package handshakeMsg;
	t_package* handshakeRcv;
	handshakeMsg.code = codigoMio;

	if(enviar(socket,codigoMio,NULL,logger)){
		log_error(logger, "Error al enviar el handshake");
		return EXIT_FAILURE;
	}
	if(recibir(socket,&handshakeRcv,logger)){
		log_error(logger,"Error al recibir el handshake");
		return EXIT_FAILURE;
	}
	if(handshakeRcv.code != codigoOtro){
		log_warning(logger, "Codigo de handshake incorrecto");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

uint32_t packageSize(uint32_t size){
	return size + packageHeaderSize;
}

char* compress(int code, char* data, uint32_t size, t_log* logger){
	char* compressPack = (char*) malloc(packageSize(size));
	if (compressPack){
		memcpy(compressPack,code, sizeof(uint16_t));
		memcpy(compressPack, size, sizeof(uint32_t));
		memcpy(compressPack, data, data);
		return compressPack;
	}
	log_error(logger,"Error al asignar espacio para el packete de salida");
	return NULL;
}

int enviar(int socket, int code, char* data, uint32_t size, t_log* logger){
	log_trace(logger,"enviar()");
	char* package = compress(code, data, size, logger);
	int sizeOfData = packageSize(size);
	int totalDataSent = 0;
	int sent;

	do{
		sent = send(socket, package, packageSize(size), 0);
		if (sent< 0){
			log_error(logger, "Error al enviar: ",strerror(errno));
			return EXIT_FAILURE;
		}
		totalDataSent += sent;
	}while(totalDataSent < sizeOfData);
	log_debug(logger, "Error al enviar: ",strerror(errno));
	return EXIT_SUCCESS;
}
