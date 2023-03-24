#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "utils.h"

#define READ_END 0
#define WRITE_END 1
#define MESSAGE_SIZE 256


int nanosleep(const struct timespec *req, struct timespec *rem);


/* Estructura para almacenar los argumentos de la función simulate_bus_route */
typedef struct Arg_struct {
    int bus_id; /* Identificador del autobús */
    char *route_name; /* Nombre de la ruta */
    int min_duration; /* Duración de un minuto en la simulación */
    int counter_time; /* Contador de tiempo de la simulación */
    int capacity; /* Capacidad del autobús */
    int duration; /* Duración del recorrido */
    arrival_node *arrivals; /* Lista con los horarios de llegada de las personas */
    int *fd; /* Arreglo de descriptores de archivo */
} args;


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
                      char *route_name,
                      int min_duration,
                      int counter_time,
                      int capacity,
                      int duration,
                      arrival_node *arrivals,
                      int *fd)
{
    args *new_args = (args *)malloc(sizeof(args));

    if (!new_args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_args->bus_id = bus_id;
    new_args->route_name = route_name;
    new_args->min_duration = min_duration;
    new_args->counter_time = counter_time;
    new_args->capacity = capacity;
    new_args->duration = duration;
    new_args->arrivals = arrivals;
    new_args->fd = fd;

    return new_args;
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
    char *route_name = info->route_name;
    int min_duration = info->min_duration;
    int counter_time = info->counter_time;
    int capacity = info->capacity;
    int duration = info->duration;
    arrival_node *arrivals = info->arrivals;
    int *fd = info->fd;

    int recorr = 0; /* Tiempo de recorrido del autobús */
    int min_duration_n; /* Duración de un minuto en nanosegundos */
    int sim_duration_seg; /* Duración de la simulación en segundos */
    int sim_duration_n; /* Duración de la simulación en nanosegundos */
    struct timespec ts; /* Estructura para simular el paso del tiempo */

    close(fd[READ_END]); /* Cierra el extremo de lectura no utilizado */

    /* Escribe un mensaje en el pipe */
    sprintf(message, "Hola soy el autobus %d y estoy yendo a la parada %s",
            bus_id, route_name);
    write(fd[WRITE_END], message, sizeof(message));
    

    /* Simula el recorrido de ida hacia la parada */
    while (recorr < duration) {
        /* Simula el paso del tiempo */
        ts.tv_sec = min_duration;
        ts.tv_nsec = 0;
        nanosleep(&ts, NULL);
        
        /* Incrementa el contador de tiempo */
        recorr++;
        counter_time++;
    }

    /* Escribe un mensaje en el pipe */
    sprintf(message, "Hola soy el autobus %d y ya llegue a la parada %s",
            bus_id, route_name);
    write(fd[WRITE_END], message, sizeof(message));

    /* Carga a los pasajeros */
    
    min_duration_n = min_duration * 1000000000;
    sim_duration_seg = 10 * min_duration;
    sim_duration_n =  (10 * min_duration - sim_duration_seg) * min_duration_n; 

    ts.tv_sec = sim_duration_seg; 
    ts.tv_nsec = sim_duration_n;
    nanosleep(&ts, NULL);

    counter_time += 10;

    /* Simula el recorrido de regreso hacia la universidad */
    while (recorr > 0) {
        /* Simula el paso del tiempo */
        ts.tv_sec = min_duration;
        ts.tv_nsec = 0;
        nanosleep(&ts, NULL);
        
        /* Incrementa el contador de tiempo */
        recorr--;
        counter_time++;
    }

    /* Escribe un mensaje en el pipe */
    sprintf(message, "Hola soy el autobus %d y ya regrese a la universidad", bus_id);
    write(fd[WRITE_END], message, sizeof(message));

    pthread_exit(NULL);
}


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


int main(int argc, char *argv[]) {
    /* Lee los datos de entrada y los guarda en las listas */
    svc_charac_node *svc_list = new_svc_charac_list();
    stop_node *stop_list = new_stop_list();
    float min_duration = read_input(argc, argv, &svc_list, &stop_list);
    /* Tiempo en seguntos que dura un minuto de la simulación */

    /* Cuenta el numero de rutas */
    int num_routes = 1;
    /*int num_routes = count_routes(svc_list);*/

    /* Arreglo para almacenar los id's de los procesos hijos */
    pid_t *child_pids = malloc(num_routes * sizeof(pid_t));

    /* Inicializa el arreglo de pipes */
    int **pipefd = initialize_pipes(num_routes);

    /* Variables para el manejo de tiempo de la simulación */
    int sim_time = 480; /* 8 horas de servicio en minutos */
    int sim_counter = 0; /* contador de tiempo (en mins) de la simulación */
    
    /* Inicializa la hora de inicio del servicio a las 4:10 */
    time_t start_time = create_hour(4, 10, 0);

    /* Crea los procesos hijos */
    int i;
    for (i = 0; i < num_routes; i++) {
        child_pids[i] = fork();

        if (child_pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (!child_pids[i]) {
            /* i-esimo proceso hijo */

            /* id del autobús */
            int j = 0;
            /* Puntero al nodo con el horario del k-esimo bus de la i-esima ruta */
            bus_dep_time_node *sched_k = svc_list->data->scheds;
            /* Puntero al nodo con la inf de llegada de la parada de la i-esima ruta */
            arrival_node *arrival_k = stop_list->data->arrivals;

            /* Inicio de la simulacion */
            while (sim_counter < sim_time) {
                struct timespec ts; /* Estructura para el nanosleep */
                time_t current_time; /* Tiempo actual de la simulación */
                char message[MESSAGE_SIZE]; /* Mensaje a escribir en el pipe */

                /* Obtiene el tiempo actual de la simulación */
                current_time = get_current_time(start_time, sim_counter);
                if (!difftime(current_time, sched_k->data->time)) {
                    /* Si el tiempo actual es igual al tiempo de salida del autobús */
                    /* Crea un hilo para simular el recorrido del autobús */
                    args *bus_info = create_new_args(j, svc_list->data->route,        
                        min_duration, sim_counter, sched_k->data->cap,
                        stop_list->data->recorr, arrival_k, pipefd[i]);                     
                    pthread_t bus_thread_id;
                    if (pthread_create(&bus_thread_id, NULL, simulate_bus_route, 
                        (void *) bus_info)) {
                        perror("pthread_create");
                        exit(EXIT_FAILURE);
                    }

                    /* Cerrar el extremo de lectura no utilizado */
                    close(pipefd[i][READ_END]); 

                    /* Escribir un mensaje en el pipe */
                    sprintf(message, "Hola, soy la ruta %s", svc_list->data->route);
                    write(pipefd[i][WRITE_END], message, sizeof(message));

                    /* Espera a que termine el hilo */
                    if (pthread_join(bus_thread_id, NULL)) {
                        perror("pthread_join");
                        exit(EXIT_FAILURE);
                    }

                    /* Avanza al siguiente horario */
                    sched_k = sched_k->next;
                    j++;
                }

                /* Simula el paso del tiempo */
                ts.tv_sec = min_duration;
                ts.tv_nsec = 0; 
                nanosleep(&ts, NULL);
                
                /* Incrementa el contador de tiempo de la simulación */
                sim_counter++;
            }
            /* Salir del proceso hijo */
            exit(EXIT_SUCCESS);
        } 
        else {
            /* Proceso padre */
            int status;
            char buffer[MESSAGE_SIZE];
            int n;

            /* Cerrar el extremo de escritura no utilizado */
            close(pipefd[i][WRITE_END]); 

            /* Leer el mensaje enviado por el proceso hijo */
            while ((n = read(pipefd[i][READ_END], buffer, sizeof(buffer))) > 0)
                printf("Mensaje recibido del proceso hijo %d: %s\n", i, buffer);

            /* Esperar a que termine el i-esimo proceso hijo */
            waitpid(child_pids[i], &status, 0);

            svc_list = svc_list->next;
            stop_list = stop_list->next;
        }
    }
    return 0;
}
