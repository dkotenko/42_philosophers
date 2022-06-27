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
#include <limits.h>

# define NEXT_STATUS me->order->arr[me->order->start]

int	had_an_action(t_data *data, t_phi *me, int action)
{
	long long	action_end;
	long long	action_time;

	action_time = data->c->times[action];
	print_action(data->print_mutex, me->id, action, 1);
	action_end = get_current_time_us() + action_time;
	while (get_current_time_us() < action_end)
	{
		if (is_dead(data, me))
			data->mon->is_death = 1;
		if (data->mon->is_death)
		{
			if (action == EAT)
				put_forks(me->left_fork, me->right_fork, data);
			me->status = DEAD;
			return (0);
		}
		usleep(MIN_WAIT);
	}
	if (action == EAT)
		put_forks(me->left_fork, me->right_fork, data);
	set_next_order(data, me);
	me->status = NEXT_STATUS;
	return (!is_dead(data, me));
}

void	set_final_status(t_data *data, t_phi *me)
{
	if (is_dead(data, me))
	{
		me->status = DEAD;
		print_action(data->print_mutex, me->id, DEAD, 0);
		pthread_mutex_lock(data->dead_mutex);
		data->mon->dead_num++;
		pthread_mutex_unlock(data->dead_mutex);
	}
	else
	{
		me->status = DONE;
		print_action(data->print_mutex, me->id, DONE, 1);
	}
	me->last_meal = LLONG_MAX;
	pthread_mutex_lock(data->done_mutex);
	data->mon->done_num++;
	pthread_mutex_unlock(data->done_mutex);
}

int	take_forks(t_data *data, int left_fork, int right_fork, int p_id)
{
	while (1)
	{
		if (is_fork_available(data, left_fork))
		{
			pthread_mutex_lock(&data->forks_mutexes[left_fork]);
			if (is_fork_available(data, right_fork))
			{	
				pthread_mutex_lock(&data->forks_mutexes[right_fork]);
				occupy_fork(data, left_fork);
				occupy_fork(data, right_fork);
				print_action(data->print_mutex, p_id, TAKE_FORK, 1);
				print_action(data->print_mutex, p_id, TAKE_FORK, 1);
				return (1);
			}
			else
				pthread_mutex_unlock(&data->forks_mutexes[left_fork]);
		}
		if (is_dead(data, &data->phi[data->my_id]))
			data->mon->is_death = 1;
		if (data->mon->is_death)
		{
			data->phi[data->my_id].status = DEAD;
			return (0);
		}
		usleep(MIN_WAIT);
	}
	data->phi[p_id].must_eat_times--;
	data->phi[p_id].last_meal = get_current_time_us();
	return (1);
}

void	*philosopher(void *data_pointer)
{
	t_data		*data;
	t_phi		*me;

	data = (t_data *)data_pointer;
	me = &data->phi[data->my_id];
	me->id = data->my_id;
	me->status = THINK;
	me->last_meal = get_current_time_us();
	while (me->must_eat_times && me->status != DEAD)
	{
		if (is_dead(data, me))
			break ;
		if (NEXT_STATUS == EAT)
		{
			if (!(take_forks(data, me->left_fork, me->right_fork, me->id)))
				break ;

			if (!had_an_action(data, me, NEXT_STATUS))
				break ;
		}
		else if (NEXT_STATUS == SLEEP || NEXT_STATUS == THINK)
		{
			if (!had_an_action(data, me, NEXT_STATUS))
				break ;
		}
	}
	set_final_status(data, me);
	return (0);
}
