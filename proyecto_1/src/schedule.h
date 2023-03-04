#ifndef __schedule_H__
#define __schedule_H__

#include <time.h>

/**
 * Estructura de horarios del transporte USB
 */
typedef struct Schedule {
    time_t time;
    int cap;
} sched;

sched* new_sched(int hour, int min, int cap);
#endif
