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
			(args->c.p_num + 1));
	args->forks = (pthread_mutex_t *)ft_memalloc(sizeof(pthread_mutex_t) * \
			(args->c.p_num + 1));
	args->printf_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	i = 0;
	while (++i < args->c.p_num + 1)
	{
		ft_memcpy(&arr[i], args, sizeof(t_args));
	}
}

void	init_monitor(t_args *args)
{
	t_mon *info;

	info = (t_mon *)ft_memalloc(sizeof(t_mon));
	pthread_create(info, NULL, monitor, info);
}

void	init_philosophers(t_args *args, t_args *arr)
{
	int		i;
	
	i = 0;
	while (++i < args.num + 1)
	{
		arr[i].id = i;
		pthread_mutex_init(&args.forks[i], NULL);
		arr[i].last_meal = get_current_time_ms();
		pthread_create(&args.phils[i], NULL, philosopher, &arr[i]);
	}
	i = 0;
	pthread_join(monitor, NULL);
	while (++i < args.num + 1)
	{
		pthread_join(args.phils[i], NULL);
	}
}

int		main(int ac, char **av)
{
	t_data	*data;
	t_args	*arr;
	t_mon	*m;
	t_args	args;

	parse_const(&args, av, ac);
	arr = (t_args *)ft_memalloc(sizeof(t_args) * (args.num + 1));
	init_args_n_arr(&args, arr);
	init_monitor(&args);
	init_philosophers(&args, arr);
	exit(0);
	return (0);
}
