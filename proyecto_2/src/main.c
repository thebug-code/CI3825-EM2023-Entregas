/*
 * Proyecto 2 del curso Sistemas de Operacion I
 *
 * El programa cuenta el numero de archivos que cumplen con los parametros
 * de busqueda especificados por el usuario.
 *
 * Los parametros de busqueda son:
 *
 * [-r]: Region
 * [-s]: Especie
 * [-t]: Tipo de aparicion
 * [-c|--nocount]: No mostrar el numero de archivos encontrados
 * [-l|--list]: Mostrar el nombre de los archivos encontrados
 * [-z|--size]: Mostrar el tamaño de los archivos encontrados
 * [name]: Restringe la busqueda de los archivos
 *
 * El sistema jeraquico esta compuesto por 3 niveles:
 *
 * Nivel 1: Region
 * Nivel 2: Especie
 * Nivel 3: Tipo de aparicion
 *
 * Los parametros de busqueda son opcionales, si no se especifica alguno
 * se asume que se desea buscar en todos los directorios.
 *
 * Ejemplo de uso:
 *
 * Si queremos saber cuáles son los líderes de gimnasio de Kanto, pero no nos interesa el número:
 *
 * $ ./fameChecker -t gym_leader -r kanto --nocount --list
 *
 * Si necesitamos tener una idea de cuánta información puede haber sobre un personaje que aparece solo
una vez:
 *$ ./fameChecker -t one_time --list
 *
 * Autores:
 * Karen Martinez.
 * Oliver Bueno.
 * Alejandro Meneses
 */


#include "cli_parser.h"
#include "directory_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* Para constantes y tipos simbólicos misceláneos (optind) */

#define MAX_PATH_LEN 1024


int main(int argc, char* argv[]) {
    /* Parsea los argumentos de entrada */
    options_t *opts = (options_t*)malloc(sizeof(options_t));
    handle_cli_args(argc, argv, opts);

    traverse_directory_dfs(
        opts->region,
        opts->species,
        opts->appear_type,
        opts->nocount,
        opts->list,
        opts->size,
        argv[optind]
    );

    free(opts);

    return 0;
}
