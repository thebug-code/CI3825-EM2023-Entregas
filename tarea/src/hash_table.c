/**
 * Implementacion de la tabla de hash y de funciones utiles para
 * la misma.
 *
 * Soporta las operaciones creacion, insercion y obtencion de user.
 */

#include <stdlib.h>
#include <string.h>
#include <aio.h>
#include <stdio.h>

#include "hash_table.h"
#include "user_list.h"

/**
 * Inicializa un tabla de hash de tamanio HASH_MAX.
 * Cada item de la tabla es apuntador a la cabeza de una
 * lista enlazada.
 */
user_node **new_hash_table() {
    int i = 0;
    user_node **hash_table = (user_node**) malloc(HASH_MAX * sizeof(user_node*));
    if (!hash_table) 
        return NULL;
    
    /* Inicializar item de la tabla de hash */
    for (i = 0; i < HASH_MAX; i++) {
        hash_table[i] = new_user_list();
    }
    return hash_table;
}

/*
 * Retorna un codigo hash correspondienre al string <str>
 */
u_int32_t hash_code(char *str) {
    u_int32_t hash_val;
    for (hash_val = 0; *str != '\0'; str++) 
        hash_val = *str + 31 * hash_val;
    return hash_val % HASH_MAX;
}

/**
 * Buscar un usuario en la tabla de hash. 
 *
 * @param hash_table: tabla de hash con los usuarios.
 * @param str: apuntador al username del usuario.
 * @return apuntador a structura tipo usuario, si el usuario
 * esta en la tabla de hash. NULL en caso contrario.
 */
user *get_user(user_node **hash_table, char* str) {
    u_int32_t hash = hash_code(str); /* indice donde se supone que esta el user */
    user_node *head = hash_table[hash]; /* Apuntador a la cabeza de la lista enlazada  */

    if (!head->data)
        return NULL; /* el user no esta en la tabla de hash */
    
    while (head != NULL) {
        if (strcmp(str, head->data->username) == 0) {
            return head->data;
        }
        head = head->next;
    }
    return NULL;
}

/**
 * Inserta un usuario en la tabla de hash.
 *
 * @param hash_table: Tabla de hash con los usuarios.
 * @param user_struct: apuntador a estructura user a insertar en la tabla de hash.
 * @return 1 si la operacion fue exitosa. 0 de lo contrario.
 */
u_int8_t insert_user_hash_table(user_node ***hash_table, user *user_struct) {
    user_node **array = *hash_table;
    u_int32_t hash = hash_code(user_struct->username);
    return push_user_list(&array[hash], user_struct); 
}

/*
 * Libera todos los elementos de la tabla de hash.
 *
 * @param hash_table: Apuntador a la tabla de hash.
 */
void free_table(user_node **hash_table) {
    int i;
    user_node* item = NULL;

    for (i = 0; i < HASH_MAX; i++) {
        item = hash_table[i];
        if (item->data)
            free_user_node(&item);
        else {
            free(hash_table[i]);
            hash_table[i] = NULL;
        }
    }

    free(hash_table);
}
