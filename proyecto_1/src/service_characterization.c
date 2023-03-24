/*
 * Implementacion de las funciones de la estructura de caracterizacion
 * de servicio.
 */
#include <stdlib.h>

#include "service_characterization.h"


/*
 * Crea una structura de caracterizacion de servicio
 *
 * @param route: puntero a char con el nombre de la ruta
 * @return Un apuntador a svc_charac si la creacion fue exitosa.
 *         Null en caso contrario.
 */
svc_charac* new_svc_charac(char *route) {
    svc_charac *s = malloc(sizeof(svc_charac));

    if (!s)
        return NULL;

    s->route = route;
    s->scheds = new_bus_dep_time_list();

    return s;
}
