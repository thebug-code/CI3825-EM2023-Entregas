#ifndef __TIMELINE_H__
#define __TIMELINE_H__

#include <aio.h>

#include "user_list.h"
#include "pair.h"

/**
 * Estructura de timeline nodo para lista circular doblemente enlazada
 */
typedef struct Timeline_node {
    struct Timeline_node *prev, *next; /* Elementos anterior y siguiente */
    pair *data; /* Dato de nodo, de tipo tweet */
} timeline_node;

/**
 * Funciones utiles para timeline.
 */

timeline_node *new_timeline_list();
u_int8_t build_timeline_list(timeline_node **timeline_list, user_node *lfu_head);
u_int8_t sorted_insert_timeline_list(timeline_node **timeline_list, pair *tw_pair);
void show_timeline(user_node *list_follower_users);
#endif
