#include "stop_list.h"
#include "utils.h"

int main(int argc, char *argv[]) {
	stop_node *l;
	l = ul_charac_ld_sys(argv[1]);
	print_charac_ld_sys(l);
	
	return 0;
}
