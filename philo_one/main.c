#include "../philosophers.h"

int *get_forks(t_args *args)
{
    int *forks;

    forks = (int *)malloc(sizeof(int) * args->phil_num);
    if (!forks)
        handle_error("Malloc error\n");
    return (malloc)
}

int main(int ac, char **av)
{
	t_args args;

	parse_arguments(&args, av, ac);
	forks = get_forks(&args);
	return (0);
}
