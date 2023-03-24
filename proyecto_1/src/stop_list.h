#ifndef __stop_list_H__
#define __stop_list_H__

#include <aio.h>

#include "bus_stop.h"

/*
 * Estructura de nodo de lista de paradas de autobuses
 */
typedef struct Stop_node {
    struct Stop_node *prev, *next; /* Elementos anterior y siguiente */
    stop *data; /* Dato de nodo, de tipo stop */
} stop_node;


/*
 * Crea una lista doblemente enlazada de paradas de autobuses sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * De lo contrario NULL.
 */
stop_node *new_stop_list();


/*
 * Añade un stop nodo a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo stop.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_stop_list(stop_node **list, stop *data);


/*
 * Imprime la lista de paradas de autobuses en un formato legible.
 *
 * @param list: apuntador a la cabeza de la lista de paradas de autobuses
 */
void print_stop_list(stop_node *list);

#endif
