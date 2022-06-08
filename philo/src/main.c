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
			(data->c->p_num + 1));
	data->pthread_mon = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	data->printf_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->done_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->dead_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->meal_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
}

void	init_monitor(t_data *data)
{
	data->mon = (t_mon *)ft_memalloc(sizeof(t_mon));
	data->mon->is_alive = (int *)ft_memalloc(sizeof(int) * (data->c->p_num + 1));
	data->mon->can_eat = (int *)ft_memalloc(sizeof(int) * (data->c->p_num + 1));
	data->mon->can_take_fork = (int *)ft_memalloc(sizeof(int) *\
	 (data->c->p_num + 1));
	pthread_create(data->pthread_mon, NULL, monitor, data);
}

void	init_philosophers(t_data *data, t_data *data_arr)
{
	int		i;
	t_phi	*curr_p;
	
	i = 0;
	while (++i < data->c->p_num + 1)
	{
		curr_p = &data->phi[i];
		curr_p->id = i;
		curr_p->left_fork = get_fork_id(i, data->c->p_num, 1);
		curr_p->right_fork = get_fork_id(i, data->c->p_num, 0);
		curr_p->status = THINK;
		curr_p->must_eat_times = data->c->must_eat_times;
		curr_p->last_meal = get_current_time_ms();
		ft_memcpy(&data_arr[i], data, sizeof(t_data));
		data_arr[i].my_id = i;
		pthread_create(&data->pthread_phi[i], NULL, philosopher, &data_arr[i]);
	}
}

int		main(int ac, char **av)
{
	t_data	data;
	t_data *data_arr;
	int		i;

	ft_memset(&data, 0, sizeof(t_data));
	parse_const(&data, av, ac);
	init_data(&data);
	init_monitor(&data);
	data_arr = ft_memalloc(sizeof(t_data) * (data.c->p_num + 1));
	init_philosophers(&data, data_arr);
	i = 0;
	pthread_mutex_init(data.printf_mutex, NULL);
	pthread_mutex_init(data.done_mutex, NULL);
	pthread_mutex_init(data.dead_mutex, NULL);
	pthread_mutex_init(data.meal_mutex, NULL);
	pthread_join(*data.pthread_mon, NULL);
	
	while (++i < data.c->p_num + 1)
	{
		pthread_join(data.pthread_phi[i], NULL);
	}
	printf("Result: %d / %d alive\n", data.c->p_num - data.mon->dead_num, data.c->p_num);
	exit(0);
	return (0);
}
