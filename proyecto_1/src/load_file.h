#ifndef __load_file_H__
#define __load_file_H__

#include <stdio.h>

#include "stop_list.h"

stop_node *load(char *name_file);
void imprimir(stop_node *list);

#endif