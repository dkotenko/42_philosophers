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

int	is_mutexes_init(t_data *data)
{
	int	i;
	int	error;

	error = 0;
	error |= pthread_mutex_init(data->print_mutex, NULL);
	error |= pthread_mutex_init(data->done_mutex, NULL);
	error |= pthread_mutex_init(data->death_mutex, NULL);
	i = 0;
	while (++i < data->c->p_num + 1)
	{
		error |= pthread_mutex_init(&data->forks_mutexes[i], NULL);
		error |= pthread_mutex_init(&data->can_take_fork_mutexes[i], NULL);
	}
	if (error)
	{
		handle_error("mutex init");
		return (0);
	}
	return (1);
}

static int	init_and_check(t_data *data)
{
	int	i;

	if (!data->data_arr
		|| !data->phi
		|| !data->pthread_phi
		|| !data->print_mutex
		|| !data->done_mutex
		|| !data->death_mutex
		|| !data->forks_mutexes
		|| !data->can_take_fork_mutexes
		|| !data->mon
		|| !data->can_take_fork)
	{
		free_data(data);
		return (0);
	}
	i = 0;
	while (++i < data->c->p_num + 1)
		data->can_take_fork[i] = AVAILABLE;
	return (1);
}

int	init_data(t_data *data)
{
	data->data_arr = ft_memalloc(sizeof(t_data) * (data->c->p_num + 1));
	data->phi = (t_phi *)ft_memalloc(sizeof(t_phi) * (data->c->p_num + 1));
	data->pthread_phi = (pthread_t *)ft_memalloc(sizeof(pthread_t) * \
			(data->c->p_num + 1));
	data->print_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->done_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->death_mutex = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t));
	data->forks_mutexes = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t) * (data->c->p_num + 1));
	data->can_take_fork_mutexes = (pthread_mutex_t *)ft_memalloc(
			sizeof(pthread_mutex_t) * (data->c->p_num + 1));
	data->mon = (t_mon *)ft_memalloc(sizeof(t_mon));
	data->can_take_fork = (int *)ft_memalloc(sizeof(int) * \
	(data->c->p_num + 1));
	return (init_and_check(data));
}
