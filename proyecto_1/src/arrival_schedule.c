/**
 * Implementaciones de funciones utiles para estructura de tipo
 * Arrival_schedule.
 */

#include <stdlib.h>
#include "arrival_schedule.h"


/**
 * Crea una nueva estructura de horarios de llegada
 *
 * @param hour: hora de llegada
 * @param people: numero de personas que llegan
 * @return un apuntador a la nueva estructura de horarios de llegada
 */
arrival* new_arrival(time_t hour, int people) {
    arrival *a = malloc(sizeof(arrival));

    if (!a)
        return NULL;
 
    a->hour = hour;
    a->n_people = people;

    return a;
}
