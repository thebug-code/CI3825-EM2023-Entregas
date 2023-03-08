/**
 * Implementaciones de funciones utiles para lista circular de los
 * servicio.
 *
 * La lista soporta las operaciones de creacion e insercion
 */

#include <stdio.h>
#include <stdlib.h>

#include "service_list.h"

/**
 * Crea una lista doblemente enlazada sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * de los contrario NULL.
 */
svc_node *new_service_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    svc_node *head = malloc(sizeof(svc_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}

/**
 * Añade un svc nodo a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo svc.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_service_list(svc_node **list, svc *data) {
    svc_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, pone el dato en el nodo */
        head->data = data;
    } else {
        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        svc_node *temp;
        svc_node *new_node = malloc(sizeof(svc_node));
        if (!new_node)
            return 0;

        /* Coloca el dato en el nodo */
        new_node->data = data;

        /* Recorre toda la lista para llegar al último nodo */
        temp = head;
        while (temp->next)
            temp = temp->next;

        temp->next = new_node;  
        new_node->prev = temp;  
        new_node->next = NULL;
    }

    return 1;
}

