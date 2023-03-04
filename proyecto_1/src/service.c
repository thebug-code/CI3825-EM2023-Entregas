/**
 * Implementaciones de funciones utiles para estructura de tipo
 * service.
 */

#include <stdlib.h>

#include "service.h"

/*
 * Crea una structura de servicio
 *
 * @param route: puntero a char con el nombre de la ruta
 * @return Un apuntador a svc si la creacion fue exitosa.
 *         Null en caso contrario.
 */
svc* new_svc(char *route) {
    svc *s = malloc(sizeof(svc));

    if (!s)
        return NULL;

    s->route = route;
    s->scheds = new_sched_list();

    return s;
}
