#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "schedule_list.h"
#include "stop_list.h"
#include "utils.h"

#define READ_END 0
#define WRITE_END 1
#define MESSAGE_SIZE 256

/* Estructura para almacenar los argumentos de la función simulate_bus_route */
typedef struct Arg_struct {
    int bus_id; /* Identificador del autobús */ 
    int *fd; /* Arreglo de descriptores de archivo */
    pthread_mutex_t *mutex; /* Apuntador al mutex compartido */
    svc_node *arg1; /* Apuntador a la cabeza de la lista de servicios */
    stop_node *arg2; /* Apuntador a la cabeza de la lista de paradas */
} args;

/* 
 * Crea una estructura args con los argumentos de la función 
 * simulate_bus_route. Si hay un error, termina el programa.
 *
 * @param bus_id Identificador del autobús
 * @param fd Arreglo de descriptores de archivo
 * @param mutex Apuntador al mutex compartido
 * @param svc_list Apuntador a la cabeza de la lista de servicios
 * @param stop_list Apuntador a la cabeza de la lista de paradas
 * @return Apuntador a la estructura args
 */
args *create_new_args(int bus_id, 
                      int *fd, 
                      pthread_mutex_t *mutex,
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
    new_args->mutex = mutex;
    new_args->arg1 = svc_list;
    new_args->arg2 = stop_list;

    return new_args;
}


/*
 * Simula el recorrido de un autobús por una ruta.
 *
 * @param arg Apuntador a la estructura args
 */
void *simulate_bus_route(void *arg) {
    args *info = (args *) arg;
    int bus_id = info->bus_id;
    int *fd = info->fd;
    pthread_mutex_t *mutex = info->mutex;

    pthread_mutex_lock(mutex); /* Bloquea el mutex */
    close(fd[READ_END]); /* Cierra el extremo de lectura no utilizado */

    /* Escribe un mensaje en el pipe */
    char message[MESSAGE_SIZE];
    sprintf(message, "Hola, soy el hilo %lu\n", pthread_self());
    write(fd[WRITE_END], message, sizeof(message));

    pthread_mutex_unlock(mutex); /* Desbloquea el mutex */

    pthread_exit(NULL);
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

    /* Inicializa el mutex para sincronizar escritura en el pipe */
    pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    if (pthread_mutex_init(mutex, NULL)) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    /* Variables para el manejo de tiempo de la simulación */
    int sim_time = 28800; /* 8 horas de servicio en segundos */
    int sim_counter = 0; /* contador de tiempo de la simulación */
    time_t start_time;
    struct tm *start_time_info;
    
    start_time = time(NULL); /* Se obtiene la hora actual */
    start_time_info = localtime(&start_time); /* Se convierte la hora actual a una estructura tm */
    
    /* Inicializa la hora de inicio del servicio a las 6:00 */
    start_time_info->tm_hour = 6;
    start_time_info->tm_min = 0;
    start_time_info->tm_sec = 0;
    start_time = mktime(start_time_info); /* Convierte la hora de inicio del servicio a time_t */

    /* Crea los procesos hijos */
    int i;
    for (i = 0; i < num_routes; i++) {
        child_pids[i] = fork();

        if (child_pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (!child_pids[i]) {
            /* i-esimo proceso hijo FALTA LOS FREE */

            /* Crear el hilo y ejecutar la función simulate_bus_route */
            pthread_t bus_thread_id;
            if (pthread_create(&bus_thread_id, NULL, simulate_bus_route, 
                create_new_args(i, pipefd[i], mutex, svc_list, stop_list))) {
                perror("pthread_create");
                exit(EXIT_FAILURE);
            }

            pthread_mutex_lock(mutex); /* Bloquear el mutex */
            close(pipefd[i][READ_END]); /* Cerrar el extremo de lectura no utilizado */

            /* Escribir un mensaje en el pipe */ 
            char message[MESSAGE_SIZE];
            sprintf(message, "Hola, soy el proceso hijo %d", i);
            write(pipefd[i][WRITE_END], message, sizeof(message));

            pthread_mutex_unlock(mutex); /* Desbloquear el mutex */

            /* Espera a que termine el hilo */
            if (pthread_join(bus_thread_id, NULL)) {
                perror("pthread_join");
                exit(EXIT_FAILURE);
            }

            /* Salir del proceso hijo */
            exit(EXIT_SUCCESS);
        } else {
            /* Proceso padre */
            
            pthread_mutex_lock(mutex); /* Bloquear el mutex */
            close(pipefd[i][WRITE_END]); /* Cerrar el extremo de escritura no utilizado */

            /* Leer el mensaje enviado por el proceso hijo */
            char buffer[MESSAGE_SIZE];
            int n;
            while ((n = read(pipefd[i][READ_END], buffer, sizeof(buffer))) > 0)
                printf("Mensaje recibido del proceso hijo %d: %s\n", i, buffer);

            /* Esperar a que termine el i-esimo proceso hijo */
            int status;
            waitpid(child_pids[i], &status, 0);
        }

        svc_list = svc_list->next;
        stop_list = stop_list->next;
    }

    return 0;
}
