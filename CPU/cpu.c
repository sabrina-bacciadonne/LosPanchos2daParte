/*
 #!/usr/bin/ansisop
 begin
 variables a, b
 a = 3
 b = 5
 a = b + 12
 end
 */
#include "cpu.h"
#include "parser/parser.h"

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
		.AnSISOP_finalizar				= finalizar

};
AnSISOP_kernel primitivas_kernel = {
		.AnSISOP_wait					=wait_kernel,
		.AnSISOP_signal					=signal_kernel,
		.AnSISOP_reservar				=reservar_kernel,
		.AnSISOP_liberar				=liberar_kernel,
//		.AnSISOP_abrir					=abrir_kernel,
		.AnSISOP_borrar					=borrar_kernel,
		.AnSISOP_cerrar					=cerrar_kernel,
		.AnSISOP_moverCursor			=moverCursor_kernel,
		.AnSISOP_escribir				=escribir_kernel,
		.AnSISOP_leer					=leer_kernel
};

int main (int argc, char *argv[]) {
	t_log* logger = log_create("log_kernel", "CPU", 1, LOG_LEVEL_TRACE);
	configCPU* conf = (configCPU*) cargarConfiguracion("./config", 4, CPU, logger);
	int socketKernel;
	t_package pkg;

	puts("CPU.");
	printf("IP_KERNEL: %s\n",conf->ipKernel);
	printf("IP_MEMORIA: %s\n",conf->ipMemoria);
	printf("PUERTO_KERNEL: %d\n",conf->puertoKernel);
	printf("PUERTO_MEMORIA %d\n",conf->puertoMemoria);

/*
	if(cargarSoket(conf->puertoKernel, conf->ipKernel, &socketKernel, logger)){
		//ERROR
	}
	if(enviarHandshake(socketKernel, CPU_HSK, KERNEL_HSK,logger)){
		//ERROR
	}
	log_debug(logger, "Conectado al Kernel");
*/
	if(cargarSoket(conf->puertoMemoria, conf->ipMemoria, &socketMemoria, logger)){
		//ERROR
		return EXIT_FAILURE;
	}
	if(enviarHandshake(socketMemoria, CPU_HSK, MEMORIA_HSK,logger)){
		//ERROR
		return EXIT_FAILURE;
	}
	log_debug(logger, "Conectado a la Memoria");

//	while(1){
//		printf("Esperando mensaje del Kernel.\n");
//		if(recibir(socketKernel, &pkg, logger)){
//			//ERROR
//			close(socketKernel);
//			return EXIT_FAILURE;
//		}
//		printf("Mensaje recibido del kernels: %s\n",pkg.data);
//		free(pkg.data);
//	}

/*PARSER*/printf("-- INICIO PARSER --\n");
	char* sentencia = "variables a, b\n";
	analizadorLinea(depurarSentencia(sentencia), &primitivas,&primitivas_kernel);
/*PARSER*/printf("-- FIN PARSER --\n");

	free(logger);
	free(conf);
	return EXIT_SUCCESS;
}

char* depurarSentencia(char* sentencia) {

	int i = strlen(sentencia);
	while (string_ends_with(sentencia, "\n")) {
		i--;
		sentencia = string_substring_until(sentencia, i);
	}
	return sentencia;
}
