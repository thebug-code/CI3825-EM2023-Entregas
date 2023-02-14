#ifndef __USER_LIST_H__
#define __USER_LIST_H__

#include <aio.h>

#include "tweet_list.h"

/**
 * Estructura de user nodo para lista circular doblemente enlazada
 */
typedef struct User_node {
    struct User_node *prev, *next; /* Elementos anterior y siguiente */
    struct User *data; /* Dato de nodo, de tipo user */
} user_node;

/**
 * Estructura de usuario para almacenar sus datos
 */
typedef struct User {
    char* username;
    char* description;
    int hash_password;
    tweet_node *tweet_list; /* Lista enlazada donde cada nodo es un tweet */
    struct User_node *sig_list; /* Lista enlazada donde cada nodo es un usuario */
} user;

user_node *new_user_list();
void show_user_list(user_node *list);
u_int8_t push_user_list(user_node **head, user *data);
user *get_user_list(user_node *user_list, char* str);
user *new_user(char* username, int hash_password, char* description);
void free_user_node(user_node** list);

#endif
