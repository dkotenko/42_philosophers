/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_const.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/18 18:05:22 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_meal_order(t_data *data, int *can_take_fork)
{
	int		curr_p_ind;
	t_phi	*curr_p;
	int		i;
	int		counter;

	curr_p_ind = 0;
	counter = 0;
	while (++curr_p_ind < data->c->p_num + 1)
	{
		i = (data->mon->order->start + counter) % data->c->p_num;
		if (data->mon->order->arr[i] == 'E')
		{
			curr_p = &data->phi[curr_p_ind];
			can_take_fork[curr_p->left_fork] = curr_p_ind;
			can_take_fork[curr_p->right_fork] = curr_p_ind;
		}
		counter++;
	}
	data->mon->order->start--;
	if (data->mon->order->start < 0)
		data->mon->order->start += data->c->p_num;
}

int	*generate_order_arr(int size)
{
	int	*order_arr;
	int	i;

	order_arr = ft_memalloc(sizeof(int) * size);
	i = 0;
	if (size == 1)
	{
		order_arr[i] = 'E';
		return (order_arr);
	}
	while (i < size)
	{
		order_arr[i] = 'E';
		order_arr[i + 1] = 'S';
		i += 2;
	}
	if (size % 2)
	{
		order_arr[size - 1] = 'S';
		order_arr[size - 2] = 'T';
	}
	return (order_arr);
}

void	increase_meals_counter(t_mon *mon, pthread_mutex_t *m, int p_num)
{
	int	temp;

	temp = mon->meals_counter;
	while (1)
	{
		if (temp == mon->meals_counter)
		{
			mon->meals_counter++;
			break ;
		}
		else
		{
			temp = mon->meals_counter;
		}
	}
	if (mon->meals_counter % (p_num / 2) == 0)
		mon->start_ordering = 1;
	(void)m;
}

void	clean_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->c->p_num + 1)
	{
		pthread_detach(data->pthread_phi[i]);
		pthread_mutex_unlock(&data->forks_mutexes[i]);
		pthread_mutex_destroy(&data->forks_mutexes[i]);
	}
}

void	*monitor(void *data_pointer)
{
	t_data	*data;

	data = (t_data *)data_pointer;
	while (data->mon->done_num < data->c->p_num)
	{
		if (data->mon->start_ordering)
		{
			set_meal_order(data, data->mon->can_take_fork);
			data->mon->start_ordering = 0;
		}
		if (data->mon->dead_num)
		{
			memset(data->mon->can_take_fork, 0, \
sizeof(int) * (data->c->p_num + 1));
			clean_all(data);
			break ;
		}
	}
	return (0);
}
