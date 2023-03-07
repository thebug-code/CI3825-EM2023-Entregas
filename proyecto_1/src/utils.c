/* Implementaciones de funciones utiles para transporte USB
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>


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
                if (strcmp("\n", line)) {
                    hour = atoi(strtok(line, ":"));
                    min = atoi(strtok(NULL, "("));
                    cap = atoi(strtok(NULL, ") "));

                    /* Crea un nuevo horario */
                    new_schedule = new_sched(hour, min, cap);

                    /* Lo inserta en lista de horarios de la 
                    * ruta asociada */
                    push_sched_list(&(svc_list->data->scheds), new_schedule);
                }
            }

            line = strtok(NULL, "");
        }
    }

    fclose(fp);

    
    if (line)
        free(line);
    return 1;   
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
 * Lee y verifica los argumentos pasados por lineas de comandos.
 * En caso de que haya un error muestra un mensaje con el error
 * y termina la ejecucion del programa.
 *
 * @param argc: Numero de argumentos de la linea de comandos
 * @param argv: Vector de argumentos de la linea de comandos
 */
void read_input(int argc, char *argv[])  {
    sched_node *scheds; /* Lista de horarios */
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
    scheds = new_sched_list();
    ul_svc_charac(svalue, &scheds);

    /* printf("svalue = \"%s\"\n", svalue);
	printf("cvalue = \"%s\"\n", cvalue);
	printf("tvalue = \"%s\"\n", tvalue); */
    return;
}
