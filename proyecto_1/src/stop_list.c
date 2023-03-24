/**
 * Implementaciones de funciones utiles para lista circular de las
 * paradas de autobuses.
 *
 * La lista soporta las operaciones de creacion e insercion
 */

#include <stdio.h>
#include <stdlib.h>

#include "stop_list.h"


/**
 * Crea una lista doblemente enlazada de paradas de autobuses sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * de los contrario NULL.
 */
stop_node *new_stop_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    stop_node *head = malloc(sizeof(stop_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}


/**
 * Añade un stop nodo a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo stop.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_stop_list(stop_node **list, stop *data) {
    stop_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, pone el dato en el nodo
         * head->prev apunta al final de la cola
         */
        head->data = data;
        head->prev = head;

    } else {

        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        stop_node *new_node = malloc(sizeof(stop_node));
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


/**
 * Imprime la lista de paradas de autobuses en un formato legible.
 *
 * @param list: Apuntador a la cabeza de la lista.
 */
void print_stop_list(stop_node *list) {
    stop_node *h = list;
    
    while (h) {
        arrival_node *arri = h->data->arrivals;
        printf("%s %s %d ", h->data->cod, h->data->route_name, h->data->recorr);
    
        while (arri) {
            printf("%d ", arri->data->n_people);
    	arri = arri->next;
        }
    
        printf("\n");
        h = h->next;
    }

    return;
}
