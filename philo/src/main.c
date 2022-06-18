/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/18 21:16:45 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data)
{
	data->phi = (t_phi *)ft_memalloc(sizeof(t_phi) * (data->c->p_num + 1));
	data->pthread_phi = (pthread_t *)ft_memalloc(sizeof(pthread_t) * \
			(data->c->p_num + 1));
	data->pthread_mon = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	data->pthread_print = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	data->print_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->done_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->dead_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->meals_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->forks_mutexes = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t) * (data->c->p_num + 1));
}

void	init_monitor(t_data *data)
{
	data->mon = (t_mon *)ft_memalloc(sizeof(t_mon));
	data->mon->can_take_fork = (int *)ft_memalloc(sizeof(int) * \
	(data->c->p_num + 1));
	data->mon->order = (t_order *)ft_memalloc(sizeof(t_order));
	data->mon->order->arr = generate_order_arr(data->c->p_num);
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
	i = data->phi[data->c->p_num].left_fork;
	data->phi[data->c->p_num].left_fork = data->phi[data->c->p_num].right_fork;
	data->phi[data->c->p_num].right_fork = i;
}

void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(data->print_mutex, NULL);
	pthread_mutex_init(data->meals_mutex, NULL);
	pthread_mutex_init(data->done_mutex, NULL);
	pthread_mutex_init(data->dead_mutex, NULL);
	i = 0;
	while (++i < data->c->p_num + 1)
	{
		pthread_mutex_init(&data->forks_mutexes[i], NULL);
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_data	*data_arr;
	int		i;

	ft_memset(&data, 0, sizeof(t_data));
	parse_const(&data, av, ac);
	if (is_const_valid(data.c, ac, av))
	{
		init_data(&data);
		init_monitor(&data);
		data_arr = ft_memalloc(sizeof(t_data) * (data.c->p_num + 1));
		init_philosophers(&data, data_arr);
		init_mutexes(&data);
		set_meal_order(&data, data.mon->can_take_fork);
		pthread_join(*data.pthread_mon, NULL);
		pthread_join(*data.pthread_print, NULL);
		i = 0;
		while (++i < data.c->p_num + 1)
			pthread_join(data.pthread_phi[i], NULL);
		printf("Result: %d / %d alive\n", \
		data.c->p_num - data.mon->dead_num, data.c->p_num);
	}
	exit(0);
	return (0);
}
