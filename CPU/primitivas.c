t_puntero definirVariable(t_nombre_variable identificador_variable){
	printf("definiendo variable %c",identificador_variable);
}

t_puntero obtenerPosicionVariable (t_nombre_variable identificador_variable){
	printf("obtenieindo posicion variable %c",identificador_variable);
}

t_valor_variable dereferenciar(t_puntero direccion_variable){
	printf("dereferenciando direccion de variable");
}

void asignar(t_puntero direccion_variable,t_valor_variable valor){
	printf("asignando valor %i a la variable %c",valor,direccion_variable);
}
t_valor_variable obtenerValorCompartida(t_nombre_compartida variable){
	printf("");
}
t_valor_variable asignarValorCompartida(t_nombre_compartida variable,t_valor_variable valor){
	printf("");
}
void irAlLabel(t_nombre_etiqueta etiqueta){
	printf("");
}
//t_puntero_instruccion llamarFuncion(t_nombre_etiqueta etiqueta,t_puntero donde_retornar,t_puntero_instruccion linea_en_ejecucion){
	printf("");
}
void llamarSinRetorno(t_nombre_etiqueta etiqueta){
	printf("");
}
void llamarConRetorno(t_nombre_etiqueta etiqueta, t_puntero donde_retornar){
	printf("");
}
void finalizar(void){
	printf("");
}
void retornar(t_valor_variable retorno){
	printf("");
}
//void imprimir(t_valor_variable valor_mostrar){
	printf("");
}
//void imprimirTexto(char*texto)printf(""); no estaban en el parser.{
	h
}
//void entradaSalida(t_nombre_dispositivo dispositivo,int tiempo)printf(""); no reconoce t_nombre_dispositiv{
	o
}
void finalizar(){
	printf("finalizo el programa");
}
void wait_kernel(t_nombre_semaforo identificador_semaforo){
	printf("");
}
void signal_kernel(t_nombre_semaforo identificador_semaforo){
	printf("");
}
t_puntero reservar_kernel(t_valor_variable espacio){
	printf("");
}
void liberar_kernel(t_puntero puntero){
	printf("");
}
t_descriptor_archivo abrir_kernel(t_direccion_archivo direccion, t_banderas flags){
	printf("");
}
void borrar_kernel(t_descriptor_archivo direccion){
	printf("");
}
void cerrar_kernel(t_descriptor_archivo descriptor_archivo){
	printf("");
}
void moverCursor_kernel(t_descriptor_archivo descriptor_archivo, t_valor_variable posicion){
	printf("");
}
void escribir_kernel(t_descriptor_archivo descriptor_archivo, void* informacion, t_valor_variable tamanio){
	printf("");
}
void leer_kernel(t_descriptor_archivo descriptor_archivo, t_puntero informacion, t_valor_variable tamanio){
	printf("");
}
