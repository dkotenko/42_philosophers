/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/28 21:38:47 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	is_dead(t_data *data, t_phi *me)
{
	return (me->last_meal + data->c->time_to_die <= get_current_time_us() \
		|| me->status == DEAD);
}

t_sem	*create_sem(char *name, int value)
{
	t_sem	*new;

	sem_unlink(name);
	new = (t_sem *)ft_memalloc(sizeof(t_sem));
	new->name = ft_strdup(name);
	new->sem = sem_open(new->name, O_CREAT, S_IRWXU, value);
	return (new);
}

void	set_final_status(t_data *data, t_phi *me)
{
	if (is_dead(data, me))
	{
		if (me->status == EAT)
		{
			sem_post(data->forks_common->sem);
			sem_post(data->forks_common->sem);
		}
		me->status = DEAD;
		print_action(data->print_sem->sem, me->id, DEAD);
		sem_wait(data->print_sem->sem);
	}
	else
	{
		me->status = DONE;
		print_action(data->print_sem->sem, me->id, DONE);
	}
}

void	*monitor(void *p)
{
	t_data	*data;
	t_phi	*me;

	data = (t_data *)p;
	me = &data->phi[data->my_id];
	while (1)
	{
		usleep(50);
		if (is_dead(data, me))
		{
			set_final_status(data, me);
			free_all(data);
			exit (1);
		}
	}
}
