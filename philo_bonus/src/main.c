/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2021/09/12 18:04:08 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	while (args->c.must_eat_times)
	{	
		check_death(args);
		sem_wait(args->lock);
		sem_wait(args->forks);
		print_action(args->print, args->id, TAKE_FORK, 1);
		sem_wait(args->forks);
		print_action(args->print, args->id, TAKE_FORK, 2);
		sem_post(args->lock);
		check_death_with_forks(args);
		print_action(args->print, args->id, EAT, 0);
		usleep_ms(args->c.time_to_eat);
		args->last_meal = get_current_time_us();
		args->c.must_eat_times--;
		sem_post(args->forks);
		sem_post(args->forks);
		print_action(args->print, args->id, SLEEP, 0);
		usleep_ms (args->c.time_to_sleep);
		print_action(args->print, args->id, THINK, 0);
	}
	print_action(args->print, args->id, DONE, 0);
	return (0);
}

void	clean_all()
{
	exit(0);
}

void	init_args_n_arr(t_args *args)
{
	args->phils = (pid_t *)ft_memalloc(sizeof(pid_t) * \
			(args->c.p_num + 1));
	
	sem_unlink("forks");
	args->forks = sem_open("forks", O_CREAT, S_IRWXU, args->c.p_num);
	sem_unlink("lock");
	args->lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
	sem_unlink("print");
	args->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	args->last_meal = get_current_time_us();
}

void	create_sem(char *name, int value)
{
	t_sem	*new;

	sem_unlink(name);
	new = (t_sem *)ft_memalloc(sizeof(t_sem));
	new->name = ft_strdup(name);
	new->sem = sem_open(new->name, O_CREAT, S_IRWXU, value);
	return new;
}

void	init_philosophers(t_data *data, t_data *data_arr)
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
		data_arr[i].my_id = i;
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
	
	data->done_sem = create_sem("done", 1);
	data->print_sem = create_sem("print", 1);
	data->dead_sem = create_sem("dead", 1);
	data->meals_sem = create_sem("meals counter", 1);
	data->forks_common = create_sem("forks common", data->c->p_num);
	i = 0;
	while (++i < data->c->p_num + 1) {
		asprintf(&sem_name, "fork_%d", i);
		data->forks_sem[i] = create_sem(sem_name, 1);
		free(sem_name);
	}
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

		while (++i < args.num + 1)
		{
			args.id = i;
			args.phils[i] = fork();
			if (args.phils[i] < 0)
			{
				perror("fork");
				abort();
			}
			else if (args.phils[i] == 0)
			{
				philosopher(&args);
				exit(0);
			}
		}


		printf("Result: %d / %d alive\n", 
		data.c->p_num - data.mon->dead_num, data.c->p_num);
	}
	clean_all();
	wait_n_exit(&args);
}
