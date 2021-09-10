#include "../philosophers.h"



int main(int ac, char **av)
{
	t_args args;

	if (ac != 5 && ac != 6)
		print_usage();
	parse_arguments(&args, av, ac);
	return (0);
}
