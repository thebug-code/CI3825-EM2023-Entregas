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
    FILE *fp;                /* Apuntador a archivo */
    char *line = NULL;       /* Puntero a lineas del archivo */
    size_t len = 0;          /* Numero de caracteres de cada linea */
    int first_time = 1;
    ssize_t read;
    svc_node *ptr_svc_list_h; /* Ptr a la cabeza de la lista de svcs */
    svc_node *ptr_svc_list;   /* Ptr a nodos de la lista de svcs */

    fp = fopen(filename, "r");
    if (!fp) {
        perror("no such file");
		return NULL;
    }

    /* Inicializa la lista con los servicios */
    ptr_svc_list_h = new_service_list(); /* FALTA VERIFICAR */
    ptr_svc_list = ptr_svc_list_h;

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
                push_service_list(&ptr_svc_list_h, new_service); /* FALTA VERIFICAR */

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
                    sched *new_schedule = new_sched(hour, min, cap);

                    /* Lo inserta en lista de horarios de la 
                    * ruta asociada */
                    push_sched_list(&(ptr_svc_list->data->scheds), new_schedule);
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
 * Imprime la lista enlazada con los servicios (rutas y 
 * horarios asociados) en un formato legible para fines
 * de depuracion.
 *
 * @param list: Puntero a la cabeza de lista de servicios
 */
void print_svc_list(svc_node *list) {
	while (list) {
		sched_node *sched_s = list->data->scheds; /* Lista de horarios de la s-esima ruta */
		printf("%s ", list->data->route);

        /* Recorre la lista de horarios y los imprime */
		while (sched_s) {
            char st[30];
            strftime(st, sizeof st, "%H:%M", localtime(&(sched_s->data->time)));
			printf("%s ", st);
			printf("%d ", sched_s->data->cap);

			sched_s = sched_s->next;
		}

		printf("\n");
		list = list->next;
    }
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
	} else {
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
        	push_stop_list(&stop_list, n_stop);
        	
        	j = j - 8;

    	}

    	fclose(file);
    	return stop_list;
	}
}


/*
 * Imprime la lista enlazada con los datos de carga del
 * sistema (paradas de los autobuses, tiempo de recorrido
 * y numero de personas que llegan a las paradas) 
 * en un formato legible para fines de depuracion.
 *
 * @param list: Puntero a la cabeza de lista de paradas
 * de autobuses
 */
void print_charac_ld_sys(stop_node *list) {
	stop_node *h = list;

	while (h) {
		arrival_node *arri = h->data->arrivals;
		printf("%s %s %d ", h->data->cod, h->data->route_name, h->data->recorr);

		while (arri) {
			printf("%d ", arri->data->n_people);
			arri = arri->next;
		}

		printf("\n");
		h = h->next;
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
 * @param svc_list: puntero a la cabeza de la lista de servicios
 * @param stop_list: puntero a la cabeza de la lista de paradas
 * de autobuses
 */
void read_input(int argc, char *argv[], svc_node **svc_list, stop_node **stop_list)  {
    svc_node *svc_list_h = *svc_list;
	stop_node *stop_list_h = *stop_list;

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
    svc_list_h = ul_svc_charac(svalue);
    /* print_svc_list(svc_list); */

   /*
    * Carga la caracterizacion de carga del sistema en una lista
    * enlazada FALTA VERIFICAR
    */
	stop_list_h = ul_charac_ld_sys(cvalue);
	/* print_charac_ld_sys(stop_list); */

    /* printf("svalue = \"%s\"\n", svalue);
	printf("cvalue = \"%s\"\n", cvalue);
	printf("tvalue = \"%s\"\n", tvalue); */
    return;
}
