#ifndef __bus_stop_H__
#define __bus_stop_H__

#include "arrival_list.h"

/**
 * Estructura de la parada de autobuses (rutas, tiempo del recorrido y 
 * horarios asociados) del transporte USB
 */
typedef struct Bus_stop{
    char cod[4]; /* codigo de la rura */
    char route_name[50]; /*nombre largo de la ruta */
    int recorr; /*Recorrido de la ruta en minutos */
    arrival_node *arrivals; /* Lista con horarios asociados de la parada de la ruta */
} stop;


/*
 * Crea una structura de parada de autobuses
 *
 * @param cod: puntero a char con el codigo de la parada
 * @param route_name: puntero a char con el nombre de la parada
 * @param recorr: Duracion del recorrido entre la universidad y la parada
 * @return Un apuntador a stop si la creacion fue exitosa.
 *         Null en caso contrario.
 */
stop* new_stop(char cod[4], char route_name[50], int recorr);

#endif
