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

void	print_action_more(char **s, int phil_num, int action)
{
	if (action == SLEEP)
	{
		asprintf(s, "%lld %d is sleeping\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == THINK)
	{
		asprintf(s, "%lld %d is thinking\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == DEAD)
	{
		asprintf(s, "%lld %d died\n",
			get_current_time_ms(), phil_num);
	}
	else if (action == DONE)
	{
		asprintf(s, "%lld %d is done and alive. Congratulations!\n",
			get_current_time_ms(), phil_num);
	}
}

void	print_action(t_phi *me, int phil_num, int action, int fork_id)
{
	char			*s;
	t_dlist_node	*node;

	if (action == TAKE_FORK)
	{
		asprintf(&s, "%lld %d has taken a fork %d\n",
			get_current_time_ms(), phil_num, fork_id);
	}
	else if (action == EAT)
	{
		asprintf(&s, "%lld %d is eating\n",
			get_current_time_ms(), phil_num);
	}
	else
	{
		print_action_more(&s, phil_num, action);
	}
	node = t_dlist_node_new(s, sizeof(char));
	pthread_mutex_lock(me->print_mutex);
	t_dlist_append(me->pq, node);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_usage(void)
{
	printf("%sUSAGE: ./philo_n number_of_philosophers time_to_die" \
		   " time_to_eat time_to_sleep" \
   " [number_of_times_each_philosopher_must_eat]\n%s", GREEN, RESET);
	exit(0);
}
