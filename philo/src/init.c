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

void	init_data(t_data *data)
{
	int	i;
	
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
	i = 0;
	data->mon = (t_mon *)ft_memalloc(sizeof(t_mon));
	data->can_take_fork = (int *)ft_memalloc(sizeof(int) * \
	(data->c->p_num + 1));
	while (++i < data->c->p_num + 1)
		data->can_take_fork[i] = AVAILABLE;
}