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

static void	print_action_more(int phil_num, int action, long long time)
{
	if (action == THINK)
	{
		printf("%lld %d is thinking\n",
			time, phil_num);
	}
	else if (action == DEAD)
	{
		printf("%lld %d died\n",
			time, phil_num);
	}
	else if (action == DONE)
	{
		printf("%lld %d is done and alive. Congratulations!\n",
			time, phil_num);
	}
}

void	print_action(sem_t *print, int phil_num, int action, long long time)
{
	sem_wait(print);
	if (action == TAKE_FORK)
	{
		printf("%lld %d has taken a fork\n",
			time, phil_num);
	}
	else if (action == EAT)
	{
		printf("%lld %d is eating\n",
			time, phil_num);
	}
	else if (action == SLEEP)
	{
		printf("%lld %d is sleeping\n",
			time, phil_num);
	}
	else
		print_action_more(phil_num, action, time);
	sem_post(print);
}

void	print_usage(void)
{
	printf("%sUSAGE: ./philo_n number_of_philosophers time_to_die" \
		   " time_to_eat time_to_sleep \
		   [number_of_times_each_philosopher_must_eat]\n%s", GREEN, RESET);
	exit(0);
}

void	usleep_ms(long long ms)
{
	usleep(ms * 1000);
}
