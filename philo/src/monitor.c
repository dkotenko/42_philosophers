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
	while (i < size && i + 1 < size)
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
