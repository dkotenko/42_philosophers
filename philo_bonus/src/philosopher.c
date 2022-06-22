/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/21 20:56:31 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

void	do_eat(t_data *data, long long diff, t_phi *me)
{
	if (diff >= 0)
	{
		usleep(diff);
		me->status = DEAD;
	}
	else
	{	
		data->phi[me->id].must_eat_times--;
		data->phi[me->id].status = SLEEP;
		usleep(data->c->time_to_eat - (get_current_time_us() - me->last_meal));
	}
}

int	had_a_meal(t_data *data, t_phi *me)
{
	long long	diff;

	sem_wait(data->fork_access_sem->sem);
	sem_wait(data->forks_common->sem);
	print_action(data->print_sem->sem, me->id, TAKE_FORK);
	if (data->c->p_num < 2)
	{
		sem_post(data->fork_access_sem->sem);
		return (data->phi[me->id].status = DEAD);
	}
	sem_wait(data->forks_common->sem);
	sem_post(data->fork_access_sem->sem);
	print_action(data->print_sem->sem, me->id, TAKE_FORK);
	print_action(data->print_sem->sem, me->id, EAT);
	diff = get_current_time_us() - me->last_meal - data->c->time_to_die;
	me->last_meal = get_current_time_us();
	do_eat(data, diff, me);
	sem_post(data->forks_common->sem);
	sem_post(data->forks_common->sem);
	return (1);
}

int	had_a_nap(t_data *data, t_phi *me)
{
	long long	diff;

	print_action(data->print_sem->sem, me->id, SLEEP);
	diff = get_current_time_us() - me->last_meal - data->c->time_to_die;
	if (diff >= 0)
	{
		usleep(diff);
		me->status = DEAD;
		return (0);
	}
	else
	{
		usleep(data->c->time_to_sleep);
	}
	return (1);
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
		//kill_all(data);
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
		if(is_dead(data, me))
		{
			set_final_status(data, me);
			exit (1);
		}
			
	}
	return (0);
}

void	*routine(void *p)
{
	t_data	*data;
	t_phi	*me;

	data = (t_data *)p;
	me = &data->phi[data->my_id];
	while (me->must_eat_times && me->status != DEAD)
	{
		
		had_a_meal(data, me);
		had_a_nap(data, me);
		print_action(data->print_sem->sem, me->id, THINK);
		me->status = THINK;
	}
	set_final_status(data, me);
	exit (0);
	return (0);
}

void	*philosopher(t_data *data)
{
	t_phi	*me;

	me = &data->phi[data->my_id];
	me->id = data->my_id;
	me->status = THINK;
	me->last_meal = get_current_time_us();
	pthread_create(data->pthread_monitor, NULL, monitor, data);
	pthread_create(data->pthread_monitor, NULL, routine, data);
	pthread_join(*data->pthread_routine, NULL);
	pthread_join(*data->pthread_monitor, NULL);
	return (0);
}
