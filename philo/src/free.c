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

void	free_data(t_data *data)
{
	int	i;

	if (data->c && data->c->p_num && data->phi)
	{
		i = 0;
		while (++i < data->c->p_num + 1)
		{	
			FREE_IF(&data->phi[i].order_arr);
		}
	}
	FREE_IF(&data->c->times);
	FREE_IF(&data->c);
	FREE_IF(&data->mon);
	FREE_IF(&data->phi);
	FREE_IF(&data->can_take_fork);
	FREE_IF(&data->data_arr);
	FREE_IF(&data->done_mutex);
	FREE_IF(&data->death_mutex);
	FREE_IF(&data->print_mutex);
	FREE_IF(&data->forks_mutexes);
	FREE_IF(&data->can_take_fork_mutexes);
	FREE_IF(&data->pthread_phi);
	FREE_IF(&data);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(data->done_mutex);
	pthread_mutex_destroy(data->death_mutex);
	pthread_mutex_destroy(data->print_mutex);
	i = 0;
	while (++i < data->c->p_num + 1)
	{
		pthread_mutex_destroy(&data->forks_mutexes[i]);
		pthread_mutex_destroy(&data->can_take_fork_mutexes[i]);
	}
}

void	free_all(t_data *data)
{
	destroy_mutexes(data);
	free_data(data);
}

void	free_if(void *p)
{
	if (p)
		free(p);
}
