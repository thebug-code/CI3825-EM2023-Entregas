#ifndef __utils_H__
#define __utils_H__

#define USAGE "USAGE: ./simutransusb -s <archivo> [-c <archivo>] [-t <num>]\n"

#define MAX_BUFFER 200
#include "schedule_list.h"
#include "service_list.h"
#include "stop_list.h"
#include "bus_stop.h"
#include "arrival_schedule.h"

svc_node *ul_svc_charac(char filename[]);
void read_input(int argc, char *argv[], svc_node **svc_list, stop_node **stop_list);
void check_opt_arg(char* optarg);
stop_node *ul_charac_ld_sys(char filename[]);

#endif
