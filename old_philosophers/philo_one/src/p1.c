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
	args->last_meal = get_current_time_ms();
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
	if (args->last_meal + \
		(long long)args->time_to_die <= get_current_time_ms())
	{
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
		print_action(args->printf_mutex, args->id, EAT, 0);
		args->last_meal = get_current_time_ms();
		usleep(args->time_to_eat);
		put_forks(first_fork, second_fork, args->forks);
		args->must_eat_times--;
		print_action(args->printf_mutex, args->id, SLEEP, 0);
		usleep (args->time_to_sleep);
		print_action(args->printf_mutex, args->id, THINK, 0);
	}
	print_action(args->printf_mutex, args->id, DONE, 0);
	return (0);
}
