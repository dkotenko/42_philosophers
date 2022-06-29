/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/29 19:27:55 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosophers(t_data *data)
{
	int		i;
	t_phi	*curr_p;

	i = 0;
	while (++i < data->c->p_num + 1)
	{
		curr_p = &data->phi[i];
		curr_p->id = i;
		curr_p->status = THINK;
		curr_p->must_eat_times = data->c->must_eat_times;
	}
}

int	init_data(t_data *data)
{
	data->phi = (t_phi *)ft_memalloc(sizeof(t_phi) * (data->c->p_num + 1));
	data->processes_phi = (pid_t *)ft_memalloc(sizeof(pid_t) * \
			(data->c->p_num + 1));
	data->pthread_routine = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	data->pthread_monitor = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	if (!data->phi || !data->processes_phi
		|| !data->pthread_monitor || !data->pthread_monitor)
		free_data(data);
	data->forks_common = create_sem("forks_common", data->c->p_num);
	data->print_sem = create_sem("print", 1);
	data->done_sem = create_sem("done", data->c->p_num);
	data->fork_access_sem = create_sem("fork_access", 1);
	return (1);
}

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->c->p_num + 1)
		kill(data->processes_phi[i], 9);
	exit(1);
}

void	start_philosophers(t_data *data)
{
	int	i;	

	i = 0;
	while (++i < data->c->p_num + 1)
	{
		data->processes_phi[i] = fork();
		if (data->processes_phi[i] == 0)
		{
			data->my_id = i;
			philosopher(data);
			exit (0);
		}
		else if (data->processes_phi[i] < 0)
		{
			perror("fork");
			abort();
		}
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)ft_memalloc(sizeof(t_data));
	if (!data)
	{
		handle_error(ERR_MALLOC);
		return (1);
	}
	if (!parse_const(data, av, ac) || !is_const_valid(data->c, ac, av))
		return (1);
	if (!init_data(data))
		return (1);
	init_philosophers(data);
	start_philosophers(data);
	wait_end(data);
	free_all(data);
	return (0);
}
