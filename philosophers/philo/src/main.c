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

void	init_data(t_data *data)
{
	data->phi = (t_phi *)ft_memalloc(sizeof(t_phi) * (data->c->p_num + 1));
	data->pthread_phi = (pthread_t *)ft_memalloc(sizeof(pthread_t) * \
			(args->c.p_num + 1));
	args->printf_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
}

void	init_monitor(t_data *data)
{
	t_mon *info;

	data->mon = (t_mon *)ft_memalloc(sizeof(t_mon));
	info->is_alive = (int *)ft_memalloc(data->c.p_num + 1);
	info->can_eat = (int *)ft_memalloc(data->c.p_num + 1);
	info->is_fork_clean = (int *)ft_memalloc(data->c.p_num + 1);
}

void	init_threads(t_args *args, t_args *arr)
{
	int		i;
	
	pthread_create(info, NULL, monitor, data);
	i = 0;
	while (++i < data->c->p_num + 1)
	{
		arr[i].id = i;
		arr[i].last_meal = get_current_time_ms();
		pthread_create(&args.phils[i], NULL, philosopher, &arr[i]);
	}
	
}

int		main(int ac, char **av)
{
	t_data	data;
	int		i;

	parse_const(&data, av, ac);
	init_args_n_arr(&data);
	init_monitor(&data);
	init_philosophers(&data);
	i = 0;
	pthread_join(monitor, NULL);
	while (++i < data->c->p_num + 1)
	{
		pthread_join(args.phils[i], NULL);
	}
	
	exit(0);
	return (0);
}
