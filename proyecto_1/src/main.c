#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "schedule_list.h"
#include "stop_list.h"
#include "utils.h"

#define READ_END 0
#define WRITE_END 1
#define MESSAGE_SIZE 256


int nanosleep(const struct timespec *req, struct timespec *rem);


/* Estructura para almacenar los argumentos de la función simulate_bus_route */
typedef struct Arg_struct {
    int bus_id; /* Identificador del autobús */ 
    int *fd; /* Arreglo de descriptores de archivo */
    svc_node *arg1; /* Apuntador a la cabeza de la lista de servicios */
    stop_node *arg2; /* Apuntador a la cabeza de la lista de paradas */
} args;


/* 
 * Crea una estructura args con los argumentos de la función 
 * simulate_bus_route. Si hay un error, termina el programa.
 *
 * @param bus_id Identificador del autobús
 * @param fd Arreglo de descriptores de archivo
 * @param svc_list Apuntador a la cabeza de la lista de servicios
 * @param stop_list Apuntador a la cabeza de la lista de paradas
 * @return Apuntador a la estructura args
 */
args *create_new_args(int bus_id, 
                      int *fd, 
                      svc_node *svc_list,
                      stop_node *stop_list)
{
    args *new_args = (args *)malloc(sizeof(args));

    if (!new_args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_args->bus_id = bus_id;
    new_args->fd = fd;
    new_args->arg1 = svc_list;
    new_args->arg2 = stop_list;

    return new_args;
}


/*
 * Crea una estructura tm con la hora actual y la modifica
 * para que tenga la hora, minuto y segundo especificados.
 *
 * @param hour Hora
 * @param min Minuto
 * @param sec Segundo
 * @return Estructura tm con la hora especificada
 */
time_t create_hour(int hour, int min, int sec) {
    time_t t;
    struct tm *time_info;

    t = time(NULL);
    time_info = localtime(&t);

    time_info->tm_hour = hour;
    time_info->tm_min = min;
    time_info->tm_sec = sec;
    t = mktime(time_info);

    return t;
}


/*
 * Simula el recorrido de un autobús por una ruta.
 *
 * @param arg Apuntador a la estructura args
 */
void *simulate_bus_route(void *arg) {
    args *info = (args *) arg;
    char message[MESSAGE_SIZE];
    int bus_id = info->bus_id;
    int *fd = info->fd;

    close(fd[READ_END]); /* Cierra el extremo de lectura no utilizado */

    /* Escribe un mensaje en el pipe */
    sprintf(message, "Bus %d: Hello world!", bus_id);
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
time_t get_current_time(time_t start_time, size_t sim_counter) {
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
    svc_node *svc_list = new_service_list();
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
    size_t sim_time = 480; /* 8 horas de servicio en minutos */
    size_t sim_counter = 0; /* contador de tiempo (en mins) de la simulación */
    
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
            /* Puntero a la lista de horarios de los k-esimo autobuses */
            sched_node *sched_list = svc_list->data->scheds;

            /* Inicio de la simulacion */
            while (sim_counter < sim_time) {
                struct timespec ts; /* Estructura para el nanosleep */
                time_t current_time; /* Tiempo actual de la simulación */
                char message[MESSAGE_SIZE]; /* Mensaje a escribir en el pipe */

                /* Obtiene el tiempo actual de la simulación */
                current_time = get_current_time(start_time, sim_counter);
                if (!difftime(current_time, sched_list->data->time)) {
                    /* Si el tiempo actual es igual al tiempo de salida del autobús */
                    /* Crea un hilo para simular el recorrido del autobús */
                    pthread_t bus_thread_id;
                    if (pthread_create(&bus_thread_id, NULL, simulate_bus_route, 
                        create_new_args(j, pipefd[i], svc_list, stop_list))) {
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
                    sched_list = sched_list->next;
                    j++;
                }

                /* Simula el paso del tiempo */
                ts.tv_sec = 0;
                ts.tv_nsec = min_duration * 1000; /* min_duration en microsegundos */
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
