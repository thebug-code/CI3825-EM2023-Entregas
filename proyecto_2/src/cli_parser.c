/*
 * Implementacion de las funciones utiles para el manejo de la linea de comandos.
 */

#include "cli_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


/*
 * Imprime el mensaje de uso del programa.
 *
 * @param program_name Nombre del programa.
 */
void print_usage(char *program_name) {
    fprintf(stderr, "Usage: %s -s [-r <region>] [-s <species>] [-t <appear_type>] "
        "[-c|--nocount] [-l|--list] [-z|--size] [name]\n", program_name);
}


/*
 * Parsea los argumentos de la línea de comandos y los guarda en la estructura
 * de opciones.
 *
 * @param argc Cantidad de argumentos de la línea de comandos.
 * @param argv Argumentos de la línea de comandos.
 * @param opts Estructura de opciones donde se guardarán los argumentos.
 */
void handle_cli_args(int argc, char *argv[], options_t *opts) {
    /* 
     * Variables para indicar las opciones 
     */
    int rflag = 0;
    int sflag = 0;
    int tflag = 0;
    int cflag = 0;
    int lflag = 0;
    int zflag = 0;

    /*
     * Punteros para argumentos de las opciones
     */
    char *rvalue = NULL;
    char *svalue = NULL;
    char *tvalue = NULL;
    char *name = NULL;

    /* 
     * Variables para el getopt
     */
    struct option long_options[] = {
        {"nocount", no_argument, 0, 'c'},
        {"list",    no_argument, 0, 'l'},
        {"size",    no_argument, 0, 'z'},
        {0,         0,           0, 0}
    };

    /* 
     * Opciones cortas
     */
    char *short_options = "r:s:t:clz";

    int opt;

    if (argc < 2) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (opt) {
            case 'r':
                sflag = 1;
                rvalue = optarg;
                break;
            case 's':
                cflag = 1;
                svalue = optarg;
                break;
            case 't':
                tflag = 1;
                tvalue = optarg;
                break;
            case 'c':
                cflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            case 'z':
                zflag = 1;
                break;
            case '?':
                fprintf(stderr, "Unknown option -%c.\n", optopt);
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
            case ':':
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
     /* Verifica si queda algún argumento que no sea de opción */
    if (optind < argc)
        name = argv[optind];

    /* Ignorar la advertencia de variable no utilizada para 'nombre' */
    (void)name;

    /* Verifica que se haya especificado al menos una opción (ojo falta) */
    if (!rflag && !sflag && !tflag && !cflag && !lflag && !zflag) {
        fprintf(stderr, "You must specify at least one option.\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Guarda los argumentos en la estructura de opciones */
    opts->region = rvalue;
    opts->species = svalue;
    opts->appear_type = tvalue;
    opts->nocount = cflag;
    opts->list = lflag;
    opts->size = zflag;

    return;
}
