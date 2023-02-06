#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <aio.h>

#include "user_list.h"

#define HASH_MAX 10 /* Maximo tamano de la tabla de hash */

/**
 * Funciones utiles para la tabla de hash.
 */

user *get_user(user_node **hash_table, char *str);
user_node **new_hash_table();
u_int32_t hash_code(char* str);
u_int8_t insert_user_hash_table(user_node ***hash_table, user *user_struct);
#endif
