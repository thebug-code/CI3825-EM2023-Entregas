#include "schedule_list.h"
#include "utils.h"

int main(int argc, char *argv[]) {

	/* stop *paradas;
	FILE *f = fopen(argv[1], "r");
	int lineas = n_lines(f);

	fclose(f);

	paradas = load(argv[1]);
	imprimir(paradas, lineas);
    */

    sched_node *scheds = new_sched_list();
    ul_svc_charac(argv[1], &scheds);
	
	return 0;
}
