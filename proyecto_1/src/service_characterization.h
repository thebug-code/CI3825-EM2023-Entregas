#ifndef __charac_svc_H__
#define __charac_svc_H__

#include "bus_departure_time_list.h"

typedef struct service_characterization {
    char *route; /* Nombre de la ruta */
    bus_dep_time_node *scheds; /* Lista con horarios de salida de los buses */
} svc_charac;


/*
 * Crea una structura de caracterizacion de servicio
 *
 * @param route: puntero a char con el nombre de la ruta
 * @return Un apuntador a svc_charac si la creacion fue exitosa.
 *         Null en caso contrario.
 */
svc_charac* new_svc_charac(char *route);

#endif
