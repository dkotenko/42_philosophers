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

int	had_a_meal_new(t_data *data, t_phi *me)
{
	long long	meal_end;

	meal_end = get_current_time_us() + data->c->time_to_eat;
	while (get_current_time_us() < meal_end)
	{
		if (is_dead(data, me))
		{
			data->mon->is_death = 1;
		}
		if (data->mon->is_death)
		{
			me->status = DEAD;
			put_forks(me->left_fork, me->right_fork, data);
			return (0);
		}
	}
	put_forks(me->left_fork, me->right_fork, data);
	return (1);
}

int	had_a_nap_new(t_data *data, t_phi *me)
{
	long long	nap_end;

	print_action(data->print_mutex, me->id, SLEEP, 1);
	nap_end = get_current_time_us() + data->c->time_to_sleep;
	while (get_current_time_us() < nap_end)
	{
		if (is_dead(data, me))
		{
			data->mon->is_death = 1;
		}
		if (data->mon->is_death)
		{
			me->status = DEAD;
			return (0);
		}
	}
	return (1);
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
		if (!is_forks_taken(data, me->left_fork, me->right_fork, me->id))
			continue ;
		if (!had_a_meal_new(data, me))
			break ;
		if (!had_a_nap_new(data, me))
			break ;
		print_action(data->print_mutex, me->id, THINK, 1);
		me->status = THINK;
	}
	set_final_status(data, me);
	return (0);
}
