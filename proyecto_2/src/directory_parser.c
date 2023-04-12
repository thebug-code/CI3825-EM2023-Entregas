/*
 * Implementacion de las funciones utiles para el manejo de directorios y archivos
 */

#include "directory_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/*
 * Imprime los archivos encontrados
 *
 * @param list Indica si se debe mostrar el nombre de los archivos encontrados
 * @param size Indica si se debe mostrar el tamaño de archivos encontrados
 * @param size_file Tamaño del archivo
 * @param name_file Nombre del archivo
 */
void print_file(int list, int size, long int size_file, char* name_file) {
    if(list == 1 && size == 0) {
        printf("%s\n", name_file);
    }
    else if(list == 1 && size == 1) {
        printf("%s %ldKb\n", name_file, size_file/1024);
    }
    else if(list == 0 && size == 1) {
        printf("%ldKb\n", size_file/1024);
    }
}

/*
 * Recorre los archivos de un directorio
 *
 * @param rut Ruta del directorio en donde estan los archivos
 * @param list Indica si se debe mostrar el nombre de los archivos encontrados
 * @param size Indica si se debe mostrar el tamaño de archivos encontrados
 * @param name Restringe la busqueda de los archivos
 */
int inode_traversal(char* rut, int list, int size, char* name) {
    DIR* dir;
    struct dirent* entry;
    char path[1024];
    struct stat statbuf;
    int cnt = 0;

    /*Habre el directorios indicado*/
    dir = opendir(rut);
    if (!dir) {
        return cnt;
    }

    while ((entry = readdir(dir))) {

        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);

        if (lstat(path, &statbuf) == -1) {
          continue;
        }
        
        /*Imprime los archivos*/
        if (!S_ISDIR(statbuf.st_mode) && name == NULL) {
            print_file(list, size, statbuf.st_size, entry->d_name);
            cnt++;
        }else if (!S_ISDIR(statbuf.st_mode) && name != NULL && !strncmp(name, entry->d_name, strlen(name))) {
            print_file(list, size, statbuf.st_size, entry->d_name);
            cnt++;
        }
    }

    closedir(dir);
    return cnt;
}

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
int traverse_directory_dfs(char* rut1, char* rut2, char* rut3, int nocount,
    int list, int size, char* name) {
    DIR* dir;
    struct dirent* entry;
    char path[1024];
    struct stat statbuf;
    char rut[1024];
    int n_file = 0;

    /*Habre el directorios indicado*/
    if(rut1 != NULL) {
        dir = opendir(rut1);
        if (!dir) {
            perror("opendir");
            return n_file;
        }
        strcpy(rut, rut1);
    }else {
        dir = opendir(".");
        if (!dir) {
            perror("opendir");
            return n_file;
        }
        strcpy(rut, ".");
    }


    while ((entry = readdir(dir))) {

        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        
        /*Recorre los directorios de forma recursiva*/

        /*Todos los comandos que se refieren a nombre de directorios son usados*/
        if(rut1 != NULL && rut2 != NULL && rut3 != NULL) {
            snprintf(path, sizeof(path), "%s/%s/%s", rut1, rut2, rut3);
            n_file = inode_traversal(path, list, size, name);
            break;
        }
        /*El comando que se refiere al tipo de apariciones no es usado*/
        else if(rut1 != NULL && rut2 != NULL && rut3 == NULL) {
            if(!strcmp(rut2, "level3")){
                snprintf(path, sizeof(path), "%s/%s", rut1, entry->d_name);
                n_file = n_file + inode_traversal(path, list, size, name);
            }else {
                snprintf(path, sizeof(path), "%s/%s", rut1, rut2);
                if (lstat(path, &statbuf) == -1) {
                    continue;
                }
                n_file = traverse_directory_dfs(path, "level3", rut3, 1, list, size, name);
                break;
            }
        /*El comando que se refiere al tipo de especie no es usado*/
        }else if(rut1 != NULL && rut2 == NULL && rut3 != NULL) {
            n_file = n_file + traverse_directory_dfs(rut1, entry->d_name, rut3, 1, list, size, name);
        /*El comando que se refiere a la región no es usado*/
        }else if(rut1 == NULL && rut2 != NULL && rut3 != NULL) {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                n_file = n_file + traverse_directory_dfs(entry->d_name, rut2, rut3, 1, list, size, name);
            }
        }
        /*Solo es usado el comando qu se refiere a la región*/
        else if(rut1 != NULL && rut2 == NULL && rut3 == NULL) {
            n_file = n_file + traverse_directory_dfs(rut1, entry->d_name, rut3, 1, list, size, name);

        }
        /*Solo es usado el comando qu se refiere a la especie*/
        else if(rut1 == NULL && rut2 != NULL && rut3 == NULL) {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                n_file = n_file + traverse_directory_dfs(entry->d_name, rut2, rut3, 1, list, size, name);
            }
        }
        /*Solo es usado el comando que se refiere a las apariciones*/
        else if(rut1 == NULL && rut2 == NULL && rut3 != NULL) {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                n_file = n_file + traverse_directory_dfs(entry->d_name, rut2, rut3, 1, list, size, name);
            }
        /*Recorre todos los directorios*/
        }else {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                n_file = n_file + traverse_directory_dfs(entry->d_name, rut2, rut3, 1, list, size, name);
            } 
        }

    }
    closedir(dir);

    /*Verifica si se debe imprimir la cantidad de archivos encontrados*/
    if(nocount == 0) {
        printf("Archivos encontrados: %d\n", n_file);
    }

    return n_file;
}