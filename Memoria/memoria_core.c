/*
 ============================================================================
 Name        : memoria_core.c
 Author      : epreyes
 Version     :
 Copyright   :
 Description : Funciones core de la memoria
 ============================================================================
 */

#include "memoria_core.h"

t_mem_server* config;

// Retorna la cantidad de marcos que ocupa las estructuras administrativas
int obtenerMarcosTablaPaginas() {
	return sizeof(t_mem) * CANTIDAD_MARCOS / TAMANIO_MARCO;
}

// Retorna la cantidad de marcos de memoria fisica disponible al usuario
int obtenerMarcosMemoriaFisica() {
	return CANTIDAD_MARCOS - obtenerMarcosTablaPaginas();
}

// Arma la tabla de paginas y la coloca en la memoria
void generarTablaPaginas() {
	int i = 0;

	t_list* tabla = obtenerTablaPaginas();
	tabla = list_create();

	for (i = 0; i < obtenerMarcosMemoriaFisica(); i++) {
		t_mem* reg1 = malloc(sizeof(t_mem));
		reg1->idProceso = -1; // -1 indica que esta libre
		reg1->marco = i;
		reg1->pagina = -1; // indica que esta libre
		list_add(tabla, reg1);

	}

	memcpy(memoria, tabla, CANTIDAD_MARCOS * 12);

	// libero la estructura auxiliar (ya que tengo todo en memoria)
	free(tabla);

}

// Busca un frame libre y lo asigna al proceso
int asignarPaginaAProceso(int pid, int cantPaginasRequeridas) {
	int i = 0;
	int j = 0;
	int libre = 0;

	t_list* tabla = obtenerTablaPaginas();

	for (j = 0; j < cantPaginasRequeridas; j++) {
		for (i = 0 + libre; i < CANTIDAD_MARCOS; i++) {
			t_mem* m = (t_mem*) list_get(tabla, i);

			// El marco esta libre
			if (m != NULL && m->idProceso == -1) {
				libre++;
				break;
			}

		}
	}

	if (libre < cantPaginasRequeridas)
		return MARCOS_INSUFICIENTES;

	// Asigno

	i = 0;
	j = 0;
	libre = 0;

	for (j = 0; j < cantPaginasRequeridas; j++) {
		for (i = 0 + libre; i < CANTIDAD_MARCOS; i++) {
			t_mem* m = (t_mem*) list_get(tabla, i);

			// El marco esta libre
			if (m != NULL && m->idProceso == -1) {
				m->idProceso = pid;
				m->pagina = i;
				break;
			}

		}
	}

	return 0;
}

void listarTablaPaginas() {
	int i = 0;

	t_list* tabla = obtenerTablaPaginas();

	for (i = 0; i < CANTIDAD_MARCOS; i++) {

		t_mem* m = (t_mem*) list_get(tabla, i);
		if (m != NULL)
			printf("pagina: %d - pid: %d - marco: %d\n", m->pagina,
					m->idProceso, m->marco);

	}

}

// Dado un processId, pagina, offset y buffer escribe el mismo en el marco asociado
int escribirMemoria(int processId, int pagina, int offset, char* buffer,
		int tamanio) {

	int marco = -1;

	marco = traducirADireccionFisica(pagina, processId);

	if (marco == -1)
		return MARCO_INVALIDO;

	// TODO: ver si esta validacion es correcta
	if (tamanio > TAMANIO_MARCO)
		return MARCO_DEMASIADO_CHICO;

	// me ubico en el comienzo del espacio de usuario (despues de los N bloques administrativos)
	bloqueMemoria* p = getComienzoMemoria();

	// me ubico en el marco pedido
	p += marco;

	log_info(logger,
			"Escribiendo el buffer en memoria de pid: %d - Pagina: %d - offset: %d",
			processId, pagina, offset);

	memcpy(p + offset, buffer, tamanio);

	return 0;

}

