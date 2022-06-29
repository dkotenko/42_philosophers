/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/29 19:10:00 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data, t_data *data_arr)
{
	int	i;

	if (data->c && data->c->p_num && data->phi)
	{
		i = 0;
		while (++i < data->c->p_num + 1)
		{	
			free_if(data->phi[i].order_arr);
		}
	}
	free_if(data->c->times);
	free_if(data->c);
	free_if(data->mon);
	free_if(data->phi);
	free_if(data->can_take_fork);
	free_if(data_arr);
	free_if(data->done_mutex);
	free_if(data->dead_mutex);
	free_if(data->print_mutex);
	free_if(data->forks_mutexes);
	free_if(data->can_take_fork_mutexes);
	free_if(data->pthread_phi);
	free_if(data);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(data->done_mutex);
	pthread_mutex_destroy(data->dead_mutex);
	pthread_mutex_destroy(data->print_mutex);
	i = 0;
	while (++i < data->c->p_num + 1)
	{
		pthread_mutex_destroy(&data->forks_mutexes[i]);
		pthread_mutex_destroy(&data->can_take_fork_mutexes[i]);
	}
}

void	free_all(t_data *data, t_data *data_arr)
{
	destroy_mutexes(data);
	free_data(data, data_arr);
}

void	free_if(void *p)
{
	if (p)
		free(p);
}
