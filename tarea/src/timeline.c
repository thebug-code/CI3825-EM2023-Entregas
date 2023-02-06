/**
 * Implementacion de las funciones auxiliares para el timeline de los
 * usuarios.
 */

#include <stdlib.h> 
#include <stdio.h> 

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
    timeline_node *tl_head = *timeline_list;
    /* user_node *lfu_head = *list_follower_users; */
    
    while (lfu_head != NULL) {
        /* Obtener el puntero al head de la lista de 
         * tweet de i-esimo user */
        tweet_node *tw_list_i = lfu_head->data->tweet_list;

        /* Recorrer la lista e insertar los tweet en
         * timeline list */
        while (tw_list_i != NULL) {
            /* crear par del i-esimo tweet */
            pair *p_i = pair_new(lfu_head->data->username, tw_list_i->data);
            if (!p_i)
                return 0;
            if (sorted_insert_timeline_list(&tl_head, p_i) == 0)
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
    while (timeline_list != NULL) {
        printf("User @%s\n", timeline_list->data->first);
        printf("Dijo a las %s: '%s'\n", ctime(&(timeline_list->data->second->tm)), timeline_list->data->second->str_tweet);
        timeline_list = timeline_list->next;
    }
    return;
}

/*
 * Anade un pair donde el segundo elemento es un tweet y el primer
 * elemento el usuario que lo publico a la lista en orden 
 * (desde el mas antiguo al mas reciente).
 *
 * @param list: apuntador a la cabeza de la timeline list.
 * @param tw: estructura pair a anadir en la lista.
 * @return 1 si la operacion fue exitosa. 0 en caso contrario.
 */
u_int8_t sorted_insert_timeline_list(timeline_node **timeline_list, pair *tw_pair) {
    timeline_node *head = *timeline_list;

    if (!head->data)
        /* la lista no tiene elementos */
        head->data = tw_pair;
    else if (difftime(head->data->second->tm, tw_pair->second->tm) == 0 || difftime(head->data->second->tm, tw_pair->second->tm) < 0) {
        /* El tweet que esta en la cabeza de la lista fue publicado al mismo t o antes que el
         * t del nuevo nodo*/
        timeline_node *new_node = (timeline_node*)malloc(sizeof(timeline_node));

        if (!new_node)
            return 0;

        new_node->data = tw_pair;
        head->prev = new_node;
        new_node->next = head;
        new_node->prev = NULL;

        /* El nuevo nodo es la cabeza de la lista */
        *timeline_list = new_node;
    }
    else {
        /* Se recorre la lista hasta encontrar el tweet que tenga t mayor al tweet a insertar */
        timeline_node *new_node = (timeline_node*)malloc(sizeof(timeline_node));
        timeline_node *curr = head;

        while (curr->next != NULL && difftime(curr->next->data->second->tm, tw_pair->second->tm) > 0)
            curr = curr->next;

        new_node->next = curr->next;
        new_node->prev = curr;

        if (curr->next != NULL)
            curr->next->prev = new_node;

        curr->next = new_node;
    }
    return 1;
}
