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
	if (is_left_fork)
	{
		return (id);
	}
	else
	{
		if (id == forks_number)
		{
			return (1);
		}
		return (id + 1);
	}
}

void	put_forks(int left_fork, int right_fork, t_data *data)
{
	pthread_mutex_unlock(&data->can_take_fork_mutexes[left_fork]);
	pthread_mutex_unlock(&data->can_take_fork_mutexes[right_fork]);
	release_fork(data, left_fork);
	release_fork(data, right_fork);
	increase_ended_meal(data);
}

