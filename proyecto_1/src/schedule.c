/**
 * Implementaciones de funciones utiles para estructura de tipo
 * schedule.
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
    time_t now;
    struct tm *time_info;
    sched *s = malloc(sizeof(sched));

    if (!s)
        return NULL;

    now = time(NULL);
    time_info = localtime(&now);

    time_info->tm_hour = hour;
    time_info->tm_min = min;
    time_info->tm_sec = 0;
 
    s->time = mktime(time_info);
    s->cap = cap;

    return s;
}
