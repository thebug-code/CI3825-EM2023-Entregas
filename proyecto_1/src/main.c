#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "schedule_list.h"
#include "stop_list.h"
#include "utils.h"

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) {
    /* Lee los datos de entrada y los guarda en las listas */
    svc_node *svc_list = new_service_list();
    stop_node *stop_list = new_stop_list();
    float min_duration = read_input(argc, argv, &svc_list, &stop_list);

    /* Cuenta el numero de rutas */
    int num_routes = count_routes(svc_list);

    /* Arreglo para almacenar los id's de los procesos hijos */
    pid_t *child_pids = malloc(num_routes * sizeof(pid_t));

    /* Inicializa el arreglo de pipes */
    int **pipefd = initialize_pipes(num_routes);

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
            close(pipefd[i][READ_END]); /* Cerrar el extremo de lectura no utilizado */
            char message[100];
            sprintf(message, "Hola, soy el proceso hijo %d", i);
            write(pipefd[i][WRITE_END], message, sizeof(message));
            exit(EXIT_SUCCESS);
        }
    }

    /* Cerrar los extremos de escritura de todas las tuberías en el proceso padre */
    for (i = 0; i < num_routes; i++)
        close(pipefd[i][WRITE_END]);

    /* Leer los mensajes enviados por los procesos hijos */
    for (i = 0; i < num_routes; i++) {
        char buffer[100];
        read(pipefd[i][READ_END], buffer, sizeof(buffer));
        printf("Mensaje recibido del proceso hijo %d: %s\n", i, buffer);
    }

    /* Esperar a que terminen todos los procesos hijos */
    for (i = 0; i < num_routes; i++) {
        int status;
        waitpid(child_pids[i], &status, 0);
    }

    
    return 0;
}
