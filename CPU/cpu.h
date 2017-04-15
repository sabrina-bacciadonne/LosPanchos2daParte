#ifndef TP_2017_1C_LOSPANCHOS_CPU_H
#define TP_2017_1C_LOSPANCHOS_CPU_H

#include "../Commons/configuracion.h"
#include "../Commons/socket.h"
#include <commons/log.h>
#include <commons/config.h>
#include <sys/types.h>

typedef u_int32_t t_puntero;
typedef u_int32_t t_size;
typedef t_puntero t_puntero_instruccion;
typedef t_puntero t_descriptor_archivo;

typedef char t_nombre_variable;
typedef int t_valor_variable;

typedef t_nombre_variable* t_nombre_semaforo;
typedef t_nombre_variable* t_nombre_etiqueta;
typedef  t_nombre_variable* t_nombre_compartida;
typedef  t_nombre_variable* t_direccion_archivo;

char* depurarSentencia(char* sentencia);

#endif //TP_2017_1C_LOSPANCHOS_CPU_H


