#ifndef __schedule_list_H__
#define __schedule_list_H__

#include <aio.h>
#include "schedule.h"

/**
 * Estructura de nodo para lista circular doblemente enlazada
 * de horarios
 */
typedef struct Schedule_node {
    struct Schedule_node *prev, *next; /* Elementos anterior y siguiente */
    sched *data; /* Dato de nodo, de tipo sched */
} sched_node;

sched_node *new_sched_list();
u_int8_t push_sched_list(sched_node **list, sched *data);
void print_sched_node(sched_node* sched);
void free_sched_node(sched_node** list);
/* user *get_sched_list(sched_node *sched_list, char* str); */

#endif
