/* Implementaciones de funciones utiles para transporte USB
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "service_list.h"

/*
 * Carga la caracterizacion del servicio en una lista enlazada
 *
 * @param filename: ruta del archivo con la caracterizacioin del servicio
 * @param svc_charac_list: Puntero a la cabeza de la lista donde se cargara
 * la caracterizacion del servicio
 * @return 1 si la carga fue exitosa de lo contrario 0.
 */
u_int8_t ul_svc_charac(char filename[], sched_node** scheds) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int hour;
    int min;
    int cap;
    svc *new_service; /* Lista de servicios */
    svc_node *svc_list; /* Nodo de la lista de servicios */
    sched *new_schedule; /* Lista de horarios */

    fp = fopen(filename, "r");

    if (!fp)
        return 0;

    /* Inicializa la lista con los servicios */
    svc_list = new_service_list(); /* FALTA VERIFICAR */

    /* Leer archivo linea por linea */
    while ((read = getline(&line, &len, fp)) != -1) {
        /* printf("Retrieved line of length %zu:\n", read); */
        /* printf("%s", line); */
        char *route = strtok(line, " ");

        while(line) {
            if (!strcmp(route, line)) {
                /* Crea un nuevo servicio */
                new_service = new_svc(route); /* FALTA VERIFICAR */
                /* Lo inserta en la lista de servicios */
                push_service_list(&svc_list, new_service); /* FALTA VERIFICAR */
            }
            else {
                /* Extrae la hora, minuto y capacidad del 
                 * j-enesimo horario */
                    hour = atoi(strtok(line, ":"));
                    min = atoi(strtok(NULL, "("));
                    cap = atoi(strtok(NULL, ") "));
                    
                    /* Crea un nuevo horario */
                    new_schedule = new_sched(hour, min, cap);

                    /* Lo inserta en lista de horarios de la 
                     * ruta asociada */
                    push_sched_list(&(svc_list->data->scheds), new_schedule);
            }

            line = strtok(NULL, "");
            if (strcmp("\n", line)) line = NULL;
        }
    }

    fclose(fp);

    
    if (line)
        free(line);
    return 1;   
}
