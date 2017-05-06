// Estructura para el PCB
typedef struct __attribute__((packed))t_pcb{
	int pid;
	//int paginasDeMemoria;
	unsigned int pc;
	unsigned int paginasDeCodigo;
	int *indiceDeCodigo;
	char *indiceDeEtiquetas;
	int *indiceDelStack;
	int exitCode;
	//t_size      instrucciones_size;           // Cantidad de instrucciones
	//t_intructions* instrucciones_serializado; // Instrucciones del programa
}t_pcb;
