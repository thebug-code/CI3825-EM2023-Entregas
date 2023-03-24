#ifndef __arrival_schedule_H__
#define __arrival_schedule_H__

/**
 * Estructura de horarios de las paradas del transporte USB
 */
typedef struct Arrival_schedule {
    time_t hour;
    int n_people;
} arrival;

arrival* new_arrival(time_t hour, int people);
#endif
