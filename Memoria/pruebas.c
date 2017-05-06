/*
 * pruebas.c
 *
 *  Created on: 02/05/2017
 *      Author: epreyes
 */

#include "memoria_core.h"
#include "pruebas.h"

void pruebas(t_log* logger, int marcosTablaPagina) {

	// Prueba de asignacion de marcos a procesos

	log_info(logger, "----------------------------------");
	log_info(logger, "INICIO DE PRUEBAS");
	log_info(logger, "----------------------------------");

	log_info(logger, "Asignando paginas a procesos");

	int me = asignarPaginaAProceso(1, 1);
	me = asignarPaginaAProceso(2, 1);

	if (me == 0)
		log_info(logger, "Asignacion ok");
	else
		log_info(logger, "Error: %d", me);

	listarTablaPaginas();

	// Prueba de escritura en marcos

	int resEscribir = escribirMemoria(1, 0, 0, "Esteban", 7);
	resEscribir = escribirMemoria(2, 1, 0, "Paz", 3);

	switch (resEscribir) {
	case MARCO_DEMASIADO_CHICO:
		log_error(logger, "Marco demasiado chico para el buffer recibido");
		break;
	case MARCO_INVALIDO:
		log_error(logger, "Marco invalido");
		break;
	}

	// Prueba de lectura de marcos

	char* test = malloc(TAMANIO_MARCO);
	int d = leerMemoria(1, 0, 0, test);

	if (d == 0)
		log_info(logger, "Prueba lectura: %s", test);
	else
		log_error(logger, "error: %d", d);

	free(test);

	test = malloc(TAMANIO_MARCO);

	log_info(logger, "2do test");

	d = leerMemoria(2, 1, 0, test);

	if (d == 0)
		log_info(logger, "Prueba lectura: %s", test);
	else
		log_error(logger, "error: %d", d);

	free(test);

	// Prueba de dump de memoria

	log_info(logger, "Dump de memoria completo");

	int j = 0;

	bloqueMemoria* p = getComienzoMemoria();

	for (j = 0; j < CANTIDAD_MARCOS - marcosTablaPagina; j++) {
		char* t = malloc(TAMANIO_MARCO);
		memcpy(t, p, 13);
		t_mem* m = buscarPaginaPorMarco(j);
		if (m != NULL) {
			log_info(logger, "pid: %d - marco %d - pagina %d: %s", m->idProceso,
					j, m->pagina, t);
			free(t);
		}
		p++;
	}

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

	j = 0;

	p = getComienzoMemoria();

	for (j = 0; j < CANTIDAD_MARCOS - marcosTablaPagina; j++) {
		char* t = malloc(TAMANIO_MARCO);
		memcpy(t, p, 13);
		t_mem* m = buscarPaginaPorMarco(j);
		if (m != NULL) {
			log_info(logger, "pid: %d - marco %d - pagina %d: %s", m->idProceso,
					j, m->pagina, t);
			free(t);
			//free(m);

		}
		p++;
	}

	log_info(logger, "----------------------------------");
	log_info(logger, "FIN DE PRUEBAS");
	log_info(logger, "----------------------------------");

}
