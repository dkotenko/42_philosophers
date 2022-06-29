/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/28 20:33:59 by clala            ###   ########.fr       */
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
	free_if(data);
}

void	free_and_destroy_mutex(pthread_mutex_t *m)
{
	pthread_mutex_destroy(m);
	free(m);
}

void	free_all(t_data *data, t_data *data_arr)
{
	int	i;
	
	free_and_destroy_mutex(data->done_mutex);
	free_and_destroy_mutex(data->dead_mutex);
	free_and_destroy_mutex(data->print_mutex);
	i = 0;
	while (++i < data->c->p_num + 1)
	{
		pthread_mutex_destroy(&data->forks_mutexes[i]);
		pthread_mutex_destroy(&data->can_take_fork_mutexes[i]);
	}
	free(data->forks_mutexes);
	free(data->can_take_fork_mutexes);
	free(data->pthread_phi);
	free_data(data, data_arr);
}

void	free_if(void *p)
{
	if (p)
		free(p);
}
