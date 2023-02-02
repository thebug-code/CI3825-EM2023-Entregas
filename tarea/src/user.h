#ifndef __USER_H__
#define __USER_H__

#include "user_list.h"
#include "tweet_list.h"

/**
 * Estructura de usuario para almacenar sus datos
 */
typedef struct User {
    char* username;
    int hash_password;
    tweet_node* tweet_list; // Lista enlazada donde cada nodo es un tweet
    user_node* sig_list; // Lista enlazada donde cada nodo es un usuario
} user;

user* new_user(char* username, int hash_password);
#endif
