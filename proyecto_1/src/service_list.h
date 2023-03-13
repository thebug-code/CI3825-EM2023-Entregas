#ifndef __service_list_H__
#define __service_list_H__

#include <aio.h>

#include "service.h"

/**
 * Estructura de nodo para lista circular doblemente enlazada
 * de servicios.
 */
typedef struct Service_node {
    struct Service_node *prev, *next; /* Elementos anterior y siguiente */
    svc *data; /* Dato de nodo, de tipo svc */
} svc_node;

svc_node *new_service_list();
u_int8_t push_service_list(svc_node **list, svc *data);
void print_svc_list(svc_node *list);

/*void print_sched_node(sched_node* sched);*/
/*void free_sched_node(service_node** list);*/
#endif
