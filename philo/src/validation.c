#include "philosophers.h"

#define msg "ERROR: invalid integer %s for %s param: must be at least %d\n"

int		is_const_valid(t_const *c, int ac, char **av)
{
	int is_error;

	is_error = 0;
	if (c->must_eat_times < 0 && ac > 5) {
		is_error = printf(msg, av[5], "\"must eat times\"", 0);
	}
	if (c->p_num < 1) {
		is_error = printf(msg, av[1], "\"philo number\"", 2);
	}
	if (c->p_num > 200) {
		is_error = printf("ERROR: too many philosophers, must be less than 201\n");
	}
	if (c->time_to_die < 60 * 1000) {
		is_error = printf(msg, av[2], "\"time to die\"", 60);
	}
	if (c->time_to_eat < 60 * 1000) {
		is_error = printf(msg, av[3], "\"time to die\"", 60);
	}
	if (c->time_to_sleep < 60 * 1000) {
		is_error = printf(msg, av[4], "\"time to sleep\"", 60);
	}
	return (is_error == 0);
}