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

void	check_death(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		print_action(args->print, args->id, DEAD, curr);
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
		print_action(args->print, args->id, DEAD, curr);
		pthread_exit(0);
	}
	else if (death_time <= curr + args->time_to_eat)
	{
		usleep_ms(curr + args->time_to_eat - death_time);
		sem_post(args->forks);
		sem_post(args->forks);
		print_action(args->print, args->id, DEAD, curr);
		pthread_exit(0);
	}
}

void	do_sleep(t_args *args)
{
	long long	curr;
	long long	death_time;

	print_action(args->print, args->id, SLEEP, get_current_time_ms());
	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		print_action(args->print, args->id, DEAD, curr);
		pthread_exit(0);
	}
	else if (death_time <= curr + args->time_to_eat)
	{
		usleep_ms(curr + args->time_to_sleep - death_time);
		print_action(args->print, args->id, DEAD, curr);
		pthread_exit(0);
	}
	usleep_ms(args->time_to_sleep);
}

void	do_eat(t_args *args)
{
	print_action(args->print, args->id, EAT, get_current_time_ms());
	check_death_with_forks(args);
	usleep_ms(args->time_to_eat);
	args->last_meal = get_current_time_ms();
	sem_post(args->forks);
	sem_post(args->forks);
	args->must_eat_times--;
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
		print_action(args->print, args->id, TAKE_FORK, get_current_time_ms());
		sem_wait(args->forks);
		print_action(args->print, args->id, TAKE_FORK, get_current_time_ms());
		sem_post(args->lock);
		do_eat(args);
		do_sleep(args);
		print_action(args->print, args->id, THINK, get_current_time_ms());
		usleep_ms (args->time_to_think);
	}
	check_death(args);
	print_action(args->print, args->id, DONE, 0);
	pthread_exit(0);
	return (0);
}
