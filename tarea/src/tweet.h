#ifndef __TWEET_H__
#define __TWEET_H__

#include <time.h>

/**
 * Estructura Tweet para almecenar str de tweet y fecha
 */
typedef struct Tweet {
    char* str_tweet;
    time_t tm;
} tweet;
// Falta algunas funciones aqui (verificar en el .c)
#endif

