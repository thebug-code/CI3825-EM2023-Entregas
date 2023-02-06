#ifndef __TWEET_LIST_H__
#define __TWEET_LIST_H__

#include <aio.h>
#include <time.h>

/**
 * Estructura de tweet nodo para lista circular doblemente enlazada
 */
typedef struct Tweet_node {
    struct Tweet_node *prev, *next; /* Elementos anterior y siguiente */
    struct Tweet *data; /* Dato de nodo, de tipo tweet */
} tweet_node;

/**
 * Estructura Tweet para almecenar str de tweet y fecha
 */
typedef struct Tweet {
    char* str_tweet;
    time_t tm;
} tweet;

tweet* new_tweet(char* tweet, time_t tm);
tweet_node *new_tweet_list();
u_int8_t push_tweet_list(tweet_node **head, tweet *data);


#endif
