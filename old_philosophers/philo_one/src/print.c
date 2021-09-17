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

void	print_action_more(long long time, int id, int action)
{
	if (action == THINK)
	{
		printf("%lld %d is thinking\n",
			time, id);
	}
	else if (action == SLEEP)
	{
		printf("%lld %d is sleeping\n",
			time, id);
	}
	else if (action == DEAD)
	{
		printf("%lld %d died\n",
			time, id);
	}
	else if (action == DONE)
	{
		printf("%lld %d is done and alive. Congratulations!\n",
			time, id);
	}
}

void	print_action(t_args *args, long long time, int action, int fork_id)
{
	if (action == TAKE_FORK)
	{
		printf("%lld %d has taken a fork %d\n",
			time, args->id, fork_id);
	}
	else if (action == EAT)
	{
		printf("%lld %d is eating\n",
			time, args->id);
	}
	else
	{
		print_action_more(time, args->id, action);
	}
}

void	print_usage(void)
{
	printf("%sUSAGE: ./philo_n number_of_philosophers time_to_die" \
		   " time_to_eat time_to_sleep" \
		   " [number_of_times_each_philosopher_must_eat]\n%s", GREEN, RESET);
	exit(0);
}