// Dado un processId, pagina y offset lee el contenido del marco asociado y lo retorna en res
int leerMemoria(int processId, int pagina, int offset, char* res) {

	int marco = -1;

	marco = traducirADireccionFisica(pagina, processId);

	if (marco == -1)
		return MARCO_INVALIDO;

	// me ubico en el comienzo del espacio de usuario (despues de los N bloques administrativos)
	bloqueMemoria* p = getComienzoMemoria();

	// me ubico en el marco pedido (indice en la tabla de paginas)
	p += marco;

	log_info(logger, "Leyendo memoria de pid: %d - Pagina: %d - offset: %d",
			processId, pagina, offset);

	memcpy(res, p, TAMANIO_MARCO);

	return 0;

}

// Traduce una direccion virtual a fisica.
// TODO: debe usar una funcion de hash para la busqueda
int traducirADireccionFisica(int pagina, int processId) {

	log_info(logger,
			"Traduciendo direccion virtual a fisica de pid: %d - Pagina: %d ",
			processId, pagina);

	t_list* tabla = obtenerTablaPaginas();

	int i;
	for (i = 0; i < CANTIDAD_MARCOS; i++) {
		t_mem* p2 = (t_mem*) list_get(tabla, i);
		if (p2 != NULL)
			if (p2->pagina == pagina && p2->idProceso == processId) {
				log_info(logger, "Marco obtenido de id: %d", p2->marco);
				return i;
			}

	}

	return -1;
}

t_mem* buscarPaginaPorMarco(int marco) {
	int i = 0;

	t_list* tabla = obtenerTablaPaginas();

	for (i = 0; i < CANTIDAD_MARCOS; i++) {

		t_mem* m = (t_mem*) list_get(tabla, i);
		if (m != NULL)
			if (m->marco == marco)
				return m;

	}

	return NULL;

}

// Libera la memoria asignada a un proceso de la tabla de paginas
// Nota: no modifica el char*
int liberarProcesoMemoria(int processId) {

	t_list* tabla = obtenerTablaPaginas();

	int i = 0;
	for (i = 0; i < CANTIDAD_MARCOS; i++) {
		t_mem* reg = (t_mem*) list_get(tabla, i);

		if (reg != NULL)
			if (reg->idProceso == processId) {
				reg->idProceso = -1; // -1 indica que esta libre
				reg->pagina = -1; // indica que esta libre
			}

	}
	return -1;

}

// Libera la memoria completamente
void liberarMemoria() {

	free(memoria);
}

// Devuelve un puntero al comienzo de la memoria de usuario
bloqueMemoria* getComienzoMemoria() {
	bloqueMemoria* p = (bloqueMemoria*) memoria;
	p += marcosTablaPagina;
	return p;
}

// Devuelve la tabla de paginas de la memoria
t_list* obtenerTablaPaginas() {
	bloqueMemoria* p = (bloqueMemoria*) memoria;
	return (t_list*) p;
}

// Funcion de inicializacion de memoria
void memoriaInit(t_mem_server* config) {

	log_info(logger, "Inicializando memoria...");

	memoria = malloc(TAMANIO_MARCO * CANTIDAD_MARCOS);

	// Para mejor visualizacion
	memset(memoria, '-', TAMANIO_MARCO * CANTIDAD_MARCOS);

	if (CANTIDAD_MARCOS * TAMANIO_MARCO - CANTIDAD_MARCOS * 12 < 0) {
		log_error(logger, "Error de configuracion");
		exit(1);
	}

	marcosTablaPagina = obtenerMarcosTablaPaginas();

	log_info(logger, "marcos: %d - tamanio: %d bytes", CANTIDAD_MARCOS,
	TAMANIO_MARCO);
	log_info(logger,
			"Tamaño tabla de paginas: %d (marcos) - Memoria fisica disponible: %d (marcos) - %d (bytes)",
			marcosTablaPagina, obtenerMarcosMemoriaFisica(),
			obtenerMarcosMemoriaFisica() * TAMANIO_MARCO);

	generarTablaPaginas();

	log_info(logger, "Memoria inicializada correctamente");

}

