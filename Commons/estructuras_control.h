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
}t_pcb;
