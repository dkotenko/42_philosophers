/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/16 20:57:17 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	clean_all()
{
	exit(0);
}

t_sem	*create_sem(char *name, int value)
{
	t_sem	*new;

	sem_unlink(name);
	new = (t_sem *)ft_memalloc(sizeof(t_sem));
	new->name = ft_strdup(name);
	new->sem = sem_open(new->name, O_CREAT, S_IRWXU, value);
	return new;
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
		curr_p->left_fork = get_fork_id(i, data->c->p_num, 1);
		curr_p->right_fork = get_fork_id(i, data->c->p_num, 0);
		curr_p->status = THINK;
		curr_p->must_eat_times = data->c->must_eat_times;
		curr_p->last_meal = get_current_time_ms();
	}
}

void	init_data(t_data *data)
{
	int	i;
	char *sem_name;

	data->phi = (t_phi *)ft_memalloc(sizeof(t_phi) * (data->c->p_num + 1));
	data->processes_phi = (pid_t *)ft_memalloc(sizeof(pid_t) * \
			(data->c->p_num + 1));
	data->process_mon = (pid_t *)ft_memalloc(sizeof(pid_t));
	data->forks_sem = (t_sem **)ft_memalloc(sizeof(t_sem *) *
	(data->c->p_num + 1));

	data->done_sem = create_sem("done", 1);
	data->forks_common = create_sem("forks_common", data->c->p_num);
	data->print_sem = create_sem("print", 1);
	data->dead_sem = create_sem("dead", 1);
	data->meals_sem = create_sem("meals_counter", 1);
	//data->forks_common = create_sem("forks common", data->c->p_num);
	i = 0;
	while (++i < data->c->p_num + 1) {
		asprintf(&sem_name, "fork_%d", i);
		data->forks_sem[i] = create_sem(sem_name, 1);
		free(sem_name);
	}
}

void	init_monitor(t_data *data)
{
	data->mon = (t_mon *)ft_memalloc(sizeof(t_mon));
	data->mon->can_take_fork = (int *)ft_memalloc(sizeof(int) *\
	 (data->c->p_num + 1));
	data->mon->order = (t_order *)ft_memalloc(sizeof(t_order));
	data->mon->order->arr = generate_order_arr(data->c->p_num);
	//print_arr(data->mon->can_take_fork, 5);
	//pthread_create(data->pthread_mon, NULL, monitor, data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	ft_memset(&data, 0, sizeof(t_data));
	i = parse_const(&data, av, ac);
	if (i && is_const_valid(data.c, ac, av)) {
		init_data(&data);
		init_monitor(&data);
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


		printf("Result: %d / %d alive\n", 
		data.c->p_num - data.mon->dead_num, data.c->p_num);
	}
	// clean_all();
	wait_n_exit(&data);
}
