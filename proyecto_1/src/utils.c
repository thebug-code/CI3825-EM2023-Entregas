/* Implementaciones de funciones utiles para transporte USB
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "utils.h"


/*
 * Carga la caracterizacion del servicio en una lista enlazada
 *
 * @param filename: ruta del archivo con la caracterizacioin del servicio
 * @return Puntero a la cabeza de la lista con los servicios si la operacion
 * se realizo exito. NULL en caso contrario
 */
svc_charac_node *ul_svc_charac(char filename[]) {
    FILE *fp;                /* Apuntador a archivo */
    char *line = NULL;       /* Puntero a lineas del archivo */
    size_t len = 0;          /* Numero de caracteres de cada linea */
    int first_time = 1;
    ssize_t read;
    svc_charac_node *ptr_svc_list_h; /* Ptr a la cabeza de la lista de svcs */
    svc_charac_node *ptr_svc_list;   /* Ptr a nodos de la lista de svcs */

    fp = fopen(filename, "r");
    if (!fp) {
        perror("no such file");
	return NULL;
    }

    /* Inicializa la lista con los servicios */
    ptr_svc_list_h = new_svc_charac_list();
    if (!ptr_svc_list_h) {
        perror("no memory");
        exit(EXIT_FAILURE);
    }
    
    ptr_svc_list = ptr_svc_list_h;

    /* Leer archivo linea por linea */
    while ((read = getline(&line, &len, fp)) != -1) {
        /* printf("Retrieved line of length %zu:\n", read); */
        /* printf("%s", line); */
        char *route = strtok(line, " ");

        while(line) {
            if (!strcmp(route, line)) {
                /* Crea un nuevo servicio */
                svc_charac *new_svc = new_svc_charac(route);
                if (!new_svc) {
                    perror("no memory");
                    exit(EXIT_FAILURE);
                }

                /* Lo inserta en la lista de servicios */
                if(!push_svc_charac_list(&ptr_svc_list_h, new_svc)) {
                    perror("push error");
                    exit(EXIT_FAILURE);
                }
                
                /* Verifica si se "mueve" el puntero al siguiente nodo */
                if (!first_time) ptr_svc_list = ptr_svc_list->next;
            }
            else {
                /* Extrae la hora, minuto y capacidad del 
                 * j-enesimo horario */
                if (strcmp("\n", line)) {
                    int hour = atoi(strtok(line, ":"));
                    int min = atoi(strtok(NULL, "("));
                    int cap = atoi(strtok(NULL, ") "));

                    /* Crea un nuevo horario */
                    bus_dep_time *new_sched = \
                        new_bus_dep_time(hour, min, cap);
                    if (!new_sched) {
                        perror("no memory");
                        exit(EXIT_FAILURE);
                    }

                    /* Lo inserta en lista de horarios de la 
                    * ruta asociada */
                    if (!push_bus_dep_time_list(&(ptr_svc_list->data->scheds),
                        new_sched)){
                        perror("push error");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            line = strtok(NULL, "");
        }

        first_time = 0;
    }

    fclose(fp);

    if (line)
        free(line);

    return ptr_svc_list_h; 
}


/*
 * Carga el archivo de caracterizacion de la carga al sistema 
 * en un arreglo de tipo stop
 *
 * @param filename: ruta del archivo con la caracterizacion de la carga
 * @return un apuntador al arreglo de tipo stop si el fichero existe
 */
stop_node *ul_charac_ld_sys(char filename[]) {
    FILE *file = fopen(filename, "r");
    char buffer[MAX_BUFFER];
    char cod[4];
    char route_name[50];
    int recorr;
    int people;
    int i = 0;
    int j = 0;
    stop *n_stop;
    stop_node *stop_list;
    arrival *arriv;
    
    if (!file) {
        perror("no such file");
        return NULL;
    } 
    else {
        /* Inicializa la lista con los servicios */
        stop_list = new_stop_list();
        fgets(buffer, MAX_BUFFER, file);
        strtok(buffer, "\n");
        strtok(buffer, ", ");
    
        while (i < 3) {
            if(i == 2) 
                j = atoi(strtok(NULL, ", "));
            else
                strtok(NULL, ", ");
            i++;
        }
    
        i = j + 8;
        while (fgets(buffer, MAX_BUFFER, file)) {
            strtok(buffer, "\n");
    
            strcpy(cod, strtok(buffer, ","));
            strncpy(route_name, &strtok(NULL, ",")[1], 50);
            recorr = atoi(strtok(NULL, ", :"))*3600 + atoi(strtok(NULL, ", :"))*60;
    
            n_stop = new_stop(cod, route_name, recorr);
    
            while (j < i) {
                people = atoi(strtok(NULL, ", "));
                arriv = new_arrival(j, people);
                push_arrival_list(&(n_stop->arrivals), arriv);
                j++;
            }
    
            if(!push_stop_list(&stop_list, n_stop)){
                perror("push error");
                exit(EXIT_FAILURE);
            }
        
            j = j - 8;
        }
    
        fclose(file);
        return stop_list;
    }
}


/*
 * Verifica que un argumento de opcion no es otra opcion. 
 * En caso afirmativo termina la ejecuacion del programa.
 *
 * @param optarg: Variable externa que es el apuntador a los
 * argumentos de las opciones.
 */
void check_opt_arg(char* optarg) {
    if (optarg && optarg[0] == '-') {
        printf("./simutransusb: Option -s requires an argument.\n");
        printf(USAGE);
        exit(EXIT_FAILURE);
    }
    else 
        return;
}


/*
 * Lee y verifica los argumentos pasados por linea de comandos.
 * En caso de que haya un error muestra un mensaje con el error
 * y termina la ejecucion del programa.
 *
 * @param argc: Numero de argumentos de la linea de comandos
 * @param argv: Vector de argumentos de la linea de comandos
 * @param svc_list: puntero a la cabeza de la lista de servicios
 * @param stop_list: puntero a la cabeza de la lista de paradas
 * de autobuses
 * @return float tiempo que dura un minuto en la simulacion
 */
float read_input(int argc, char *argv[], svc_charac_node **svc_list, stop_node **stop_list)  {
    /* 
     * Variables para indicar las opciones 
     */
    int sflag = 0;
    int cflag = 0;
    int tflag = 0;

    /*
     * Punteros para argumentos de las opciones
     */
    char *svalue = NULL;
    char *cvalue = NULL;
    char *tvalue = NULL;

    int c;

    while ((c = getopt (argc, argv, ":s:c:t:")) != -1) {
        switch (c) {
            case 's':
                check_opt_arg(optarg);

                sflag = 1;
                svalue = optarg;
                break;
            case 'c':
                check_opt_arg(optarg);

                cflag = 1;
                cvalue = optarg;
                break;
            case 't':
                check_opt_arg(optarg);

                tflag = 1;
                tvalue = optarg;
                break;
            case '?':
                fprintf(stderr, "./simutransusb: Unknown option: %c\n", optopt);
		        printf(USAGE);
                exit(EXIT_FAILURE);
            case ':':
                fprintf(stderr, "./simutransusb: Option -%c requires an argument.\n", optopt);
		        printf(USAGE);
                exit(EXIT_FAILURE);
            default:
                abort ();
        }
    }
    
    /* Verifica que la opcion -s fue ingresada */
    if (!sflag) { 
        printf("./simutransusb: Option s is required.\n");
	printf(USAGE);
        exit(EXIT_FAILURE);
    }

   /*
    * Carga la caracterizacion del servicio en una lista enlazada
    */
    *svc_list = ul_svc_charac(svalue);

   /*
    * Carga la caracterizacion de carga del sistema en una lista
    * enlazada
    */
    if (!cflag)
        *stop_list = ul_charac_ld_sys("carga.csv");
    else
        *stop_list = ul_charac_ld_sys(cvalue);
    
    /* Verifica que la opcion -t fue ingresada y retorna el tiempo */
    if (!tflag) return 0.25;

    return atof(tvalue);
}


 /*
 * Crea una estructura de tipo time_t a partir de una hora, minuto y segundo
 * dados.
 *
 * @param hour: hora
 * @param min: minuto
 * @param sec: segundo
 * @return time_t con la hora, minuto y segundo dados
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
 * Cuenta el numero de rutas que hay en la lista de caracterizacion
 * del servicio.
 *
 * @param svc_list: Puntero a la cabeza de la lista de caracterizacion
 * del servicio.
 */
int count_routes(svc_charac_node *svc_list) {
    int cont = 0;

    while (svc_list) {
        cont++;
        svc_list = svc_list->next;
    }

    return cont;
}


/*
 * Crea un arreglo de n pipes. En caso de error termina la ejecucion
 * del programa.
 *
 * @param n: numero de pipes a crear
 * @return int** Apuntador a arreglo nx2 de pipes
 */
int **initialize_pipes(int n) {
    /* Counter loop */
    int i;

    /* Asigna memoria para n punteros a entero */
    int **pipefd = (int **)malloc(sizeof(int *) * n);

    if (!pipefd) {
        fprintf(stderr, "Error! en la reserva de memoria\n");
        exit(EXIT_FAILURE);
    }

    /* Inicializa n pipes */
    for (i = 0; i < n; i++) {
        pipefd[i] = (int *) malloc(sizeof(int) * 2);

        if (!pipefd) {
            fprintf(stderr, "Error! en la reserva de memoria\n");
        }
        else if (pipe(pipefd[i]) == -1) {
            perror("Error al crear pipe");
            exit(EXIT_FAILURE);
        }
    }

    return pipefd;
}


/*
 * Libera la memoria de un arreglo de pipes.
 *
 * @param pipefd: Puntero a arreglo de pipes
 * @param n: numero de pipes en el arreglo
 */
void free_pipe_arr(int **pipefd, int n) {
    int i;
    for (i = 0; i < n; i++) free(pipefd[i]);
    free(pipefd);
}
