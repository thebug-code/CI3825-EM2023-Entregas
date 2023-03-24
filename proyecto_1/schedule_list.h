#ifndef __svc_charac_list_H__
#define __svc_charac_list_H__

/*
 * Incluye la libreria stdint.h para poder usar el tipo de dato uint8_t.
 */
#include <stdint.h>

#include "svc_charac_list.h"

/**
 * Estructura de nodo para lista circular doblemente enlazada
 * de caracterizacion del servicio.
 */
typedef struct service_characterization_list {
    struct service_characterization_list *prev, *next; /* Elementos anterior y siguiente */
    svc_charac *data; /* Dato de nodo, de tipo svc_charac */
} svc_charac_node;


/*
 * Crea una lista doblemente enlazada de caracterizacion del servicio
 * sin elementos.
 *
 * @return Un apuntador a la cabeza de la lista si la creacion fue exitosa.
 * De lo contrario NULL.
 */
svc_charac_node *new_svc_charac_list();


/*
 * Añade un nodo de caracterizacion del servicio a la lista.
 *
 * @param list: Apuntador a la direccion de la cabeza de la lista.
 * @param data: Dato a almacenar en el nodo, de tipo svc_charac.
 * @return 1 si la operación fue exitosa. De lo contrario 0.
 */
u_int8_t push_svc_charac_list(svc_charac_node **list, svc_charac *data);


/*
 * Imprime un nodo de la lista de caracterizacion del servicio en un
 * formato legible.
 *
 * @param node: apuntador al nodo de la lista de caracterizacion del
 * servicio.
 */
void print_svc_charac_node(svc_charac_node *node);


/*
 * Libera la memoria de la lista de caracterizacion del servicio.
 *
 * @param list: apuntador a la lista de caracterizacion del servicio.
 */
void destroy_svc_charac_list(svc_charac_node **list);

#endif
