#ifndef __bus_departure_time_list_H__
#define __bus_departure_time_list_H__

/*
 * Incluye la libreria stdint.h para poder usar el tipo de dato uint8_t.
 */
#include <stdint.h>

#include "bus_departure_time.h"


/**
 * Estructura de nodo para lista circular doblemente enlazada
 * de horarios de salida de los autobuses.
 */
typedef struct bus_departure_time_node {
    struct bus_departure_time_node *prev, *next; /* Elementos anterior y siguiente */
    bus_dep_time *data; /* Dato de nodo, de tipo bus_departure_time */
} bus_dep_time_node;



/*
 * Crea una lista doblemente enlazada de horarios de salida de los
 * autobuses sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * De lo contrario NULL.
 */
bus_dep_time_node *new_bus_dep_time_list();


/*
 * Añade un nodo de horario de salida de autobus a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo bus_dep_time.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_bus_dep_time_list(bus_dep_time_node **list, bus_dep_time *data);


/*
 * Imprime un nodo de la lista de horarios de salida de los autobuses en un
 * formato legible.
 *
 * @param node: apuntador al nodo de la lista de horarios de salida de los
 * autobuses.
 */
void print_bus_dep_time_node(bus_dep_time_node *node);


/*
 * Libera la memoria de la lista de horarios de salida de los autobuses.
 *
 * @param list: apuntador a la lista de horarios de salida de los autobuses.
 */
void destroy_bus_dep_time_list(bus_dep_time_node **list);

#endif
