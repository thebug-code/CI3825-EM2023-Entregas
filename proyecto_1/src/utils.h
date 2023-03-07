#ifndef __utils_H__
#define __utils_H__

#define USAGE "USAGE: ./simutransusb -s <archivo> [-c <archivo>] [-t <num>]\n"

#include "schedule_list.h"

u_int8_t ul_svc_charac(char filename[], sched_node** scheds);
void read_input(int argc, char *argv[]); 
void check_opt_arg(char* optarg);

#endif
