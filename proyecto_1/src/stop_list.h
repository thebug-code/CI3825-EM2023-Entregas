#ifndef __stop_list_H__
#define __stop_list_H__

#include <aio.h>

#include "bus_stop.h"

/**
 * Estructura de nodo para lista circular doblemente enlazada
 * de servicios.
 */
typedef struct Stop_node {
    struct Stop_node *prev, *next; /* Elementos anterior y siguiente */
    stop *data; /* Dato de nodo, de tipo stop */
} stop_node;

stop_node *new_stop_list();
u_int8_t push_stop_list(stop_node **list, stop *data);
void print_stop_list(stop_node *list);

#endif
