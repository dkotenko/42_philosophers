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

int	is_forks_taken(t_args *args, int first_fork, int second_fork)
{
	if (args->monitor->is_fork_clean[first_fork] && \
		args->monitor->is_fork_clean[second_fork])
	{
		print_action(args->printf_mutex, args->id, TAKE_FORK, first_fork);
		print_action(args->printf_mutex, args->id, TAKE_FORK, second_fork);
		return (1);
	}
	return (0);
}

void	put_forks(int f1, int f2, t_mon *monitor)
{
	monitor->is_fork_clean[f1] = 1;
	monitor->is_fork_clean[f2] = 1;
}

void	usleep_ms(long long ms)
{
	usleep(ms * 1000);
}
