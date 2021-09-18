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
	printf("%lld\n", death_time - curr);
	if (death_time <= curr)
	{
		print_action(args->print, args->id, DEAD, curr);
		pthread_exit(0);
	}
}

void	do_sleep(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die - 1;
	curr = get_current_time_ms();
	print_action(args->print, args->id, SLEEP, get_current_time_ms());
	usleep_ms(llmin(death_time - curr, args->time_to_sleep));
	check_death(args);
}

void	do_eat(t_args *args)
{
	long long	curr;
	long long	death_time;

	curr = get_current_time_ms();
	args->last_meal = curr;
	death_time = args->last_meal + args->time_to_die - 1;
	print_action(args->print, args->id, EAT, curr);
	usleep_ms(llmin(death_time - curr, args->time_to_eat));
	sem_post(args->forks);
	sem_post(args->forks);
	check_death(args);
	args->must_eat_times--;
}

void	do_think(t_args *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die - 1;
	curr = get_current_time_ms();
	print_action(args->print, args->id, THINK, curr);
	//printf("%lld\n", llmin(death_time - curr, args->time_to_think));
	usleep_ms(llmin(death_time - curr, args->time_to_think));
	check_death(args);
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
		do_think(args);
		//print_action(args->print, args->id, THINK, get_current_time_ms());
	}
	check_death(args);
	print_action(args->print, args->id, DONE, 0);
	pthread_exit(0);
	return (0);
}
