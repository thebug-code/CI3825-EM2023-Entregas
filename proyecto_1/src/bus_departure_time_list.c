/*
 * Implementacion de las funciones de la lista de horarios de salida
 * de los buses.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bus_departure_time_list.h"


/*
 * Crea una lista doblemente enlazada de horarios de salida de los
 * autobuses sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * De lo contrario NULL.
 */
bus_dep_time_node *new_bus_dep_time_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    bus_dep_time_node *head = malloc(sizeof(bus_dep_time_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}


/*
 * Añade un nodo de horario de salida de autobus a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo bus_dep_time.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_bus_dep_time_list(bus_dep_time_node **list, bus_dep_time *data) {
    bus_dep_time_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, pone el dato en el nodo
         * head->prev apunta al final de la cola
         */
        head->data = data;
        head->prev = head;
    } else {
        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        bus_dep_time_node *new_node = malloc(sizeof(bus_dep_time_node));
        if (!new_node)
            return 0;

        /* Coloca los datos en el nodo */
        new_node->data = data;
        new_node->next = NULL;
        new_node->prev = head->prev;

        head->prev->next = new_node;
        head->prev = new_node;
    }

    return 1;
}


/*
 * Libera la memoria de la lista de horarios de salida de los autobuses.
 *
 * @param list: apuntador a la lista de horarios de salida de los autobuses.
 */
void destroy_bus_dep_time_list(bus_dep_time_node **list) {
    bus_dep_time_node *bus_dep_time = *list;

    if (!bus_dep_time->data) {
        free(bus_dep_time);
    }
    else {
        /* Recorre la lista de horarios de salida de los autobuses */
        while (bus_dep_time) {
            bus_dep_time_node *tmp = bus_dep_time;
            bus_dep_time = bus_dep_time->next;
            free(tmp->data);
            free(tmp);
        }
    }

    *list = NULL;
}


/*
 * Imprime un nodo de la lista de horarios de salida de los autobuses en un
 * formato legible.
 *
 * @param node: apuntador al nodo de la lista de horarios de salida de los
 * autobuses.
 */
void print_bus_dep_time_node(bus_dep_time_node *node) {
    printf("('%ld', '%d')", node->data->time, node->data->cap);
}
