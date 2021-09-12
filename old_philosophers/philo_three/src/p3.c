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

void	wait_n_exit(t_args *args)
{
	int	status;
	int	pid;

	while (args->num-- > 0)
		pid = wait(&status);
	exit(0);
}

void	init_args_n_arr(t_args *args)
{
	int	i;

	args->phils = (pid_t *)ft_memalloc(sizeof(pid_t) * \
			(args->num + 1));
	sem_unlink("forks");
	args->forks = sem_open("forks", O_CREAT, S_IRWXU, args->num);
	sem_unlink("lock");
	args->lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
	sem_unlink("print");
	args->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	args->last_meal = get_current_time_ms();
	i = 0;
}

int	main(int ac, char **av)
{
	t_args	args;
	int		i;

	parse_arguments(&args, av, ac);
	init_args_n_arr(&args);
	i = 0;
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
	wait_n_exit(&args);
}

void	check_death(t_args *args)
{
	if (args->last_meal + \
		(long long)args->time_to_die <= get_current_time_ms())
	{
		print_action(args->print, args->id, DEAD, 0);
		pthread_exit(0);
	}
}

void	*philosopher(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	while (args->must_eat_times)
	{
		check_death(args);
		sem_wait(args->lock);
		sem_wait(args->forks);
		print_action(args->print, args->id, TAKE_FORK, 1);
		sem_wait(args->forks);
		sem_post(args->lock);
		print_action(args->print, args->id, TAKE_FORK, 2);
		print_action(args->print, args->id, EAT, 0);
		args->last_meal = get_current_time_ms();
		usleep(args->time_to_eat);
		args->must_eat_times--;
		sem_post(args->forks);
		sem_post(args->forks);
		print_action(args->print, args->id, SLEEP, 0);
		usleep (args->time_to_sleep);
		print_action(args->print, args->id, THINK, 0);
	}
	print_action(args->print, args->id, DONE, 0);
	return (0);
}
