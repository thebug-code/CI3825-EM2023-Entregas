#ifndef __utils_H__
#define __utils_H__

#define USAGE "USAGE: ./simutransusb -s <archivo> [-c <archivo>] [-t <num>]\n"

#define MAX_BUFFER 200
#include "bus_departure_time_list.h"
#include "service_characterization_list.h"
#include "stop_list.h"
#include "bus_stop.h"
#include "arrival_schedule.h"

/*
 * Carga los datos del archivo de caracterizacion del servicio en una
 * lista doblemente enlazada
 *
 * @param filename: nombre del archivo de caracterizacion del servicio
 * @return un apuntador a la lista de servicios
 */
svc_charac_node *ul_svc_charac(char filename[]);


/*
 * Carga los datos del archivo de caracterizacion de la carga al sistema
 * en una lista doblemente enlazada
 *
 * @param filename: ruta del archivo con la caracterizacion de la carga
 * al sistema
 * @return un apuntador a la lista de paradas
 */
stop_node *ul_charac_ld_sys(char filename[]);


/*
 * Lee y verifica los argumentos de entrada pasados por linea de comandos.
 * En caso de que haya un error, imprime el mensaje de error y termina
 * la ejecucion del programa.
 *
 * @param argc: numero de argumentos de la linea de comandos
 * @param argv: vector de argumentos de la linea de comandos
 * @param svc_list: puntero a la cabeza de la lista de servicios
 * @param stop_list: puntero a la cabeza de la lista de paradas
 * de autobuses
 * @return float tiempo que dura un minuto en la simulacion
 */
float read_input(int argc, char *argv[], svc_charac_node **svc_list, stop_node **stop_list);


/*
 * Verifica que el argumento de la opcion no sea una opcion.
 * En caso afirmativo termina la ejecucion del programa.
 *
 * @param optarg: variable externa que es el apuntador a los
 * argumentos de las opciones.
 */
void check_opt_arg(char* optarg);


/*
 * Crea una estructura de tipo time_t a partir de una hora, minuto y segundo
 * dados.
 *
 * @param hour: hora
 * @param min: minuto
 * @param sec: segundo
 * @return time_t con la hora, minuto y segundo dados
 */
time_t create_hour(int hour, int min, int sec);


/*
 * Cuenta el numero de rutas que hay en la lista de de caracterizacion
 * del servicio.
 *
 * @param svc_list: puntero a la cabeza de la lista de servicios
 * @return int numero de rutas
 */
int count_routes(svc_charac_node *svc_list);


/*
 * Crea un arreglo de n pipes. En caso de error termina la ejecucion
 * del programa.
 *
 * @param n: numero de pipes a crear
 * @return int** Apuntador a arreglo nx2 de pipes
 */
int **initialize_pipes(int n);


/*
 * Libera la memoria de un arreglo de pipes.
 *
 * @param pipefd: Puntero a arreglo de pipes
 * @param n: numero de pipes en el arreglo
 */
void free_pipe_arr(int **pipefd, int n);

#endif
