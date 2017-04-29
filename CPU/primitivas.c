#include "parser/parser.h"

t_puntero definirVariable(t_nombre_variable identificador_variable){
	// Reserva en el Contexto de Ejecución Actual el espacio necesario
	// para una variable llamada identificador_variable y la registra tanto en el Stack
	// como en el Diccionario de Variables. Retornando la posición del valor de esta nueva variable del stack
	printf("definiendo variable %c\n",identificador_variable);
}
t_puntero obtenerPosicionVariable (t_nombre_variable identificador_variable){
	// Devuelve el desplazamiento respecto al inicio del segmento Stack
	// en que se encuentra el valor de la variable identificador_variable del contexto actual.
	// En caso de error, retorna -1.
	printf("obtenieindo posicion variable %c\n",identificador_variable);
}
t_valor_variable dereferenciar(t_puntero direccion_variable){
	// Obtiene el valor resultante de leer a partir de direccion_variable
	// sin importar cual fuera el contexto actual
	printf("dereferenciando direccion de variable\n");
}
void asignar(t_puntero direccion_variable,t_valor_variable valor){
	// Inserta una copia del valor en la variable ubicada en direccion_variable.
	printf("asignando valor %i a la variable %c\n",valor,direccion_variable);
}
t_valor_variable obtenerValorCompartida(t_nombre_compartida variable){
	// Pide al kernel el valor (copia, no puntero) de la variable compartida por parametro.
	printf("obteniendo valor\n");
}
t_valor_variable asignarValorCompartida(t_nombre_compartida variable,t_valor_variable valor){
	// Pide al kernel asignar el valor a la variable compartida.
	 // Devuelve el valor asignado.
	printf("asignando valor\n");
}
void irAlLabel(t_nombre_etiqueta etiqueta){
	// Cambia la linea de ejecucion a la correspondiente de la etiqueta buscada.
	printf("yendo al label\n");
}
//t_puntero_instruccion llamarFuncion(t_nombre_etiqueta etiqueta,t_puntero donde_retornar,t_puntero_instruccion linea_en_ejecucion){
//	printf("llamando a la funcion\n");
//}
void llamarSinRetorno(t_nombre_etiqueta etiqueta){
	// Preserva el contexto de ejecución actual para poder retornar luego al mismo.
	// Modifica las estructuras correspondientes para mostrar un nuevo contexto vacío.
	// Los parámetros serán definidos luego de esta instrucción de la misma manera que una variable local,
	// con identificadores numéricos empezando por el 0.
	printf("llamando sin retorno\n");
}
void llamarConRetorno(t_nombre_etiqueta etiqueta, t_puntero donde_retornar){
	// Preserva el contexto de ejecución actual para poder retornar luego al mismo,
	// junto con la posicion de la variable entregada por donde_retornar.
	// Modifica las estructuras correspondientes para mostrar un nuevo contexto vacío.
	// Los parámetros serán definidos luego de esta instrucción de la misma manera que una variable local,
	// con identificadores numéricos empezando por el 0.
	printf("llamando con retorno\n");
}
void finalizar(void){
	// Cambia el Contexto de Ejecución Actual para volver al Contexto anterior al que se está ejecutando,
	// recuperando el Cursor de Contexto Actual y el Program Counter previamente apilados en el Stack.
	// En caso de estar finalizando el Contexto principal (el ubicado al inicio del Stack),
	// deberá finalizar la ejecución del programa.
	printf("finalizando...\n");
}
void retornar(t_valor_variable retorno){
	// Cambia el Contexto de Ejecución Actual para volver al Contexto anterior al que se está ejecutando,
	// recuperando el Cursor de Contexto Actual, el Program Counter y la direccion donde retornar,
	// asignando el valor de retorno en esta, previamente apilados en el Stack.
	printf("retornando...\n");
}
//void imprimir(t_valor_variable valor_mostrar){
//	printf("imprimiendo...\n");
//}
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
