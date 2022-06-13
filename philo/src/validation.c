#include "philosophers.h"

#define msg "ERROR: invalid integer %s for %s param: must be positive or zero\n"
#define msg_alone "ERROR: philos don't eat alone, needs at least two philos\n"

int		is_const_valid(t_const *c, int ac, char **av)
{
	int is_error;

	is_error = 0;
	if (c->must_eat_times < 0 && ac > 5) {
		is_error = printf(msg, av[5], "\"must eat times\"");
	}
	if (c->p_num < 0) {
		is_error = printf(msg, av[1], "\"philo number\"");
	}
	if (c->p_num == 1) {
		is_error = printf(msg_alone);
	}
	if (c->time_to_die < 0) {
		is_error = printf(msg, av[2], "\"time to die\"");
	}
	if (c->time_to_eat < 0) {
		is_error = printf(msg, av[3], "\"time to die\"");
	}
	if (c->time_to_sleep < 0) {
		is_error = printf(msg, av[4], "\"time to sleep\"");
	}
	return (is_error == 0);
}