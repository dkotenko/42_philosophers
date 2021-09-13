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
	int	first_result;
	int	second_result;

	first_result = pthread_mutex_lock(&args->forks[first_fork]);
	if (!first_result)
	{
		second_result = pthread_mutex_lock(&args->forks[second_fork]);
		if (!second_result)
		{
			print_action(args->printf_mutex, args->id, TAKE_FORK, first_fork);
			print_action(args->printf_mutex, args->id, TAKE_FORK, second_fork);
			return (1);
		}
		else
			pthread_mutex_unlock(&args->forks[first_fork]);
	}
	return (0);
}

void	put_forks(int f1, int f2, pthread_mutex_t *forks)
{
	pthread_mutex_unlock(&forks[f1]);
	pthread_mutex_unlock(&forks[f2]);
}

void	usleep_ms(long long ms)
{
	usleep(ms * 1000);
}
