/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/25 18:41:15 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_data *data, t_phi *me)
{
	return (me->last_meal + data->c->time_to_die <= get_current_time_us() \
		|| me->status == DEAD);
}

void	die(t_data *data, t_phi *me)
{
	me->status = DEAD;
	data->mon->is_death = 1;
}

void	increase_ended_meal(t_data *data)
{
	pthread_mutex_lock(data->ended_meal_mutex);
	data->mon->ended_meal++;
	pthread_mutex_unlock(data->ended_meal_mutex);
}

void	reset_ended_meal(t_data *data)
{
	pthread_mutex_lock(data->ended_meal_mutex);
	data->mon->ended_meal = 0;
	pthread_mutex_unlock(data->ended_meal_mutex);
}
				
