#ifndef __USER_LIST_H__
#define __USER_LIST_H__

// Falta agregar los .h respectivos y librerias
#include "user.h"

/**
 * Estructura de user nodo para lista circular doblemente enlazada
 */
typedef struct User_node {
    struct User_node *prev, *next; // Elementos anterior y siguiente
    user *data; // Dato de nodo, de tipo user
} user_node;

user_node *new_user_list();
u_int8_t push_user_list(user_node **head, user *data);

#endif
