/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/25 21:42:40 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data)
{
	data->phi = (t_phi *)ft_memalloc(sizeof(t_phi) * (data->c->p_num + 1));
	data->pthread_phi = (pthread_t *)ft_memalloc(sizeof(pthread_t) * \
			(data->c->p_num + 1));
	data->print_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->done_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->dead_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->forks_mutexes = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t) * (data->c->p_num + 1));
	data->can_take_fork_mutexes = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t) * (data->c->p_num + 1));
}

void	init_monitor(t_data *data)
{
	int	i;

	i = 0;
	data->mon = (t_mon *)ft_memalloc(sizeof(t_mon));
	data->can_take_fork = (int *)ft_memalloc(sizeof(int) * \
	(data->c->p_num + 1));
	while (++i < data->c->p_num + 1)
		data->can_take_fork[i] = AVAILABLE;
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
		curr_p->order = ft_memalloc(sizeof(t_order));
		curr_p->order->arr = generate_order_arr(data->c->p_num);
		curr_p->order->start = i - 1;
		ft_memcpy(&data_arr[i], data, sizeof(t_data));
		data_arr[i].my_id = i;
		curr_p->last_meal = get_current_time_ms();
		pthread_create(&data->pthread_phi[i], NULL, philosopher, &data_arr[i]);
		pthread_detach(data->pthread_phi[i]);
	}
}

void	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(data->print_mutex, NULL) != 0)
		printf("print mutex init error\n");
	if (pthread_mutex_init(data->done_mutex, NULL) != 0)
		printf("done mutex init error\n");
	if (pthread_mutex_init(data->dead_mutex, NULL) != 0)
		printf("dead mutex init error\n");

	i = 0;
	while (++i < data->c->p_num + 1)
	{
		if (pthread_mutex_init(&data->forks_mutexes[i], NULL) != 0)
			printf("fork mutex init error\n");
		if (pthread_mutex_init(&data->can_take_fork_mutexes[i], NULL) != 0)
			printf("fork mutex init error\n");
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_data	*data_arr;
	int		i;

	ft_memset(&data, 0, sizeof(t_data));
	parse_const(&data, av, ac);
	if (!is_const_valid(data.c, ac, av))
		return (1);
	init_data(&data);
	init_monitor(&data);
	data_arr = ft_memalloc(sizeof(t_data) * (data.c->p_num + 1));
	init_philosophers(&data, data_arr);
	init_mutexes(&data);
	i = 0;
	while (++i < data.c->p_num + 1)
		pthread_join(data.pthread_phi[i], NULL);
	while (1)
	{
		if (data.mon->is_death)
			break ;
		if (data.mon->done_num == data.c->p_num)
			break ;
	}
	return (0);
}
