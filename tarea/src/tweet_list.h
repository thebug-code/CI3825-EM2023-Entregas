#ifndef __TWEET_LIST_H__
#define __TWEET_LIST_H__

// Falta agregar los .h respectivos y librerias
#include "tweet.h"

/**
 * Estructura de tweet nodo para lista circular doblemente enlazada
 */
typedef struct Tweet_node {
    struct Tweet_node *prev, *next; // Elementos anterior y siguiente
    tweet *data; // Dato de nodo, de tipo tweet
} tweet_node;

tweet_node *new_tweet_list();
u_int8_t push_tweet_list(node **head, tweet *data);
#endif
