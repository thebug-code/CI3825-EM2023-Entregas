#ifndef __service_H__
#define __service_H__

#include "schedule_list.h"

/**
 * Estructura de servicios (rutas y horarios asociados) 
 * del transporte USB
 */

typedef struct Service {
    char *route; /* Nombre de la ruta */
    sched_node *scheds; /* Lista con horarios asociados a la ruta */
} svc;

svc* new_svc(char *route);

#endif
