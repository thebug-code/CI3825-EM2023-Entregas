#ifndef __arrival_list_H__
#define __arrival_list_H__

#include <aio.h>
#include "arrival_schedule.h"

/**
 * Estructura de nodo para lista circular doblemente enlazada
 * de horarios de llegada
 */
typedef struct Arrival_node {
    struct Arrival_node *prev, *next; /* Elementos anterior y siguiente */
    arrival *data; /* Dato de nodo, de tipo arraval */
} arrival_node;

arrival_node *new_arrival_list();
u_int8_t push_arrival_list(arrival_node **list, arrival *data);
void free_arrival_node(arrival_node** list);

#endif
