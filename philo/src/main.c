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

int	init_philosophers(t_data *data)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (++i < data->c->p_num + 1)
	{
		data->phi[i].id = i;
		data->phi[i].left_fork = get_fork_id(i, data->c->p_num, 1);
		data->phi[i].right_fork = get_fork_id(i, data->c->p_num, 0);
		data->phi[i].status = THINK;
		data->phi[i].must_eat_times = data->c->must_eat_times;
		data->phi[i].order_arr = generate_order_arr(data->c->p_num);
		if (!data->phi[i].order_arr && free_order_arrs(data, i))
			return (0);
		data->phi[i].order_start = i - 1;
		set_first_eat(&data->phi[i]);
		ft_memcpy(&data->data_arr[i], data, sizeof(t_data));
		data->data_arr[i].my_id = i;
		data->phi[i].last_meal = get_current_time_ms();
		err |= pthread_create(
				&data->pthread_phi[i], NULL, philosopher, &data->data_arr[i]);
		err |= pthread_detach(data->pthread_phi[i]);
	}
	return (!err);
}

void	main_routine(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->c->p_num + 1)
		pthread_join(data->pthread_phi[i], NULL);
	while (1)
	{
		if (data->mon->first_death)
		{
			usleep_ms(200);
			break ;
		}	
		if (data->mon->done_num == data->c->p_num)
			break ;
		usleep(MIN_WAIT);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)ft_memalloc(sizeof(t_data));
	if (!data)
	{
		free_data(data);
		handle_error(ERR_MALLOC);
		return (1);
	}
	if (!is_const_parsed(data, av, ac)
		|| !is_const_valid(data->c, ac, av)
		|| !init_data(data)
		|| !init_philosophers(data)
		|| !is_mutexes_init(data))
		return (1);
	main_routine(data);
	free_all(data);
	return (0);
}
