/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/20 21:27:56 by clala            ###   ########.fr       */
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

void	init_data(t_data *data)
{
	data->phi = (t_phi *)ft_memalloc(sizeof(t_phi) * (data->c->p_num + 1));
	data->processes_phi = (pid_t *)ft_memalloc(sizeof(pid_t) * \
			(data->c->p_num + 1));
	data->forks_common = create_sem("forks_common", data->c->p_num);
	data->print_sem = create_sem("print", 1);
	data->done_sem = create_sem("done", data->c->p_num);
	data->fork_access_sem = create_sem("fork_access", 1);
	data->pthread_timer = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	data->pthread_monitor = (pthread_t *)ft_memalloc(sizeof(pthread_t));
}

void	*timer(void *p)
{
	t_data	*data;

	data = (t_data *)p;
	data->curr_time = get_current_time_us();
	while (1)
	{
		sem_wait(data->done_sem->sem);
		sem_post(data->done_sem->sem);
		data->curr_time = get_current_time_us();
	}
	return (0);
}

void	*monitor(void *p)
{
	t_data	*data;

	data = (t_data *)p;
	usleep_ms(1);
	if (get_current_time_us() - data->curr_time > 1000)
	{
		kill_all(data, 0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	ft_memset(&data, 0, sizeof(t_data));
	parse_const(&data, av, ac);
	is_const_valid(data.c, ac, av);
	init_data(&data);
	init_philosophers(&data);
	i = 0;
	data.processes_phi[i] = 1;
	while (++i < data.c->p_num + 1)
	{
		data.processes_phi[i] = fork();
		if (data.processes_phi[i] == 0)
		{
			philosopher(&data);
			exit (0);
		}
		else
		{
		}
		if (data.processes_phi[i] > 0)
		{
			data.my_id = i;
			

	printf("here\n");
		}
		else if (data.processes_phi[i] < 0)
		{
			perror("fork");
			abort();
		}
	}
	i = 0;
	pthread_create(data.pthread_timer, NULL, timer, &data);
	pthread_create(data.pthread_monitor, NULL, monitor, &data);
	pthread_join(*data.pthread_timer, NULL);
	pthread_join(*data.pthread_monitor, NULL);
	while (++i < data.c->p_num + 1)
	{
		if (data.processes_phi[i] == 0)
		{
			philosopher(&data);
			exit (0);
		} else {
			waitpid(data.processes_phi[i], NULL, WNOHANG);	
		}		
	}
	exit(0);
}
