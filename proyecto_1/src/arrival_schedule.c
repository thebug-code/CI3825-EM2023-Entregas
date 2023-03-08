/**
 * Implementaciones de funciones utiles para estructura de tipo
 * Arrival_schedule.
 */

#include <stdlib.h>
#include "arrival_schedule.h"

/*
 * Crea una structura Arrival_schedule
 *
 * @param hour: j-esima hora de la i-esima parada
 * @param people: cantidad de personas que llegan a la j-esima
 * hora a la i-esima parada
 * @return Un apuntador a Arrival_schedule si la creacion fue exitosa.
 *         NULL en caso contrario.
 */
arrival* new_arrival(int hour, int people) {
    arrival *a = malloc(sizeof(arrival));

    if (!a)
        return NULL;
 
    a->hour = hour;
    a->n_people = people;

    return a;
}
