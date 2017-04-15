/*
 * socket.c
 *
 *  Created on: 7/4/2017
 *      Author: utnso
 */

#include "socket.h"

int escuchar(int puerto, int* socket, t_log* logger){
	int listenBacklog = BACKLOG;
	char* port;
	if(cargarSoket(puerto, "",  socket, logger)){
		return EXIT_FAILURE;
	}
	port = itoa(puerto);
	log_info(logger, "Escuchando en el puerto:", port);
	free(port);
	if(listen(*socket, listenBacklog) < 0){
		log_error(logger, "Error en el listen:",strerror(errno));
		close(*socket);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int acceptar(int* socket,int* newSocket, t_log* logger){
	struct sockaddr_storage their_addr;
	socklen_t addrSize;
	addrSize = sizeof their_addr;
	*newSocket = accept(*socket, (struct sockaddr *)&their_addr, &addrSize);
	if(*newSocket < 0){
		log_error(logger, "Error en el accept:",strerror(errno));
		close(*socket);
		return EXIT_FAILURE;
	}
	log_info(logger, "Conexion aceptada.");
	return EXIT_SUCCESS;
}

/*Funcion que crea el socket para escucha o para conectarse*/
int cargarSoket(int iPuerto,const char* ip, int* pSocket, t_log* logger){
	int socketFD;
	struct addrinfo hints, *servInfo, *p;
	int rv;
	char* puerto = string_itoa(iPuerto);

	if(!strcmp(puerto,"")){
		log_error(logger,"Error al convertir el puerto a string.");
		return EXIT_FAILURE;
	}
	memset(&hints,0,sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	printf("Is Empty: %d\n",strcmp(ip,""));
	if(!strcmp(ip,"")){		// use my IP
		hints.ai_flags = AI_PASSIVE;
		ip = NULL;
	}

	if ((rv = getaddrinfo(ip, puerto, &hints, &servInfo)) != 0) {
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
	*pSocket = socketFD;
	return EXIT_SUCCESS;
}

int EnviarHandshake (int socket, uint16_t codigoMio, uint16_t codigoOtro, t_log* logger){
	t_package handshakeRcv;

	if(enviar(socket,codigoMio,NULL,0,logger)){
		log_error(logger, "Error al enviar el handshake");
		return EXIT_FAILURE;
	}
	if(recibir(socket, &handshakeRcv, logger)){
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
	if (compressPack != NULL){
		memcpy(compressPack, &code, sizeof(uint16_t));
		memcpy(compressPack + sizeof(uint16_t), &size, sizeof(uint32_t));
		memcpy(compressPack + packageSize(0), data, size);
		return compressPack;
	}
	log_error(logger,"Error al asignar espacio para el packete de salida");
	return NULL;
}

int enviar(int socket, uint16_t code, char* data, uint32_t size, t_log* logger){
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

int recibir(int socket,t_package* mensaje, t_log* logger){
	int headerSize = packageHeaderSize;
	char* buffer;
	char* dbgMsj;
	mensaje = (t_package *)malloc(headerSize + sizeof(char *));
	//Recibo el primer parametro del header.
	if(recvPkg(socket, &buffer, headerSize, logger)){
		return EXIT_FAILURE;
	}
	//descomprimo el header.
	memcpy(&(mensaje->code), buffer, sizeof(uint16_t));
	memcpy(&(mensaje->size), buffer+sizeof(uint16_t), sizeof(uint32_t));
	dbgMsj = string_from_format("Code:%d\tSize:%d", mensaje->code,mensaje->size);
	log_debug(logger, dbgMsj);
	free(dbgMsj);
	free(buffer);
	if(recvPkg(socket, &buffer,mensaje->size, logger)){
		return EXIT_FAILURE;
	}
	log_trace(logger, "Data: ", buffer);
	mensaje->data = buffer;

	return EXIT_SUCCESS;
}

int recvPkg(int socket, char** buffer, uint32_t size, t_log* logger){
	int recibido;
	char* buff = (char*)malloc(sizeof(size));
	char* errorMsj;
	recibido = recv(socket, buff, size,0);
	if(recibido < 0){
		log_error(logger, "Error al recibir: ",strerror(errno));
		close(socket);
		return EXIT_FAILURE;
	}
	if(recibido < size){
		log_error(logger, "El tamanio del mensaje no coincide con el esperado.");
		errorMsj = string_from_format("Recibido:%d \tEsperado:%d", recibido, size);
		log_error(logger, errorMsj);
		free(errorMsj);
		close(socket);
		return EXIT_FAILURE;
	}
	*(buffer) = buff;
	return EXIT_SUCCESS;
}
