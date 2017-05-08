/*
 * pruebas.c
 *
 *  Created on: 02/05/2017
 *      Author: epreyes
 */

#include "memoria_core.h"
#include "pruebas.h"

void pruebas(t_log* logger, int marcosTablaPagina, t_mem_server* config) {

	// Prueba de asignacion de marcos a procesos

	log_info(logger, "----------------------------------");
	log_info(logger, "INICIO DE PRUEBAS");
	log_info(logger, "----------------------------------");

	log_info(logger, "Asignando 1 pagina a procesos 1, 2, 3 y 4 ");

	int me = asignarPaginaAProceso(1, 1);
	me = asignarPaginaAProceso(2, 3);
	me = asignarPaginaAProceso(3, 3);
	me = asignarPaginaAProceso(4, 1);

	listarTablaPaginas();

	// Prueba de escritura en marcos

	int resEscribir = escribirMemoria(1, 1, 0, "Programa1", 9);
	resEscribir = escribirMemoria(2, 1, 0, "Programa2", 9);
	resEscribir = escribirMemoria(3, 1, 0, "Programa3", 9);

	switch (resEscribir) {
	case MARCO_DEMASIADO_CHICO:
		log_error(logger, "Marco demasiado chico para el buffer recibido");
		break;
	case MARCO_INVALIDO:
		log_error(logger, "Marco invalido");
		break;
	}


	// Prueba de lectura de marcos

	char* test = malloc(config->marcos_size);
	int d = leerMemoria(1, 1, 0, test);

	if (d == 0)
		log_info(logger, "Prueba lectura: %s", test);
	else
		log_error(logger, "error: %d", d);

	free(test);

	test = malloc(config->marcos_size);

	log_info(logger, "2do test");

	d = leerMemoria(2, 1, 0, test);

	if (d == 0)
		log_info(logger, "Prueba lectura: %s", test);
	else
		log_error(logger, "error: %d", d);

	free(test);

	// Prueba de dump de memoria

	log_info(logger, "Dump de memoria completo");

	printDump(config);

	// Prueba de liberacion de marcos de procesos (finalizacion)

	log_debug(logger, "Liberando memoria para el processId 1");
	int f = liberarProcesoMemoria(1);

	log_debug(logger, "Liberando memoria para el processId 2");
	f = liberarProcesoMemoria(2);

	log_debug(logger, "Liberando memoria para el processId 2");
	f = liberarProcesoMemoria(2);
	if (f != 0)
		log_error(logger, "Error liberando memoria para pid 2");

	log_debug(logger, "Liberando memoria para el processId 3");
	f = liberarProcesoMemoria(3);
	if (f != 0)
		log_error(logger, "Error liberando memoria para pid 3");

	log_info(logger, "Dump de memoria completo");

	printDump(config);

	log_info(logger, "----------------------------------");
	log_info(logger, "FIN DE PRUEBAS");
	log_info(logger, "----------------------------------");

}

void printDump(t_mem_server* config) {
	int j = 0;

	char* p = getComienzoMemoria();


	for (j = 0; j < config->marcos; j++) {
		char* t = malloc(config->marcos_size);
		memcpy(t, p, config->marcos_size);
		t_mem* m = buscarPaginaPorMarco(j);
		if (m != NULL) {
			if (m->idProceso != -1)
				log_info(logger, "pid: %d - marco %d - pagina %d: %s",
						m->idProceso, j, m->pagina, t);
			else
				log_info(logger, "pid: -1 - marco %d - pagina %d: ADMIN", j,
						m->pagina);

			free(t);

		}

		p+=config->marcos_size;
	}
}
