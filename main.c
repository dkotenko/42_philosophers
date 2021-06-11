#include "philosophers.h"



int main(int ac, char **av)
{
	t_args args;

	if (ac != 5 && ac != 6)
		print_usage();
	parse_arguments(&args, av, ac);
	return (0);
}

4 [5] args
number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]