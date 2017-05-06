#include "configuracion.h"

void* cargarConfiguracion(char* path,int configParamAmount,processType configType, t_log* logger){
	t_config* configFile;
	configConsole* confConsola;
	configCPU* confCPU;
	configFileSystem* confFileSystem;
	configKernel* confKernel;
	configMemoria* confMemoria;

	configFile = config_create(path);
	if (!configFile || configFile->properties->elements_amount == 0) {
		log_error(logger, "No se encontro el archivo de configuracion.\n");
		config_destroy(configFile);
		exit(EXIT_FAILURE);
	}

	if (config_keys_amount(configFile) != configParamAmount) {
		log_error(logger, "No se encuentran inicializados todos los parametros de configuracion requeridos.");
		config_destroy(configFile);
		exit(EXIT_FAILURE);
	}

	switch(configType){
	case CONSOLA:
		confConsola = (configConsole*) malloc(sizeof(configConsole));
		confConsola->puerto = leerPuerto(configFile, "PUERTO_KERNEL", logger);
		confConsola->ip = leerIP(configFile, "IP_KERNEL", logger);
		config_destroy(configFile);
		return confConsola;
	case CPU:
		confCPU = (configCPU*)malloc(sizeof(configCPU));
		confCPU->puertoKernel = leerPuerto(configFile, "PUERTO_KERNEL", logger);
		confCPU->ipKernel = leerIP(configFile, "IP_KERNEL", logger);
		confCPU->puertoMemoria = leerPuerto(configFile, "PUERTO_MEMORIA", logger);
		confCPU->ipMemoria = leerIP(configFile, "IP_MEMORIA", logger);
		config_destroy(configFile);
		return confCPU;
	case FILESYSTEM:
		confFileSystem = (configFileSystem*)malloc(sizeof(configFileSystem));
		confFileSystem->puerto = leerPuerto(configFile, "PUERTO", logger);
		confFileSystem->puntoMontaje = leerString(configFile, "PUNTO_MONTAJE", logger);
		config_destroy(configFile);
		return confFileSystem;
	case KERNEL:
		confKernel = (configKernel*)malloc(sizeof(configKernel));
		confKernel->puerto_prog = leerPuerto(configFile, "PUERTO_PROG", logger);
		confKernel->puertoCPU = leerPuerto(configFile, "PUERTO_CPU", logger);
		confKernel->ipMemoria = leerIP(configFile, "IP_MEMORIA", logger);
		confKernel->puertoMemoria = leerPuerto(configFile, "PUERTO_MEMORIA", logger);
		confKernel->ipFS = leerIP(configFile, "IP_FS", logger);
		confKernel->puertoFS = leerPuerto(configFile, "PUERTO_FS", logger);
		confKernel->quantum = leerInt(configFile, "QUANTUM", logger);
		confKernel->quantumSleep = leerInt(configFile, "QUANTUM_SLEEP", logger);
		confKernel-> algoritmo = leerString(configFile, "ALGORITMO", logger);
		confKernel->gradoMultiprog = leerInt(configFile, "GRADO_MULTIPROG", logger);
		confKernel->semIds = leerString(configFile, "SEM_IDS", logger);
		confKernel->semInits = leerString(configFile, "SEM_INIT", logger);
		confKernel->sharedVars = leerString(configFile, "SHARED_VARS", logger);
		confKernel->stackSize = leerInt(configFile, "STACK_SIZE", logger);
		config_destroy(configFile);
		return confKernel;
	case MEMORIA:
		confMemoria = (configMemoria*)malloc(sizeof(configMemoria));
		confMemoria->puerto = leerPuerto(configFile, "PUERTO", logger);
		confMemoria->marcos = leerInt(configFile, "MARCOS", logger);
		confMemoria->marcoSize = leerInt(configFile, "MARCO_SIZE", logger);
		confMemoria->entradasCache =  leerInt(configFile, "ENTRADAS_CACHE", logger);
		confMemoria->cacheXProc =  leerInt(configFile, "CACHE_X_PROC", logger);
		confMemoria->retardoMemoria =  leerInt(configFile, "RETARDO_MEMORIA", logger);
		config_destroy(configFile);
		return confMemoria;
	default:
			config_destroy(configFile);
			return NULL;
	}


}

char* leerString (void* configFile, char* parametro, t_log* logger){
	char* string = "";
	if (config_has_property(configFile, parametro)) {
		string = config_get_string_value(configFile, parametro);
		//TODO: Valida que no sea vacio
	} else {
		log_error(logger, "No se encuentra el parametro en el archivo de config.");//TODO generar el string correcto para el error
		exit(EXIT_FAILURE);

	}
	return string;
}

int leerInt (void* configFile, char* parametro, t_log* logger){
	int valor = 0;
	if (config_has_property(configFile, parametro)) {
		valor = config_get_int_value(configFile, parametro);
	} else {
		log_error(logger, "No se encuentra el parametro en el archivo de configuracion.");//TODO GENERAR UN BUEN TEXTO PARA EL LOG
		exit(EXIT_FAILURE);
	}
	return valor;
}

int leerPuerto (void* configFile, char* parametro, t_log* logger){
	int puerto = 0;
	puerto = leerInt(configFile, parametro, logger);
	validar_puerto(puerto, logger);
	return puerto;
}

char* leerIP (void* configFile, char* parametro, t_log* logger){
	char* ip = "";
	ip = leerString (configFile, parametro,logger);
	return ip;
}

void validar_puerto(int puerto, t_log* logger){
	if (puerto < PUERTO_MAX) {
		log_error(logger, "El numero de puerto indicado se encuentra reservado para el sistema.");
		exit(EXIT_FAILURE);
	}
	return;
}





