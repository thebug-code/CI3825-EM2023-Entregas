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

/*
 * Recorre los archivos de un directorio
 *
 * @param rut Ruta del directorio en donde estan los archivos
 */
void inode_traversal(char* rut) {
    DIR* dir;
    struct dirent* entry;
    char path[1024];
    struct stat statbuf;


    dir = opendir(rut);
    if (!dir) {
         perror("opendir");
        return;
    }

    while ((entry = readdir(dir))) {

        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);

        if (lstat(path, &statbuf) == -1) {
          perror("lstat");
          continue;
        }
        

        if (!S_ISDIR(statbuf.st_mode)) {
            printf("Found file: %s (inode: %ld)\n", entry->d_name, statbuf.st_ino);
        }
    }
    closedir(dir);
}

/*
 * Recorre los directorios según los comandos de entrada
 *
 * @param rut1 Nivel 1 del arbol de directorios
 * @param rut2 Nivel 2 del arbol de directorios
 * @param rut2 Nivel 3 del arbol de directorios
 */
void traverse_directory_dfs(char* rut1, char* rut2, char* rut3) {
    DIR* dir;
    struct dirent* entry;
    char path[1024];
    struct stat statbuf;
    char rut[1024];

    /*Habre el directorios indicado*/
    if(rut1 != NULL) {
        dir = opendir(rut1);
        if (!dir) {
            perror("opendir");
            return;
        }
        strcpy(rut, rut1);
    }else {
        dir = opendir(".");
        if (!dir) {
            perror("opendir");
            return;
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
            if (lstat(path, &statbuf) == -1) {
                perror("lstat");
                continue;
            }
            inode_traversal(path);
            break;
        }
        /*El comando que se refiere al tipo de apariciones no es usado*/
        else if(rut1 != NULL && rut2 != NULL && rut3 == NULL) {
            if(!strcmp(rut2, "level3")){
                snprintf(path, sizeof(path), "%s/%s", rut1, entry->d_name);
                if (lstat(path, &statbuf) == -1) {
                    perror("lstat");
                    continue;
                }
                inode_traversal(path);
            }else {
                snprintf(path, sizeof(path), "%s/%s", rut1, rut2);
                if (lstat(path, &statbuf) == -1) {
                    perror("lstat");
                    continue;
                }
                traverse_directory_dfs(path, "level3", rut3);
                break;
            }
        /*El comando que se refiere al tipo de especie no es usado*/
        }else if(rut1 != NULL && rut2 == NULL && rut3 != NULL) {
            traverse_directory_dfs(rut1, entry->d_name, rut3);
        /*El comando que se refiere a la región no es usado*/
        }else if(rut1 == NULL && rut2 != NULL && rut3 != NULL) {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                perror("lstat");
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                traverse_directory_dfs(entry->d_name, rut2, rut3);
            }
        }
        /*Solo es usado el comando qu se refiere a la región*/
        else if(rut1 != NULL && rut2 == NULL && rut3 == NULL) {
            traverse_directory_dfs(rut1, entry->d_name, rut3);

        }
        /*Solo es usado el comando qu se refiere a la especie*/
        else if(rut1 == NULL && rut2 != NULL && rut3 == NULL) {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                perror("lstat");
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                traverse_directory_dfs(entry->d_name, rut2, rut3);
            }
        }
        /*Solo es usado el comando que se refiere a las apariciones*/
        else if(rut1 == NULL && rut2 == NULL && rut3 != NULL) {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                perror("lstat");
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                traverse_directory_dfs(entry->d_name, rut2, rut3);
            }
        /*Recorre todos los directorios*/
        }else {
            snprintf(path, sizeof(path), "%s/%s", rut, entry->d_name);
            if (lstat(path, &statbuf) == -1) {
                perror("lstat");
                continue;
            }
            if (S_ISDIR(statbuf.st_mode)) {
                traverse_directory_dfs(entry->d_name, rut2, rut3);
            } 
        }

    }
    closedir(dir);
}