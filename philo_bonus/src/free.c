/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/29 19:27:27 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_if(void *p)
{
	if (p)
		free(p);
	return (1);
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

void	free_data(t_data *data)
{
	free_if(data->pthread_routine);
	free_if(data->pthread_monitor);
	free_if(data->processes_phi);
	free_if(data->c);
	free_if(data->phi);
	free_if(data);
}

void	free_all(t_data *data)
{	
	free_sems(data);
	free_data(data);
}
