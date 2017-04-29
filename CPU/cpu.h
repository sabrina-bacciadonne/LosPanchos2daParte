#ifndef TP_2017_1C_LOSPANCHOS_CPU_H
#define TP_2017_1C_LOSPANCHOS_CPU_H

#include "../Commons/configuracion.h"
#include "../Commons/socket.h"
#include <commons/log.h>
#include <commons/config.h>
#include <sys/types.h>
#include "primitivas.h"

int socketMemoria;
int socketKernel;
t_log* logger;

char* depurarSentencia(char* sentencia);

#endif //TP_2017_1C_LOSPANCHOS_CPU_H


