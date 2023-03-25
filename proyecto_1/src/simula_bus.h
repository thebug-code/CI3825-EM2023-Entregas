#ifndef __simula_bus_H__
#define __simula_bus_H__

#define MESSAGE_SIZE 256
#define READ_END 0
#define WRITE_END 1


/* Estructura para almacenar los argumentos de la función simulate_bus_route */
typedef struct Arg_struct {
    int bus_id; /* Identificador del autobús */
    time_t start_time; /* Hora de inicio de la simulación */
    char *route_name; /* Nombre de la ruta */
    int min_duration; /* Duración de un minuto en la simulación */
    int *counter_time; /* Contador de tiempo de la simulación */
    int capacity; /* Capacidad del autobús */
    int duration; /* Duración del recorrido */
    arrival_node **arrivals; /* Lista con los horarios de llegada de las personas */
    pthread_mutex_t *mutex_arrivals; /* Mutex para la lista de llegadas */
    int *fd; /* Arreglo de descriptores de archivo */
} args;


/*
 * Obtiene el tiempo actual de la simulación.
 *
 * @param start_time Tiempo de inicio de la simulación
 * @param sim_counter Contador de tiempo de la simulación
 * @return Tiempo actual de la simulación
 */
time_t get_current_time(time_t start_time, int sim_counter);


/* 
 * Crea una estructura args con los argumentos de la función 
 * simulate_bus_route. Si hay un error, termina el programa.
 *
 * @param bus_id Identificador del autobús
 * @param route_name Nombre de la ruta
 * @param min_duration Duración de un minuto en la simulación
 * @param counter_time Contador de tiempo de la simulación
 * @param capacity Capacidad del autobús
 * @param duration Duración del recorrido
 * @param arrivals Lista con los horarios de llegada de las personas
 * @param fd Arreglo de descriptores de archivo
 * @return Estructura args con los argumentos de la función
 */
args *create_new_args(int bus_id, 
                      time_t start_time,
                      char *route_name,
                      int min_duration,
                      int *counter_time,
                      int capacity,
                      int duration,
                      arrival_node **arrivals,
                      pthread_mutex_t *mutex_arrivals,
                      int *fd);


/*
 * Duerme el proceso por un tiempo determinado.
 *
 * @param sec Segundos a dormir
 * @param nsec Nanosegundos a dormir
 */
void sleep_for(int sec, int nsec);


/*
 * Simula el recorrido de un autobús por una ruta.
 *
 * @param arg Apuntador a la estructura args
 */
void *simulate_bus_route(void *arg);

#endif