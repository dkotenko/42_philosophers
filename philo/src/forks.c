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

int	get_fork_id(int id, int forks_number, int is_left_fork)
{
	if (is_left_fork) {
		return id;
	} else {
		if (id == forks_number) {
			return (1);
		}
		return id + 1;
	}
}

int	is_forks_taken(t_data *data, int left_fork, int right_fork, int p_id)
{
	if (data->mon->can_take_fork[left_fork] == p_id && \
		data->mon->can_take_fork[right_fork] == p_id)
	{	
		print_action(data->printf_mutex, p_id, TAKE_FORK, left_fork);
		print_action(data->printf_mutex, p_id, TAKE_FORK, right_fork);
		return (1);
	}
	return (0);
}

int		take_forks(t_data *data, int left_fork, int right_fork, int p_id)
{
	if (p_id < data->c->p_num) {
		if (!pthread_mutex_lock(&data->forks_mutexes[left_fork])) {
			if (!pthread_mutex_lock(&data->forks_mutexes[right_fork])) {
				return (1);
			} else {
				pthread_mutex_unlock(&data->forks_mutexes[left_fork]);
			}
		}
	} else {
		if (!pthread_mutex_lock(&data->forks_mutexes[right_fork])) {
			if (!pthread_mutex_lock(&data->forks_mutexes[left_fork])) {
				return (1);
			} else {
				pthread_mutex_unlock(&data->forks_mutexes[right_fork]);
			}
		}
	}
	return (0);
}

void	put_forks(int left_fork, int right_fork, t_data *data)
{
	pthread_mutex_unlock(&data->forks_mutexes[right_fork]);
	pthread_mutex_unlock(&data->forks_mutexes[left_fork]);
}

void	give_forks(int f1, int f2, int id, t_mon *monitor)
{
	monitor->can_take_fork[f1] = id;
	monitor->can_take_fork[f2] = id;
}