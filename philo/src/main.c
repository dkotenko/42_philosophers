/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/29 19:16:01 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_order_arrs(t_data *data, int i)
{
	while (--i > 0)
	{
		free(data->phi[i].order_arr);
	}
	free(data->c);
	free(data);
	return (1);
}

int	init_philosophers(t_data *data, t_data *data_arr)
{
	int		i;
	t_phi	*curr_p;

	i = 0;
	while (++i < data->c->p_num + 1)
	{
		curr_p = &data->phi[i];
		curr_p->id = i;
		curr_p->left_fork = get_fork_id(i, data->c->p_num, 1);
		curr_p->right_fork = get_fork_id(i, data->c->p_num, 0);
		curr_p->status = THINK;
		curr_p->must_eat_times = data->c->must_eat_times;
		curr_p->order_arr = generate_order_arr(data->c->p_num);
		if (!curr_p->order_arr && free_order_arrs(data, i))
			return (0);
		curr_p->order_start = i - 1;
		ft_memcpy(&data_arr[i], data, sizeof(t_data));
		data_arr[i].my_id = i;
		curr_p->last_meal = get_current_time_ms();
		pthread_create(&data->pthread_phi[i], NULL, philosopher, &data_arr[i]);
		pthread_detach(data->pthread_phi[i]);
	}
	return (1);
}

void	main_routine(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->c->p_num + 1)
		pthread_join(data->pthread_phi[i], NULL);
	while (1)
	{
		if (data->mon->is_death)
		{
			usleep_ms(200);
			break ;
		}	
		if (data->mon->done_num == data->c->p_num)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)ft_memalloc(sizeof(t_data));
	if (!data)
	{
		free_data(data, data->data_arr);
		handle_error(ERR_MALLOC);
		return (1);
	}
	if (!parse_const(data, av, ac) || !is_const_valid(data->c, ac, av))
		return (1);
	data->data_arr = ft_memalloc(sizeof(t_data) * (data->c->p_num + 1));
	if (!init_data(data) || !init_philosophers(data, data->data_arr))
		return (1);
	init_mutexes(data);
	main_routine(data);
	free_all(data, data->data_arr);
	return (0);
}
