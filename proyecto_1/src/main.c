#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "utils.h"
#include "simula_bus.h"

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

    /* Inicializa el mutex para proteger el acceso a la lista de
     * llegadas de pasajeros */
    pthread_mutex_t *mutex_arrivals = malloc(sizeof(pthread_mutex_t));
    if (pthread_mutex_init(mutex_arrivals, NULL)) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    /* Variables para el manejo de tiempo de la simulación */
    int sim_time = 480; /* 8 horas de servicio en minutos */
    int sim_counter = 0; /* contador de tiempo (en mins) de la simulación */
    
    /* Inicializa la hora de inicio del servicio a las 4:10 */
    time_t start_time = create_hour(5, 20, 0);

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
                time_t current_time; /* Tiempo actual de la simulación */
                char message[MESSAGE_SIZE]; /* Mensaje a escribir en el pipe */

                /* Obtiene el tiempo actual de la simulación */
                current_time = get_current_time(start_time, sim_counter);
                printf("current_time: %s", ctime(&current_time));
                if (!difftime(current_time, sched_k->data->time)) {
                    /* Si el tiempo actual es igual al tiempo de salida
                     * del autobús crea un hilo para simular el recorrido
                     * del autobús */
                    args *bus_info = create_new_args(j, start_time,        
                        svc_list->data->route, min_duration, &sim_counter,
                        sched_k->data->cap, stop_list->data->recorr, &arrival_k,
                        mutex_arrivals, pipefd[i]);                     
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
                sleep_for(min_duration, 0);

                /* Incrementa el contador de tiempo de la simulación */
                sim_counter++;
            }
            printf("Terminó la simulación %d\n", sim_counter);
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
