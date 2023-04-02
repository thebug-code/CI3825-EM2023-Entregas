#ifndef __cli_parser_H__
#define __cli_parser_H__


/* Estructura que representa las opciones de la línea de comandos */
typedef struct {
    char *region;      /* Nombre de la región */
    char *species;     /* Nombre de la especie */
    char *appear_type; /* Tipo de aparición */
    int nocount;       /* Indica si se debe contar o no */
    int list;          /* Indica si se debe listar o no */
    int size;          /* Indica si se debe mostrar el tamaño o no */
} options_t;


/*
 * Imprime el mensaje de uso del programa.
 *
 * @param program_name Nombre del programa.
 */
void print_usage(char *program_name);


/*
 * Parsea los argumentos de la línea de comandos y los guarda en la estructura
 * de opciones.
 *
 * @param argc Cantidad de argumentos de la línea de comandos.
 * @param argv Argumentos de la línea de comandos.
 * @param opts Estructura de opciones donde se guardarán los argumentos.
 */
void handle_cli_args(int argc, char *argv[], options_t *opts);
#endif
