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

int	take_forks(t_data *data, int left_fork, int right_fork, int p_id)
{
	pthread_mutex_lock(&data->forks_mutexes[left_fork]);
	print_action(data->print_mutex, p_id, TAKE_FORK, left_fork);
	pthread_mutex_lock(&data->forks_mutexes[right_fork]);
	print_action(data->print_mutex, p_id, TAKE_FORK, right_fork);
	print_action(data->print_mutex, p_id, EAT, 0);
	increase_meals_counter(data->mon, data->meals_mutex, data->c->p_num);
	data->phi[p_id].status = SLEEP;
	return (1);
}

int	is_forks_taken(t_data *data, int left_fork, int right_fork, int p_id)
{
	if (data->c->p_num == 1)
		return (0);
	if (data->mon->can_take_fork[left_fork] == p_id && \
		data->mon->can_take_fork[right_fork] == p_id)
	{
		data->phi[p_id].must_eat_times--;
		take_forks(data, left_fork, right_fork, p_id);
		return (1);
	}
	return (0);
}

void	put_forks(int left_fork, int right_fork, t_data *data)
{
	pthread_mutex_unlock(&data->forks_mutexes[left_fork]);
	pthread_mutex_unlock(&data->forks_mutexes[right_fork]);
}

void	print_arr(int *arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
