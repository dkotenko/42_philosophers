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

int	get_fork_id(int id, int forks_number, int is_first_fork)
{
	int	fork_id;

	if (id % 2)
	{
		if (is_first_fork)
			fork_id = id + 1;
		else
			fork_id = id;
	}
	else
	{
		if (is_first_fork)
			fork_id = id;
		else
			fork_id = id + 1;
	}
	if (fork_id > forks_number)
		fork_id -= forks_number;
	return (fork_id);
}

int	is_forks_taken(t_data *data, int first_fork, int second_fork, int p_id)
{
	if (data->mon->can_take_fork[first_fork] == p_id && \
		data->mon->can_take_fork[second_fork] == p_id)
	{	
		print_action(data->printf_mutex, p_id, TAKE_FORK, first_fork);
		print_action(data->printf_mutex, p_id, TAKE_FORK, second_fork);
		return (1);
	}
	return (0);
}

void	put_forks(int f1, int f2, t_mon *monitor)
{
	monitor->can_take_fork[f1] = 0;
	monitor->can_take_fork[f2] = 0;
}
