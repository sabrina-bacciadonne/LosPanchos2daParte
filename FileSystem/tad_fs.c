/*
 * tad_fs.c
 *
 *  Created on: 21/4/2017
 *      Author: utnso
 */

#include "tad_fs.h"
#include <ctype.h>

void consola_reconocerComando() {

	int opcion = toupper(getchar());

	while (opcion < INIT_PROGRAM || opcion > CLEAN) {
		puts("Error");
		opcion = toupper(getchar());
	}

	switch (opcion) {
	case INIT_PROGRAM:
		break;
	case FIN_PROGRAM:
		break;
	case DISCONNECT:
		break;
	case CLEAN:
		system("clear");
		break;
	}

}
