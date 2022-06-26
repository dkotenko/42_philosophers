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
	int		*arr;

	arr = (*(data->mon->next_order))->arr;	
	curr_p_ind = 0;
	counter = 0;
	while (++curr_p_ind < data->c->p_num + 1)
	{
		i = ((*(data->mon->next_order))->start + counter) % data->c->p_num;
		if (arr[i] == EAT)
		{
			curr_p = &data->phi[curr_p_ind];
			can_take_fork[curr_p->left_fork] = curr_p_ind;
			can_take_fork[curr_p->right_fork] = curr_p_ind;
		}
		counter++;
	}
	(*(data->mon->next_order))->start--;
	if ((*(data->mon->next_order))->start < 0)
		(*(data->mon->next_order))->start += data->c->p_num;
}

void	set_next_order(t_data *data, t_phi *me)
{
	me->order->start--;
	if (me->order->start < 0)
		me->order->start = data->c->p_num - 1;
}

int	*generate_order_arr(int size)
{
	int	*order_arr;
	int	i;

	order_arr = ft_memalloc(sizeof(int) * size);
	i = 0;
	if (size == 1)
	{
		order_arr[i] = EAT;
		return (order_arr);
	}
	while (i < size)
	{
		order_arr[i] = EAT;
		order_arr[i + 1] = SLEEP;
		i += 2;
	}
	if (size % 2)
	{
		order_arr[size - 1] = SLEEP;
		order_arr[size - 2] = THINK;
	}
	return (order_arr);
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
	(void)data_pointer;
	/*
	t_data	*data;
	t_order	*tmp;

	data = (t_data *)data_pointer;
	
	while (data->mon->done_num < data->c->p_num)
	{
		if (data->mon->dead_num)
		{
			clean_all(data);
			break ;
		}
	}
	*/
	return (0);
}
