#ifndef __directory_parser_H__
#define __directory_parser_H__

/*
 * Recorre los archivos de un directorio
 *
 * @param rut Ruta del directorio en donde estan los archivos
 */
void inode_traversal(char* rut);


/*
 * Recorre los directorios según los comandos de entrada
 *
 * @param rut1 Nivel 1 del arbol de directorios
 * @param rut2 Nivel 2 del arbol de directorios
 * @param rut2 Nivel 3 del arbol de directorios
 */
void traverse_directory_dfs(char* rut1, char* rut2, char* rut3);

#endif