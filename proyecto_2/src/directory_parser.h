#ifndef __directory_parser_H__
#define __directory_parser_H__

/*
 * Imprime los archivos encontrados
 *
 * @param list Indica si se debe mostrar el nombre de los archivos encontrados
 * @param size Indica si se debe mostrar el tamaño de archivos encontrados
 * @param size_file Tamaño del archivo
 * @param name_file Nombre del archivo
 */
void print_file(int list, int size, long int size_file, char* name_file);

/*
 * Recorre los archivos de un directorio
 *
 * @param rut Ruta del directorio en donde estan los archivos
 * @param list Indica si se debe mostrar el nombre de los archivos encontrados
 * @param size Indica si se debe mostrar el tamaño de archivos encontrados
 * @param name Restringe la busqueda de los archivos
 */
int inode_traversal(char* rut, int list, int size, char* name);


/*
 * Recorre los directorios según los comandos de entrada
 *
 * @param rut1 Nivel 1 del arbol de directorios
 * @param rut2 Nivel 2 del arbol de directorios
 * @param rut2 Nivel 3 del arbol de directorios
 * @list nocount Indica si se debe mostrar el numero de archivos encontrados
 * @list list Indica si se debe mostrar el numero de archivos encontrados
 * @size size Indica si se debe mostrar el numero de archivos encontrados
 * @param name Indica si se debe restringir la busqueda de los archivos
 */
int traverse_directory_dfs(
    char* rut1,
    char* rut2,
    char* rut3,
    int nocount,
    int list,
    int size,
    char* name
);

#endif
