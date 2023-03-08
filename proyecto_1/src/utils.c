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
svc_node *ul_svc_charac(char filename[]) {
    FILE *fp;           /* Apuntador a archivo */
    char *line = NULL;  /* Ptr a lineas del archivo */
    size_t len = 0;     /* Var para numero de chars de cada linea */
    ssize_t read;
    svc_node *svc_list; /* Lista de servicios */

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
                svc *new_service = new_svc(route); /* FALTA VERIFICAR */
                /* Lo inserta en la lista de servicios */
                push_service_list(&svc_list, new_service); /* FALTA VERIFICAR */
            }
            else {
                /* Extrae la hora, minuto y capacidad del 
                 * j-enesimo horario */
                if (strcmp("\n", line)) {
                    int hour = atoi(strtok(line, ":"));
                    int min = atoi(strtok(NULL, "("));
                    int cap = atoi(strtok(NULL, ") "));

                    /* Crea un nuevo horario */
                    sched *new_schedule = new_sched(hour, min, cap);

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

    return svc_list; 
}


/*
 * Imprime la lista enlazada con los servicios (rutas y 
 * horarios asociados) en un formato legible para fines
 * de depuracion.
 *
 * @param list: Puntero a la cabeza de lista de servicios
 */
void print_svc_list(svc_node *list) {
	svc_node *s = list;

	while (s) {
		sched_node *sched_s = s->data->scheds; /* Lista de horarios de la s-esima ruta */
		printf("%s ", s->data->route);

        /* Recorre la lista de horarios y los imprime */
		while (sched_s) {
            char st[30];
            strftime(st, sizeof st, "%H:%M", localtime(&(sched_s->data->time)));
			printf("%s ", st);
			printf("%d ", sched_s->data->cap);

			sched_s = sched_s->next;
		}

		printf("\n");
		s = s->next;
	}

    return;
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
    svc_node *svc_list; /* Lista de servicios */

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
    svc_list = ul_svc_charac(svalue);
    print_svc_list(svc_list);

    /* printf("svalue = \"%s\"\n", svalue);
	printf("cvalue = \"%s\"\n", cvalue);
	printf("tvalue = \"%s\"\n", tvalue); */
    return;
}
