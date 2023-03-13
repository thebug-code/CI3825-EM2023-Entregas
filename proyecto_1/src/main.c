#include "schedule_list.h"
#include "stop_list.h"
#include "utils.h"


int main(int argc, char *argv[]) {
    svc_node *svc_list = new_stop_list();
    stop_node *stop_list = new_service_list();

    read_input(argc, argv, &svc_list, &stop_list);
	return 0;
}
