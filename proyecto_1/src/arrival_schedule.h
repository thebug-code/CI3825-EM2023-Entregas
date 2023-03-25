#ifndef __arrival_schedule_H__
#define __arrival_schedule_H__

/**
 * Estructura de horarios de las paradas del transporte USB
 */
typedef struct Arrival_schedule {
    time_t hour;
    int n_people;
} arrival;


/**
 * Crea una nueva estructura de horarios de llegada
 *
 * @param hour: hora de llegada
 * @param people: numero de personas que llegan
 * @return un apuntador a la nueva estructura de horarios de llegada
 */
arrival* new_arrival(time_t hour, int people);
#endif
