#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "utils.h"
#include "simula_bus.h"

int nanosleep(const struct timespec *req, struct timespec *rem);


/*
 * Obtiene el tiempo actual de la simulación.
 *
 * @param start_time Tiempo de inicio de la simulación
 * @param sim_counter Contador de tiempo de la simulación
 * @return Tiempo actual de la simulación
 */
time_t get_current_time(time_t start_time, int sim_counter) {
    struct tm *current_time;
    time_t current_time_t;

    /* Convertir start_time a struct tm */
    current_time = localtime(&start_time);

    current_time->tm_min += sim_counter;

    /* Convertir de vuelta a time_t */
    current_time_t = mktime(current_time);

    return current_time_t;
}

/* 
 * Crea una estructura args con los argumentos de la función 
 * simulate_bus_route. Si hay un error, termina el programa.
 *
 * @param bus_id Identificador del autobús
 * @param route_name Nombre de la ruta
 * @param min_duration Duración de un minuto en la simulación
 * @param counter_time Contador de tiempo de la simulación
 * @param capacity Capacidad del autobús
 * @param duration Duración del recorrido
 * @param arrivals Lista con los horarios de llegada de las personas
 * @param fd Arreglo de descriptores de archivo
 * @return Estructura args con los argumentos de la función
 */
args *create_new_args(int bus_id, 
                      time_t start_time,
                      char *route_name,
                      int min_duration,
                      int *counter_time,
                      int capacity,
                      int duration,
                      arrival_node **arrivals,
                      pthread_mutex_t *mutex_arrivals,
                      int *fd)
{
    args *new_args = (args *)malloc(sizeof(args));

    if (!new_args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_args->bus_id = bus_id;
    new_args->start_time = start_time;
    new_args->route_name = route_name;
    new_args->min_duration = min_duration;
    new_args->counter_time = counter_time;
    new_args->capacity = capacity;
    new_args->duration = duration;
    new_args->arrivals = arrivals;
    new_args->mutex_arrivals = mutex_arrivals;
    new_args->fd = fd;

    return new_args;
}


/*
 * Duerme el proceso por un tiempo determinado.
 *
 * @param sec Segundos a dormir
 * @param nsec Nanosegundos a dormir
 */
void sleep_for(int sec, int nsec) {
    struct timespec ts;

    /* Simula el paso del tiempo */
    ts.tv_sec = sec;
    ts.tv_nsec = nsec;
    nanosleep(&ts, NULL);

    return;
}

    
/*
 * Simula el recorrido de un autobús por una ruta.
 *
 * @param arg Apuntador a la estructura args
 */
void *simulate_bus_route(void *arg) {
    args *info = (args *) arg; /* Obtiene los argumentos */
    
    /* Extrae los argumentos de la estructura args */
    char message[MESSAGE_SIZE];
    int bus_id = info->bus_id;
    time_t start_time = info->start_time;
    char *route_name = info->route_name;
    int min_duration = info->min_duration;
    int *counter_time = info->counter_time;
    int capacity = info->capacity;
    int duration = info->duration;
    arrival_node *arrivals = *info->arrivals;
    pthread_mutex_t *mutex_arrivals = info->mutex_arrivals;
    int *fd = info->fd;

    int recorr = 0; /* Tiempo de recorrido del autobús */
    int min_duration_n; /* Duración de un minuto en nanosegundos */
    int sim_duration_seg; /* Duración de la simulación en segundos */
    int sim_duration_n; /* Duración de la simulación en nanosegundos */
    time_t current_time; /* Tiempo actual */


    close(fd[READ_END]); /* Cierra el extremo de lectura no utilizado */

    /* Escribe un mensaje en el pipe */
    sprintf(message, "Hola soy el autobus %d y estoy yendo a la parada %s",
        bus_id, route_name);
    write(fd[WRITE_END], message, sizeof(message));

    /* Simula el recorrido de ida hacia la parada */
    while (recorr < duration) {
        /* Simula el paso del tiempo */
        sleep_for(min_duration, 0);
        
        /* Incrementa el contador de tiempo */
        recorr++;
        *(counter_time) += 1;
    }
    
    time_t t = get_current_time(start_time, *counter_time);
    struct tm * ct_tm = localtime(&t);

    /* Escribe un mensaje en el pipe */
    sprintf(message, "Hola soy el autobus %d y ya llegue a la parada %s a las %d:%d",
        bus_id, route_name, ct_tm->tm_hour, ct_tm->tm_min);
    write(fd[WRITE_END], message, sizeof(message));
    
    min_duration_n = min_duration * 1000000000;
    sim_duration_seg = 10 * min_duration;
    sim_duration_n = (10 * min_duration - sim_duration_seg) * min_duration_n; 
   
    /* Bloquear el mutex */
    pthread_mutex_lock(mutex_arrivals);

    /* Espera 10 minutos para cargar a los pasajeros */
    sleep_for(sim_duration_seg, sim_duration_n);
    /* Incrementa el contador de tiempo */
    *(counter_time) += 10;
    /* Obtiene la hora actual */
    current_time = get_current_time(start_time, *counter_time);

    /* Recorre la lista de horarios de llegada */
    while (arrivals) {
        /* Obtiene el i-ésimo elemento de la lista */
        arrival *i_th_arrival = arrivals->data;
        /* Calcula la diferencia entre la hora actual y la hora de llegada */
        double diff = difftime(current_time, i_th_arrival->hour);
        
        /* Si la hora de llegada del autobús + 10 minutos es mayor o igual a la hora
         * de llegada de las personas, carga a los pasajeros */
        if (diff >= 0) {
            if (i_th_arrival->n_people > capacity) {
                /* La cantidad de pasajeros es mayor que la capacidad del autobús
                 * por lo que el autobús se llena */
                i_th_arrival->n_people -= capacity;

                /* Escribe un mensaje en el pipe */

                t = get_current_time(start_time, *counter_time);
                ct_tm = localtime(&t);
                sprintf(message, "Hola soy el autobus %d, llevo %d pasajeros y voy de regreso a la universidad a las %d:%d",
                    bus_id, capacity, ct_tm->tm_hour, ct_tm->tm_min);
                write(fd[WRITE_END], message, sizeof(message));

                /* El autobús está lleno */
                capacity = 0;
                break;
            } else {
                arrival_node *tmp = arrivals; /* Nodo temporal */
                arrivals = arrivals->next; /* Avanza al siguiente horario */
                /* Elimina el nodo de la lista */
                if(!pop_arrival_list(info->arrivals, tmp)) {
                    perror("pop_arrival_list");
                    exit(EXIT_FAILURE);
                }
                
                /* Escribe un mensaje en el pipe */
                t = get_current_time(start_time, *counter_time);
                ct_tm = localtime(&t);
                sprintf(message, "Hola soy el autobus %d, llevo %d pasajeros y voy de regreso a la universidad a las %d:%d",
                    bus_id, i_th_arrival->n_people, ct_tm->tm_hour, ct_tm->tm_min);
                write(fd[WRITE_END], message, sizeof(message));

                i_th_arrival->n_people = 0;
            }
        } else {
            /* Si la hora de llegada del autobús + 10 minutos es menor a la hora
             * de llegada de las personas, no carga a los pasajeros */
            break;
        }
    }

    /* Desbloquea el mutex */
    pthread_mutex_unlock(mutex_arrivals);

    /* Simula el recorrido de regreso hacia la universidad */
    while (recorr > 0) {
        /* Simula el paso del tiempo */
        sleep_for(min_duration, 0);

        /* Incrementa el contador de tiempo */
        recorr--;
        *(counter_time) += 1;
    }

    /* Escribe un mensaje en el pipe */
    t = get_current_time(start_time, *counter_time);
    ct_tm = localtime(&t);
    sprintf(message, "Hola soy el autobus %d y ya regrese a la universidad a las %d:%d",
        bus_id, ct_tm->tm_hour, ct_tm->tm_min);
    write(fd[WRITE_END], message, sizeof(message));

    pthread_exit(NULL);
}