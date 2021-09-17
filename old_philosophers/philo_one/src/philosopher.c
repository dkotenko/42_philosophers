/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create2dchararr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 22:02:50 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		print_action(args, curr, DEAD, 0);
		exit_thread();
	}
}

void	check_death_with_forks(t_args *args, int first_fork, int second_fork)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		put_forks(first_fork, second_fork, args->forks);
		print_action(args, curr, DEAD, 0);
		exit_thread();
	}
	else if (death_time <= curr + args->time_to_eat)
	{
		usleep_ms(curr + args->time_to_eat - death_time);
		put_forks(first_fork, second_fork, args->forks);
		print_action(args, curr, DEAD, 0);
		exit_thread();
	}
}

void	do_sleep(t_args *args)
{
	long long	curr;
	long long	death_time;

	print_action(args, args->id, SLEEP, 0);
	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		print_action(args, curr, DEAD, 0);
		exit_thread();
	}
	else if (death_time <= curr + args->time_to_sleep)
	{
		usleep_ms(curr + args->time_to_sleep - death_time);
		print_action(args, curr, DEAD, 0);
		exit_thread();
	}
	usleep_ms(args->time_to_sleep);
}

void	do_eat(t_args *args, int first_fork, int second_fork)
{
	print_action(args, get_current_time_ms(), EAT, 0);
	check_death_with_forks(args, first_fork, second_fork);
	usleep_ms(args->time_to_eat);
	args->last_meal = get_current_time_ms();
	put_forks(first_fork, second_fork, args->forks);
	args->must_eat_times--;
}

void	*philosopher(void *arg)
{
	int		first_fork;
	int		second_fork;
	t_args	*args;

	args = (t_args *)arg;
	first_fork = get_fork_id(args->id, args->num, 1);
	second_fork = get_fork_id(args->id, args->num, 0);
	while (args->must_eat_times)
	{
		check_death(args);
		if (!is_forks_taken(args, first_fork, second_fork))
			continue ;
		do_eat(args, first_fork, second_fork);
		do_sleep(args);
		print_action(args, get_current_time_ms(), THINK, 0);
		usleep_ms((args->time_to_die - args->time_to_eat \
		- args->time_to_sleep) / 2);
	}
	check_death(args);
	print_action(args, get_current_time_ms(), DONE, 0);
	exit_thread());
	return (0);
}
