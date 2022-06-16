/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/16 20:58:16 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <stdio.h>

static void	print_action_more(int phil_num, int action)
{
	if (action == THINK)
	{
		printf("%lld %d is thinking\n",
			get_current_time_us(), phil_num);
	}
	else if (action == DEAD)
	{
		printf("%lld %d died\n",
			get_current_time_us(), phil_num);
	}
	else if (action == DONE)
	{
		printf("%lld %d is done and alive. Congratulations!\n",
			get_current_time_us(), phil_num);
	}
}

void	print_action(sem_t *print, int phil_num, int action, int fork_id)
{
	sem_wait(print);
	if (action == TAKE_FORK)
	{
		printf("%lld %d has taken a fork %d\n",
			get_current_time_us(), phil_num, fork_id);
	}
	else if (action == EAT)
	{
		printf("%lld %d is eating\n",
			get_current_time_us(), phil_num);
	}
	else if (action == SLEEP)
	{
		printf("%lld %d is sleeping\n",
			get_current_time_us(), phil_num);
	}
	else
		print_action_more(phil_num, action);
	sem_post(print);
}

int	print_usage(void)
{
	printf("%sUSAGE: ./philo_n number_of_philosophers time_to_die" \
		   " time_to_eat time_to_sleep \
		   [number_of_times_each_philosopher_must_eat]\n%s", GREEN, RESET);
	return (1);
}
