#ifndef __PAIR_H__
#define __PAIR_H__

#include "tweet_list.h"

/**
 * Estructura de par de cadenas de caracteres.
 */
typedef struct Pair {
    char *first; /* Primer elemento del par */
    tweet *second; /* Segundo elmento del par */
} pair;

pair *pair_new(char *first, tweet *second);
void pair_print(pair *pair);

#endif
