/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create2dchararr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 22:02:50 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death(t_p *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	if (death_time <= curr)
	{
		args->is_alive = false;
		print_action(args, curr, DEAD, 0);
	}
}

void	do_sleep(t_p *args)
{
	long long	curr;
	long long	death_time;

	death_time = args->last_meal + args->time_to_die;
	curr = get_current_time_ms();
	print_action(args, curr, SLEEP, 0);
	usleep_ms(llmin(death_time - curr, args->time_to_sleep));
	check_death(args);
}

long long	llmin(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}

void	do_eat(t_p *args, int first_fork, int second_fork)
{
	long long	curr;
	long long	death_time;

	curr = get_current_time_ms();
	args->last_meal = curr;
	death_time = args->last_meal + args->time_to_die;
	print_action(args, curr, EAT, 0);
	usleep_ms(llmin(death_time - curr, args->time_to_eat));
	put_forks(first_fork, second_fork, args->forks);
	check_death(args);
	args->must_eat_times--;
}

void	*philosopher(void *args)
{
	int		first_fork;
	int		second_fork;
	t_p		*p;

	p = (t_p *)args;
	first_fork = get_fork_id(p->id, p->num, 1);
	second_fork = get_fork_id(p->id, p->num, 0);
	while (args->must_eat_times && p->is_alive)
	{
		check_death(args);
		//printf("%d id | %d firsk fork | %d second fork\n", args->id, first_fork, second_fork);
		if (!is_forks_taken(args, first_fork, second_fork))
		{
			//printf("%lld time to die, %d id\n", args->time_to_die, args->id);
			continue ;
		}
			
		do_eat(args, first_fork, second_fork);
		do_sleep(args);
		print_action(args, get_current_time_ms(), THINK, 0);
	}
	check_death(args);
	print_action(args, get_current_time_ms(), DONE, 0);
	exit_thread();
	return (0);
}
