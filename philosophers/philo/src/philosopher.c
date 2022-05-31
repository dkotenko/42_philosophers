#include "philosophers.h"

void	check_death(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->c.time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		print_action(args->printf_mutex, args->id, DEAD, 0);
        args->status = DEAD;
	}
}

void	*philosopher(void *arg)
{
	int		first_fork;
	int		second_fork;
	t_args	*args;

	args = (t_args *)arg;
    first_fork = get_fork_id(args->id, args->c.p_num, 1);
    second_fork = get_fork_id(args->id, args->c.p_num, 0);
    arg->first_fork = first_fork;
	arg->second_fork = second_fork;
	while (args->c.must_eat_times && arg->status != DEAD)
	{
		check_death(args);
		if (!is_forks_taken(args, first_fork, second_fork))
			continue ;
		check_death_with_forks(args, first_fork, second_fork);
		print_action(args->printf_mutex, args->id, EAT, 0);
		usleep_ms(args->c.time_to_eat);
		args->last_meal = get_current_time_ms();
		put_forks(first_fork, second_fork, args->forks);
		args->c.must_eat_times--;
		print_action(args->printf_mutex, args->id, SLEEP, 0);
		usleep_ms (args->c.time_to_sleep);
		print_action(args->printf_mutex, args->id, THINK, 0);
	}
	check_death(args);
	print_action(args->printf_mutex, args->id, DONE, 0);
	return (0);
}
