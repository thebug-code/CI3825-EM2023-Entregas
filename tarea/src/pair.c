#include <stdlib.h>
#include <stdio.h>

#include "pair.h"
#include "tweet_list.h"

/**
 * Crea una par donde el primer elemento es un char
 * y el segundo un tweet.
 *
 * @param first: Primer elemento del par.
 * @param second: Segundo elemento del par.
 * @return Un apuntador a pair si la creación fue exitosa.
 *     NULL en caso contrario.
 */
pair *pair_new(char *first, tweet *second) {
    pair *p = malloc(sizeof(pair));
    if (!p)
        return NULL;

    p->first = first;
    p->second = second;

    return p;
}

/**
 * Imprime una representacion en string del par.
 *
 * Para propositos de depuracion.
 *
 * @param pair: Apuntador a estructura pair.
 */
void pair_print(pair *p) {
    printf("('%s', '%s')", p->first, p->second);
}
