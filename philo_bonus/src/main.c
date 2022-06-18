/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/18 21:12:52 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_sem	*create_sem(char *name, int value)
{
	t_sem	*new;

	sem_unlink(name);
	new = (t_sem *)ft_memalloc(sizeof(t_sem));
	new->name = ft_strdup(name);
	new->sem = sem_open(new->name, O_CREAT, S_IRWXU, value);
	return (new);
}

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
}

void	wait_forks(t_data *data)
{
	int	i;

	i = -1;
	usleep_ms(200);
	while (++i < data->c->p_num)
	{
		sem_wait(data->done_sem->sem);
	}
	exit(0);
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
	while (++i < data.c->p_num + 1)
	{
		data.my_id = i;
		data.processes_phi[i] = fork();
		if (data.processes_phi[i] < 0)
		{
			perror("fork");
			abort();
		}
		else if (data.processes_phi[i] == 0)
		{
			philosopher(&data);
			exit(0);
		}
	}
	wait_forks(&data);
}
