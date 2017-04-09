//
// Created by Martin Gauna on 4/2/17.
//
/*
 * #!/usr/bin/ansisop
 begin
 variables a, b
 a = 3
 b = 5
 a = b + 12
 end
 */
#include "cpu.h"
#include "primitivas.h"
#include <parser/parser.h>

AnSISOP_funciones primitivas = {
		.AnSISOP_definirVariable		= definirVariable,
		.AnSISOP_obtenerPosicionVariable= obtenerPosicionVariable,
		.AnSISOP_dereferenciar			= dereferenciar,
		.AnSISOP_asignar				= asignar,
		.AnSISOP_obtenerValorCompartida = obtenerValorCompartida,
		.AnSISOP_asignarValorCompartida = asignarValorCompartida,
		.AnSISOP_irAlLabel				= irAlLabel,
		.AnSISOP_llamarConRetorno		= llamarConRetorno,
		.AnSISOP_retornar				= retornar,
		//.AnSISOP_imprimir				= imprimir,
		//.AnSISOP_imprimirTexto			= imprimirTexto,
		//.AnSISOP_entradaSalida			= entradaSalida,
		.AnSISOP_finalizar				= finalizar,

};
AnSISOP_kernel primitivas_kernel = {
		.AnSISOP_wait					=wait_kernel,
		.AnSISOP_signal					=signal_kernel,
		.AnSISOP_reservar				=reservar_kernel,
		.AnSISOP_liberar				=liberar_kernel,
		.AnSISOP_abrir					=abrir_kernel,
		.AnSISOP_borrar					=borrar_kernel,
		.AnSISOP_cerrar					=cerrar_kernel,
		.AnSISOP_moverCursor			=moverCursor_kernel,
		.AnSISOP_escribir				=escribir_kernel,
		.AnSISOP_leer					=leer_kernel
};

int main(int argc, char **argv) {

char* sentencia = 'variables a, b';

analizadorLinea(depurarSentencia(sentencia), &primitivas,&primitivas_kernel);

char* depurarSentencia(char* sentencia) {

	int i = strlen(sentencia);
	while (string_ends_with(sentencia, "\n")) {
		i--;
		sentencia = string_substring_until(sentencia, i);
	}
	return sentencia;
}
