/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/18 17:53:00 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define MSG "ERROR: invalid integer %s for %s param: must be at least %d\n"

int	is_const_valid(t_const *c, int ac, char **av)
{
	int	is_error;

	is_error = 0;
	if (c->must_eat_times < 0 && ac > 5)
		is_error = printf(MSG, av[5], "\"must eat times\"", 0);
	if (c->p_num < 1)
		is_error = printf(MSG, av[1], "\"philo number\"", 2);
	if (c->p_num > 200)
	{
		is_error = printf("ERROR: too many philosophers, \
		must be less than 201\n");
	}
	if (c->time_to_die < 60 * 1000)
		is_error = printf(MSG, av[2], "\"time to die\"", 60);
	if (c->time_to_eat < 60 * 1000)
		is_error = printf(MSG, av[3], "\"time to eat\"", 60);
	if (c->time_to_sleep < 60 * 1000)
		is_error = printf(MSG, av[4], "\"time to sleep\"", 60);
	return (is_error == 0);
}
