/*
 * Implementacion de las funciones de la lista de caracterizacion
 * del servicio.
 *
 * La lista soporta las operaciones de creacion, insercion y 
 * impresion.
 */
#include <stdio.h>
#include <stdlib.h>

#include "svc_charac_list.h"


/*
 * Crea una lista doblemente enlazada de caracterizacion del servicio
 * sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * De lo contrario NULL.
 */
svc_charac_node *new_svc_charac_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    svc_charac_node *head = malloc(sizeof(svc_charac_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}


/*
 * Añade un nodo de caracterizacion del servicio a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo svc_charac.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_svc_charac_list(svc_charac_node **list, svc_charac *data) {
    svc_charac_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, pone el dato en el nodo */
        head->data = data;
    } else {
        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        svc_charac_node *temp;
        svc_charac_node *new_node = malloc(sizeof(svc_charac_node));
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


/*
 * Libera la memoria de la lista de caracterizacion del servicio.
 *
 * @param list: apuntador a la lista de caracterizacion del servicio.
 */
void destroy_svc_charac_list(svc_charac_node **list) {
    svc_charac_node *svc_charac = *list;

    if (!svc_charac->data) {
        free(svc_charac);
    }
    else {
        /* Recorre la lista de caracterizacion del servicio */
        while (svc_charac) {
            svc_charac_node *tmp = svc_charac;
            svc_charac = svc_charac->next;
            free(tmp->data);
            free(tmp);
        }
    }

    *list = NULL;
}


/*
 * Imprime un nodo de la lista de caracterizacion del servicio en un
 * formato legible.
 *
 * @param node: apuntador al nodo de la lista de caracterizacion del
 * servicio.
 */
void print_svc_charac_node(svc_charac_node *node) {
    printf("('%ld', '%d')", node->data->time, node->data->cap);
}
