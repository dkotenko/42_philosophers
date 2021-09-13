/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2021/09/12 16:19:40 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_args_n_arr(t_args *args, t_args *arr)
{
	int	i;

	args->phils = (pthread_t *)ft_memalloc(sizeof(pthread_t) * \
			(args->num + 1));
	sem_unlink("forks");
	args->forks = sem_open("forks", O_CREAT, S_IRWXU, args->num);
	sem_unlink("lock");
	args->lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
	sem_unlink("print");
	args->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	args->last_meal = get_current_time_ms();
	i = 0;
	while (++i < args->num + 1)
	{
		ft_memcpy(&arr[i], args, sizeof(t_args));
	}
}

int	main(int ac, char **av)
{
	t_args	args;
	int		i;
	t_args	*arr;

	parse_arguments(&args, av, ac);
	arr = (t_args *)ft_memalloc(sizeof(t_args) * (args.num + 1));
	init_args_n_arr(&args, arr);
	i = 0;
	while (++i < args.num + 1)
	{
		arr[i].id = i;
		pthread_create(&args.phils[i], NULL, philosopher, &arr[i]);
	}
	i = 0;
	while (++i < args.num + 1)
	{
		pthread_join(args.phils[i], NULL);
	}
	exit(0);
	return (0);
}

void	check_death(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		print_action(args->print, args->id, DEAD, 0);
		pthread_exit(0);
	}
	else if (death_time <= curr + args->time_to_eat)
	{
		usleep_ms(curr + args->time_to_eat - death_time);
		print_action(args->print, args->id, DEAD, 0);
		pthread_exit(0);
	}
}

void	check_death_with_forks(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		sem_post(args->forks);
		sem_post(args->forks);
		print_action(args->print, args->id, DEAD, 0);
		pthread_exit(0);
	}
	else if (death_time <= curr + args->time_to_eat)
	{
		sem_post(args->forks);
		sem_post(args->forks);
		usleep_ms(curr + args->time_to_eat - death_time);
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
		print_action(args->print, args->id, TAKE_FORK, 2);
		sem_post(args->lock);
		check_death_with_forks(args);
		print_action(args->print, args->id, EAT, 0);
		usleep_ms(args->time_to_eat);
		args->last_meal = get_current_time_ms();
		args->must_eat_times--;
		sem_post(args->forks);
		sem_post(args->forks);
		print_action(args->print, args->id, SLEEP, 0);
		usleep_ms (args->time_to_sleep);
		print_action(args->print, args->id, THINK, 0);
	}
	print_action(args->print, args->id, DONE, 0);
	return (0);
}
