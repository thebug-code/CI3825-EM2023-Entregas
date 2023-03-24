/**
 * Implementaciones de funciones utiles para estructura de tipo
 * bus_stop.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bus_stop.h"


/**
 * Crea una nueva estructura de parada de autobus
 *
 * @param cod: codigo de la parada
 * @param route_name: nombre de la ruta
 * @param recorr: recorrido de la ruta
 * @return un apuntador a la nueva estructura de parada de autobus.
 *        NULL en caso contrario.
 */
stop* new_stop(char cod[4], char route_name[50], int recorr) {
    stop *s = malloc(sizeof(stop));

    if (!s)
        return NULL;

    strcpy(s->cod, cod);
    strcpy(s->route_name, route_name);
    s->recorr = recorr;
    s->arrivals = new_arrival_list();

    return s;
}
