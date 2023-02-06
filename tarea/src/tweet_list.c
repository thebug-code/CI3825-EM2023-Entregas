/**
 * Implementacion de la lista circular, donde cada cada nodo es un
 * apuntador a struct tweet.
 *
 * Soporta las operaciones de creacion, insercion sin orden e insercion
 * ordenada (desde el tweet mas antiguo al mas reciente).
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
 * Anade un tweet a la lista en orden (desde el mas antiguo al
 * mas reciente).
 *
 * @param list: apuntador a la cabeza de la lista.
 * @param tw: estructura tweet a anadir en la lista.
 * @return 1 si la operacion fue exitosa. 0 en caso contrario.
 */
u_int8_t sorted_insert_tweet_list(tweet_node **timeline_list, tweet *tw) {
    tweet_node *head = *timeline_list;

    if (!head->data)
        /* la lista no tiene elementos */
        head->data = tw;
    else if (difftime(head->data->tm, tw->tm) == 0 || difftime(head->data->tm, tw->tm) < 0) {
        /* El tweet que esta en la cabeza de la lista fue publicado al mismo t o antes que el
         * t del nuevo tweet a inadir */
        tweet_node *new_node = (tweet_node*)malloc(sizeof(tweet_node));

        if (!new_node) 
            return 0;

        head->prev = new_node;
        new_node->next = head;
        new_node->prev = NULL;

        /* El nuevo nodo es la cabeza de la lista */
        *timeline_list = new_node;
    }
    else {
        /* Se recorre la lista hasta encontrar el tweet que tenga t mayor al tweet a insertar */
        tweet_node *new_node = (tweet_node*)malloc(sizeof(tweet_node));
        tweet_node *curr = head;

        while (curr->next != NULL && difftime(curr->next->data->tm, tw->tm) > 0)
            curr = curr->next;

        new_node->next = curr->next;
        new_node->prev = curr;

        if (curr->next != NULL)
            curr->next->prev = new_node;
        
        curr->next = new_node;
    }
    return 1;
}
