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
		if (arr[i] == 'E')
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
	t_order	*tmp;

	data = (t_data *)data_pointer;
	while (data->mon->done_num < data->c->p_num)
	{
		if (data->mon->ended_meal)
		{
			if (data->mon->ended_meal % (data->c->p_num / 2) == 0)
			{
				
				//printf("%d\n", data->mon->ended_meal);
				pthread_mutex_lock(data->can_take_fork_mutex);
				/*
				ft_memcpy(data->mon->curr_order, \
					data->mon->next_order, sizeof(t_order));
				*/	
				tmp = *data->mon->curr_order;
				*data->mon->curr_order = *data->mon->next_order;
				*data->mon->next_order = tmp;
				
				pthread_mutex_unlock(data->can_take_fork_mutex);
				
				set_meal_order(data, data->mon->can_take_fork);
				//print_arr(*data->mon->order->curr_order, 6);
				//print_arr(*data->mon->order->next_order, 6);
				reset_ended_meal(data);
			}
		}
		if (data->mon->dead_num)
		{
			clean_all(data);
			break ;
		}
	}
	return (0);
}
