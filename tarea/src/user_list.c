/**
 * Implementacion de la lista circular, donde cada cada nodo es un
 * apuntador a struct User.
 *
 * Soporta las operaciones de creacion y isercion.
 */

#include <stdlib.h>
#include "user_list.h"
#include "tweet_list.h"

/**
 * Crea una lista doblemente enlazada sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa. 
 * de los contrario NULL.
 */
user_node *new_user_list() {
    /* Asignar memoria dinamicamente para crear la lista */
    user_node *head = malloc(sizeof(user_node));

    if (!head)
        return NULL;

    /* La cabeza de la lista apunta a si misma */
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;

    return head;
}

/**
 * Añade un user nodo a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo User.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_user_list(user_node **list, user *data) {
    user_node *head = *list;

    if (!head->data) {
        /* Si la lista es nueva, coloca el dato en el nodo */
        head->data = data;
    } else {
        /* De lo contrario, crea una nueva entrada para la lista
        dinamicamente */
        user_node *new_node = malloc(sizeof(user_node));
        if (!new_node)
            return 0;

        /* Coloca el dato en el nodo */
        new_node->data = data;

        new_node->next = head;
        new_node->prev = NULL;
        head->prev = new_node;

        /* El nuevo node es la cabeza de la lista */
        *list = new_node;
    }

    return 1;
}

/*
 * Crea una structura user
 *
 * @param username: nombre de usuario del usuario.
 * @param hash_password: hash de la contrasena del usuario.
 * @return Un apuntador a User si la creacion fue exitosa.
 *         NULL en caso contrario.
 */
user* new_user(char* username, int hash_password) {
    user *u = malloc(sizeof(user));

    if (!u)
        return NULL;

    u->username = username;
    u->hash_password = hash_password;
    u->tweet_list = new_tweet_list(); /* Crear lista de tweets */
    u->sig_list = new_user_list(); /* Crear lista de users */

    return u;
}

/*
 *  Libera un nodo de la lista enlazada de usuarios.
 *
 *  @param item: Apuntador al nodo a liberar.
 */
void free_user_node(user_node* item) {
    tweet_node *tw = item->data->tweet_list;
    user_node *u = item->data->sig_list;
    user_node *tmp0 = NULL;
    tweet_node *tmp1 = NULL;
        
    if (!tw->data) 
        free(tw);
    else {
        /* Recorrer la lista de tweet del usuario */
        while (tw) {
            tmp1 = tw->next;
            free_tweet_node(tw);
            tw = tmp1;
        }
    }

    if (!u->data) 
        free(u);
    else {
        /* Recorrer la lista de los siguiendo del usuario */
        while (u) {
            tmp0 = u->next;
            free_user_node(u);
            u = tmp0;
        }
    }

    free(item->data);
    free(item);
}
