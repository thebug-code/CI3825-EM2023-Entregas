#ifndef __arrival_list_H__
#define __arrival_list_H__

/*
 * Incluye la libreria stdint.h para poder usar el tipo de dato uint8_t
 */
#include <stdint.h>

#include "arrival_schedule.h"


/**
 * Estructura de nodo para lista circular doblemente enlazada
 * de horarios de llegada
 */
typedef struct Arrival_node {
    struct Arrival_node *prev, *next; /* Elementos anterior y siguiente */
    arrival *data; /* Dato de nodo, de tipo arraval */
} arrival_node;


/**
 * Crea un nuevo nodo de lista de horarios de llegada
 *
 * @param data: apuntador a la estructura de horarios de llegada
 * @return un apuntador al nuevo nodo de lista
 */
arrival_node *new_arrival_list();


/**
 * Inserta un nuevo nodo de horarios de llegada en la lista
 *
 * @param list: apuntador a la lista de horarios de llegada
 * @param data: apuntador a la estructura de horarios de llegada
 * @return 0 si la insercion fue exitosa, 1 en caso contrario
 */
u_int8_t push_arrival_list(arrival_node **list, arrival *data);


/**
 * Elimina un nodo de la lista de horarios de llegada.
 *
 * @param list: apuntador a la lista de horarios de llegada
 * @param data: Apuntador al nodo a eliminar.
 * @return 0 si la eliminacion fue exitosa, 1 en caso contrario.
 */
u_int8_t pop_arrival_list(arrival_node **list, arrival_node *del);


/*
 * Libera la memoria de la lista de horarios de llegada
 *
 * @param list: apuntador a la lista de horarios de llegada
 */
void destroy_arrival_list(arrival_node **list);

#endif
