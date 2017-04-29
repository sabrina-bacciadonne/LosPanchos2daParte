#include "parser/parser.h"
#include "cpu.h"

t_puntero definirVariable(t_nombre_variable identificador_variable){
	printf("definiendo variable %c\n",identificador_variable);
}
t_puntero obtenerPosicionVariable (t_nombre_variable identificador_variable){
	printf("obtenieindo posicion variable %c\n",identificador_variable);
}
t_valor_variable dereferenciar(t_puntero direccion_variable){
	printf("dereferenciando direccion de variable\n");
}
void asignar(t_puntero direccion_variable,t_valor_variable valor){
	printf("asignando valor %i a la variable %c\n",valor,direccion_variable);
}
t_valor_variable obtenerValorCompartida(t_nombre_compartida variable){
	printf("obteniendo valor\n");
}
t_valor_variable asignarValorCompartida(t_nombre_compartida variable,t_valor_variable valor){
	printf("asignando valor\n");
}
void irAlLabel(t_nombre_etiqueta etiqueta){
	printf("yendo al label\n");
}
//t_puntero_instruccion llamarFuncion(t_nombre_etiqueta etiqueta,t_puntero donde_retornar,t_puntero_instruccion linea_en_ejecucion){
//	printf("llamando a la funcion\n");
//}
void llamarSinRetorno(t_nombre_etiqueta etiqueta){
	printf("llamando sin retorno\n");
}
void llamarConRetorno(t_nombre_etiqueta etiqueta, t_puntero donde_retornar){
	printf("llamando con retorno\n");
}
void finalizar(void){
	printf("finalizando...\n");
}
void retornar(t_valor_variable retorno){
	printf("retornando...\n");
}
void imprimir(t_valor_variable valor_mostrar){
	printf("imprimiendo...\n");
}
//void imprimirTexto(char*texto){
//	printf("imprimiendo...\n");
//}
//void entradaSalida(t_nombre_dispositivo dispositivo,int tiempo){
//	printf("imprimiendo...\n");
//}
void wait_kernel(t_nombre_semaforo identificador_semaforo){
	printf("wait_kernel\n");
}
void signal_kernel(t_nombre_semaforo identificador_semaforo){
	printf("signal_kernel\n");
}
t_puntero reservar_kernel(t_valor_variable espacio){
	printf("reservar_kernel\n");
}
void liberar_kernel(t_puntero puntero){
	printf("liberar_kernel\n");
}
//t_descriptor_archivo abrir_kernel(t_direccion_archivo direccion, t_banderas flags){
//	printf("abrir_kernel\n");
//}
void borrar_kernel(t_descriptor_archivo direccion){
	printf("borrar_kernel\n");
}
void cerrar_kernel(t_descriptor_archivo descriptor_archivo){
	printf("cerrar_kernel\n");
}
void moverCursor_kernel(t_descriptor_archivo descriptor_archivo, t_valor_variable posicion){
	printf("moverCursor_kernel\n");
}
void escribir_kernel(t_descriptor_archivo descriptor_archivo, void* informacion, t_valor_variable tamanio){
	printf("escribir_kernel\n");
}
void leer_kernel(t_descriptor_archivo descriptor_archivo, t_puntero informacion, t_valor_variable tamanio){
	printf("leer_kernel\n");
}
