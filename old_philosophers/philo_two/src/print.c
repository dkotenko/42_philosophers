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
	if (action == THINK)
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

void	print_action(pthread_mutex_t *m, int phil_num, int action, int fork_id)
{
	m = m;
	if (action == TAKE_FORK)
	{
		printf("%lld %d has taken a fork %d\n",
			get_current_time_ms(), phil_num, fork_id);
	}
	else if (action == EAT)
	{
		printf("%lld %d is eating\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == SLEEP)
	{
		printf("%lld %d is sleeping\n",
			get_current_time_ms(), phil_num);
	}
	else
		print_action_more(phil_num, action);
}

void	print_usage(void)
{
	printf("%sUSAGE: ./philo_n number_of_philosophers time_to_die" \
		   " time_to_eat time_to_sleep \
		   [number_of_times_each_philosopher_must_eat]\n%s", GREEN, RESET);
	exit(0);
}

int	sync_printf(pthread_mutex_t *printf_mutex, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	pthread_mutex_lock(printf_mutex);
	vprintf(format, args);
	pthread_mutex_unlock(printf_mutex);
	va_end(args);
	return (1);
}