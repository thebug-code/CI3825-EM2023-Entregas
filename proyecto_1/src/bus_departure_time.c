/**
 * Implementaciones de funciones utiles para estructura de tipo
 * bus_departure_time.
 */

#include <stdlib.h>
#include "bus_departure_time.h"
#include "bus_departure_time.h"


/**
 * Crea una nueva estructura de horarios de salida
 *
 * @param hour: hora de salida
 * @param min: minuto de salida
 * @param cap: capacidad del bus
 * @return un apuntador a la nueva estructura de horarios de salida
 *        NULL en caso contrario.
 */
bus_dep_time* new_bus_dep_time(int hour, int min, int cap) {
    time_t t;
    struct tm *time_info;

    bus_dep_time *s = malloc(sizeof(bus_dep_time));

    if (!s)
        return NULL;

    t = time(NULL);
    time_info = localtime(&t);

    time_info->tm_hour = hour;
    time_info->tm_min = min;
    time_info->tm_sec = 0;

    s->time = mktime(time_info);
    s->cap = cap;

    return s;
}
