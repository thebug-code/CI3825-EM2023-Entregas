/**
 * Implementaciones de funciones utiles para estructura de tipo
 * schedule.
 *
 */

#include <stdlib.h>
#include "schedule.h"

/*
 * Crea una structura Schedule
 *
 * @param hour: hora a la que parte el j-esimo autobus de la
 * universidad hacia la i-esima parada
 * @param min: minutos despues de la hora a los que parte el
 * j-esimo autobus hacia la i-esima parada
 * @param cap: capacidad del j-esimo autobus a la i-esima parada
 * @return Un apuntador a Schedule si la creacion fue exitosa.
 *         NULL en caso contrario.
 */
sched* new_sched(int hour, int min, int cap) {
    struct tm *date;
    time_t now;
    sched *s = malloc(sizeof(sched));

    if (!s)
        return NULL;

    time(&now);
    date = localtime(&now);

    date->tm_hour = hour;
    date->tm_min = min;
 
    s->time = mktime(date);
    s->cap = cap;

    return s;
}
