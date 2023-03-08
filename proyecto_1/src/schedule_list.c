/**
 * Implementaciones de funciones utiles para lista circular de los
 * horarios.
 *
 * La lista soporta las operaciones de creacion, insercion, 
 * e impresion de horarios en un formato legible.
 */

#include <stdio.h>
#include <stdlib.h>

#include "schedule_list.h"

/**
 * Crea una lista doblemente enlazada sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * de los contrario NULL.
 */
sched_node *new_sched_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    sched_node *head = malloc(sizeof(sched_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}

/**
 * Añade un sched nodo a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo sched.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_sched_list(sched_node **list, sched *data) {
    sched_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, pone el dato en el nodo */
        head->data = data;
    } else {
        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        sched_node *temp;
        sched_node *new_node = malloc(sizeof(sched_node));
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
 *  Libera un nodo de la lista enlazada de horarios.
 *
 *  @param item: Apuntador al nodo a liberar.
 */
void free_sched_list(sched_node** list) {
    sched_node *sched = *list;

    if (!sched->data) {
        free(sched);
    }
    else {
        /* Recorre la lista de horarios */
        while (sched) {
            sched_node *tmp = sched;
            sched = sched->next;
            free(tmp->data);
            free(tmp);
        }
    }

    *list = NULL;
}


/*
 *  Imprime un nodo de la lista enlazada de horarios.
 *
 *  @param item: Apuntador al nodo a imprimir.
 */
void print_sched_node(sched_node* sched) {
    printf("('%ld', '%d')", sched->data->time, sched->data->cap);
}
