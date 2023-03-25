/**
 * Implementaciones de funciones utiles para lista circular de los
 * horarios de llegada
 *
 * La lista soporta las operaciones de creacion e insercion de nodos.
 */

#include <stdio.h>
#include <stdlib.h>

#include "arrival_list.h"


/**
 * Crea una lista doblemente enlazada sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * de los contrario NULL.
 */
arrival_node *new_arrival_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    arrival_node *head = malloc(sizeof(arrival_node));

    if (!head)
        return NULL;
    
    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}


/**
 * Añade un arrival nodo a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo arrival.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_arrival_list(arrival_node **list, arrival *data) {
    arrival_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, pone el dato en el nodo
         * head->prev apunta al final de la cola
         */
        head->data = data;
        head->prev = head;
    } else {
        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        arrival_node *new_node = malloc(sizeof(arrival_node));
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
 * Elimina un nodo de la lista de horarios de llegada.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Apuntador al nodo a eliminar.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t pop_arrival_list(arrival_node **list, arrival_node *del) {
    arrival_node *head = *list;

    if (!head || !del || !head->data) {
        /* Si la lista esta vacia o el nodo a eliminar no existe, no hace nada */
        return 0;
    } else {
        /* Si el nodo a eliminar es el primero */
        if (head == del)
            *list = del->next;
        
        /* Si el nodo a eliminar no es el ultimo */
        if (del->next)
            del->next->prev = del->prev;

        /* Si el nodo a eliminar no es el primero */
        if (del->prev)
            del->prev->next = del->next;

        free(del);
    }

    return 1;
}


/**
 * Libera la memoria de la lista de horarios de llegada
 *
 * @param list: apuntador a la lista de horarios de llegada
 */
void destroy_arrival_list(arrival_node** list) {
    arrival_node *node = *list;

    if (!node->data) {
        free(node);
    }
    else {
        /* Recorre la lista de horarios de llegada */
        while (node) {
            arrival_node *tmp = node;
            node = node->next;
            free(tmp->data);
            free(tmp);
        }
    }

    *list = NULL;
}
