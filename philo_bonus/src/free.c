/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/28 21:33:42 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data)
{
	free(data->c);
	free(data->phi);
	free(data);
}

void	free_and_destroy_mutex(pthread_mutex_t *m)
{
	pthread_mutex_destroy(m);
	free(m);
}

void	free_sem(t_sem *sem)
{
	sem_unlink(sem->name);
	free(sem->name);
	free(sem);
}

void	free_sems(t_data *data)
{
	free_sem(data->print_sem);
	free_sem(data->forks_common);
	free_sem(data->done_sem);
	free_sem(data->fork_access_sem);
}

void	free_all(t_data *data)
{
	if (data->pthread_routine)
		free(data->pthread_routine);
	if (data->pthread_monitor)
		free(data->pthread_monitor);
	free(data->processes_phi);
	free_sems(data);
	free_data(data);
}
