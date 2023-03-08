#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bus_stop.h"
#include "arrival_schedule.h"
#include "utils.h"


/*
 * Carga el archivo de caracterizacióna de la carga al sistema 
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


/*Función impresion para detectar errores*/
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
