#ifndef __bus_departure_time_H__
#define __bus_departure_time_H__

#include <time.h>


/**
 * Estructura de horarios de salida de los autobuses.
 */
typedef struct bus_departure_time {
    time_t time; /* Hora de salida */
    int cap; /* Capacidad del bus */
} bus_dep_time;


/**
 * Crea una nueva estructura de horarios de salida
 *
 * @param hour: hora de salida
 * @param min: minuto de salida
 * @param cap: capacidad del bus
 * @return un apuntador a la nueva estructura de horarios de salida
 *        NULL en caso contrario.
 */
bus_dep_time* new_bus_dep_time(int hour, int min, int cap);

#endif
