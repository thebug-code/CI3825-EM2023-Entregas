#include "stop_list.h"
#include "load_file.h"

int main(int argc, char *argv[]) {
	stop_node *l;
	l = load(argv[1]);
	imprimir(l);
	
	return 0;
}