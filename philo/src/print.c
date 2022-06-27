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
#include <sys/time.h>
#include <stdio.h>

void	print_action_more(int phil_num, int action)
{
	if (action == SLEEP)
	{
		printf("%lld %d is sleeping\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == THINK)
	{
		printf("%lld %d is thinking\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == DEAD)
	{
		printf("%lld %d died\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == DONE)
	{
		printf("%lld %d is done and alive. Congratulations!\n",
			get_current_time_ms(), phil_num);
	}
}

void	print_action(pthread_mutex_t *print_mutex, int phil_num,
int action, int release_lock)
{
	pthread_mutex_lock(print_mutex);
	if (action == TAKE_FORK)
	{
		printf("%lld %d has taken a fork\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == EAT)
	{
		printf("%lld %d is eating\n",
			get_current_time_ms(), phil_num);
	}
	else
	{
		print_action_more(phil_num, action);
	}
	(void)release_lock;
	pthread_mutex_unlock(print_mutex);
}

int	print_usage(void)
{
	printf("%sUSAGE: ./philo_n number_of_philosophers time_to_die" \
	" time_to_eat time_to_sleep" \
	" [number_of_times_each_philosopher_must_eat]\n%s", GREEN, RESET);
	return (1);
}
