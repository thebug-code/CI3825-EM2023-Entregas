/**
 * Implementacion de la lista circular donde cada cada nodo es un
 * apuntador a struct tweet y de las funciones auxiliares paea tweet.
 *
 * Soporta las operaciones de creacion e insercion.
 */

#include <stdlib.h>
#include <time.h>

#include "user_list.h"
#include "tweet_list.h"

/**
 * Crea una lista doblemente enlazada sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa. 
 * de los contrario NULL.
 */
tweet_node *new_tweet_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    tweet_node *head = malloc(sizeof(tweet_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}

/**
 * Anade un tweet nodo a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo User.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_tweet_list(tweet_node **list, tweet *data) {
    tweet_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, coloca el dato en el nodo */
        head->data = data;
    } else {
        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        tweet_node *new_node = malloc(sizeof(tweet_node));

        if (!new_node)
            return 0;

        /* Coloca el dato en el nodo */
        new_node->data = data;
        
        /* Recorre la lista enlazada hasta el final */
        while (head->next)
            head = head->next;

        /* head es el ultimo nodo de la lista enlazada */
        head->next = new_node;
        new_node->prev = head;
    }

    return 1;
}

/*
 * Crea una structura tweet
 *
 * @param str_tweet: str del tweet.
 * @param tm: hora y fecha de publicacion del tweet.
 * @return Un apuntador a tweet si la creacion fue exitosa.
 *         NULL en caso contrario.
 */
tweet* new_tweet(char* str_tweet, time_t tm) {
    tweet *tw = malloc(sizeof(tweet));

    if (!tw)
        return NULL;

    tw->str_tweet = str_tweet;
    tw->tm = tm;
    return tw;
}

/*
 *  Libera un nodo de la lista enlazada de tweet.
 *
 *  @param item: Apuntador al nodo a liberar.
 */
void free_tweet_node(tweet_node* item) {
    free(item->data);
    free(item);
}
