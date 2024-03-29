/**
 * Implementacion de las funciones auxiliares para el timeline de los
 * usuarios.
 */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#include "user_list.h"
#include "timeline.h"
#include "tweet_list.h"

/**
 * Crea una timeline list doblemente enlazada sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * de los contrario NULL.
 */
timeline_node *new_timeline_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    timeline_node *head = malloc(sizeof(timeline_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}

/*
 * Construye el timeline de un usuario.
 *
 * @param timeline_list: Puntero a la cabeza de la timeline lista.
 * @param lfu_head: Puntero a la cabeza de la lista de
 * siguiendo del usuario.
 * @return 1 si la operacion fue exitosa. 0 en caso contrario.
 */
u_int8_t build_timeline_list(timeline_node **timeline_list, user_node *lfu_head) {
    
    if (!lfu_head->data)
        return 1; /* El usuario no sigue a nadie */

    while (lfu_head) {
        /* Obtener el puntero al head de la lista de 
         * tweet de i-esimo user */
        tweet_node *tw_list_i = lfu_head->data->tweet_list;

        if (!tw_list_i->data)
            return 1; /* El usuario no a publicado tweet */

        /* Recorrer la lista e insertar los tweet en
         * timeline list */
        while (tw_list_i) {
            /* crear par del i-esimo tweet */
            pair *p_i = pair_new(lfu_head->data->username, tw_list_i->data);
            if (!p_i)
                return 0;
            if (sorted_insert_timeline_list(timeline_list, p_i) == 0)
                return 0; /* ocurrio un error */
            tw_list_i = tw_list_i->next;
        }
        lfu_head = lfu_head->next;
    }
    return 1;
}

/* Muestra en pantalla el timeline de un usuario
 *
 * @param list_follower_users: Puntero a la cabeza de la
 * lista de siguiendos del usuario.
 */
void show_timeline(user_node *list_follower_users) {
    /* Crear timeline list */
    timeline_node *timeline_list = new_timeline_list(); 
    if (!timeline_list)
        exit(0);

    /* Construir timeline list */
    if (build_timeline_list(&timeline_list, list_follower_users) == 0)
        exit(0);

    /* Mostrar timeline */
    if (!timeline_list->data) {
        printf("No hay tweets para mostrar\n");
        return; /* No hay nada que mostrar */
    }

    /* Recorre la lista enlazada hasta el final */
    while (timeline_list->next)
        timeline_list = timeline_list->next;

    while (timeline_list != NULL) {
        char *t = ctime(&(timeline_list->data->second->tm));

        printf("User @%s\n", timeline_list->data->first);
        printf("Dijo a las %.*s:'%s'\n", (int)strlen(t)-1, t, timeline_list->data->second->str_tweet);
        printf("------------------------------------\n");
        timeline_list = timeline_list->prev;
    }
    return;
}

/*
 * Anade un pair donde el segundo elemento es un tweet y el primer
 * elemento el usuario que lo publico a la lista en orden 
 * (desde el mas antiguo al mas reciente).
 *
 * @param timeline_list: apuntador a la cabeza de la timeline list.
 * @param tw_pair: estructura pair a anadir en la lista.
 * @return 1 si la operacion fue exitosa. 0 en caso contrario.
 */
u_int8_t sorted_insert_timeline_list(timeline_node **timeline_list, pair *tw_pair) {
    timeline_node *head = *timeline_list;

    if (!head->data) {
        /* la lista no tiene elementos */
        head->data = tw_pair;
    }
    else if (difftime(head->data->second->tm, tw_pair->second->tm) == 0 || difftime(head->data->second->tm, tw_pair->second->tm) < 0) {
        /* El tweet que esta en la cabeza de la lista fue publicado al mismo t o antes que el
         * t del nuevo nodo*/
        timeline_node *new_node = (timeline_node*)malloc(sizeof(timeline_node));

        if (!new_node)
            return 0;

        /* Coloca el pair en el nodo */
        new_node->data = tw_pair;

        new_node->next = head;
        new_node->prev = NULL;
        head->prev = new_node;
    
        /* El nuevo nodo es la cabeza de la lista */
        *timeline_list = new_node;
    }
    else {
        /* Se recorre la lista hasta encontrar el tweet que tenga t mayor al tweet a insertar */
        timeline_node *new_node = (timeline_node*)malloc(sizeof(timeline_node));
        timeline_node *curr = head;

        while (curr->next != NULL && difftime(curr->next->data->second->tm, tw_pair->second->tm) > 0)
            curr = curr->next;

        new_node->data = tw_pair;
        new_node->next = curr->next;
        new_node->prev = curr;

        if (curr->next != NULL)
            curr->next->prev = new_node;

        curr->next = new_node;
    }
    return 1;
}
