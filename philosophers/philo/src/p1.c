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

void	init_args_n_arr(t_args *args, t_args *arr)
{
	int	i;

	args->phils = (pthread_t *)ft_memalloc(sizeof(pthread_t) * \
			(args->num + 1));
	args->forks = (pthread_mutex_t *)ft_memalloc(sizeof(pthread_mutex_t) * \
			(args->num + 1));
	args->printf_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	i = 0;
	while (++i < args->num + 1)
	{
		ft_memcpy(&arr[i], args, sizeof(t_args));
	}
}

int	main(int ac, char **av)
{
	t_args	args;
	int		i;
	t_args	*arr;

	parse_arguments(&args, av, ac);
	arr = (t_args *)ft_memalloc(sizeof(t_args) * (args.num + 1));
	init_args_n_arr(&args, arr);
	i = 0;
	while (++i < args.num + 1)
	{
		arr[i].id = i;
		pthread_mutex_init(&args.forks[i], NULL);
		arr[i].last_meal = get_current_time_ms();
		pthread_create(&args.phils[i], NULL, philosopher, &arr[i]);
	}
	i = 0;
	while (++i < args.num + 1)
	{
		pthread_join(args.phils[i], NULL);
	}
	exit(0);
	return (0);
}

void	check_death(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		print_action(args->printf_mutex, args->id, DEAD, 0);
		pthread_exit(0);
	}
	else if (death_time <= curr + args->time_to_eat)
	{
		usleep_ms(curr + args->time_to_eat - death_time);
		print_action(args->printf_mutex, args->id, DEAD, 0);
		pthread_exit(0);
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
		print_action(args->printf_mutex, args->id, DEAD, 0);
		pthread_exit(0);
	}
	else if (death_time <= curr + args->time_to_eat)
	{
		put_forks(first_fork, second_fork, args->forks);
		usleep_ms(curr + args->time_to_eat - death_time);
		print_action(args->printf_mutex, args->id, DEAD, 0);
		pthread_exit(0);
	}
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
		check_death_with_forks(args, first_fork, second_fork);
		print_action(args->printf_mutex, args->id, EAT, 0);
		usleep_ms(args->time_to_eat);
		args->last_meal = get_current_time_ms();
		put_forks(first_fork, second_fork, args->forks);
		args->must_eat_times--;
		print_action(args->printf_mutex, args->id, SLEEP, 0);
		usleep_ms (args->time_to_sleep);
		print_action(args->printf_mutex, args->id, THINK, 0);
	}
	check_death(args);
	print_action(args->printf_mutex, args->id, DONE, 0);
	return (0);
}
