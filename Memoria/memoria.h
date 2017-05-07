//
// Created by Martin Gauna on 4/2/17.
//

#ifndef TP_2017_1C_LOSPANCHOS_MEMORIA_H
#define TP_2017_1C_LOSPANCHOS_MEMORIA_H

<<<<<<< HEAD
#include "../Commons/configuracion.h"
#include "../Commons/socket.h"
#include "../Commons/console.h"
#include "../Commons/commons.h"
#include <commons/log.h>
#include <commons/config.h>

void consolaMem_imprimir_encabezado();
void consolaMem_imprimir_menu();
int validar_archivo_configMemoria(configMemoria* datos_config,t_log* logger);
void liberar_memoria(t_log* logger,configMemoria* config);
void sleepAccesoMemoria();
void inicializarMemoria(t_log* logger,configMemoria* datos_config);
int inicializar_Conexion(t_log* logger,configMemoria* datos_config);

=======
#include <commons/log.h>
#include <commons/config.h>

#include <utilstp/console.h>
#include <utilstp/configuracion.h>
#include <utilstp/socket.h>
>>>>>>> c49313cbeb1c79b71a61b3dd2940b5f506e89398

#endif //TP_2017_1C_LOSPANCHOS_MEMORIA_H






