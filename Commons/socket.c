/*
 * socket.c
 *
 *  Created on: 7/4/2017
 *      Author: utnso
 */

#include "socket.h"


int cargarEstructuras(int puerto,char* ip, t_log* logger){
	int socketFD, errorLength;
	struct addrinfo hints, *servInfo, p;
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
		errorLength = strlen("getaddrinfo: \n") + strlen(gai_strerror(rv)) + 1;
		char error[errorLength];
		sprintf(error, "getaddrinfo: %s\n", gai_strerror(rv));
		log_error(logger, "error");
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
