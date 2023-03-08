/**
 * Implementaciones de funciones utiles para estructura de tipo
 * bus_stop.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bus_stop.h"

/*
 * Crea una structura de parada de autobuses
 *
 * @param cod: puntero a char con el codigo de la parada
 * @param route_name: puntero a char con el nombre de la parada
 * @param recorr: tiempo de rrecorido desde la j_esima parada
                 hasta la USB
 * @return Un apuntador a stop si la creacion fue exitosa.
 *         Null en caso contrario.
 */
stop* new_stop(char cod[4], char route_name[50], int recorr) {
    stop *s = malloc(sizeof(stop));

    if (!s)
        return NULL;

    strcpy(s->cod,cod);
    strcpy(s->route_name, route_name);
    s->recorr = recorr;
    s->arrivals = new_arrival_list();

    return s;
}