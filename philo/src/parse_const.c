/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_const.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/18 21:17:42 by clala            ###   ########.fr       */
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
	if (c->times[DIE]  < 60 * 1000)
		is_error = printf(MSG, av[2], "\"time to die\"", 60);
	if (c->times[EAT] < 60 * 1000)
		is_error = printf(MSG, av[3], "\"time to eat\"", 60);
	if (c->times[SLEEP] < 60 * 1000)
		is_error = printf(MSG, av[4], "\"time to sleep\"", 60);
	return (is_error == 0);
}

int		populate_const(t_data *data, char **av, int ac)
{
	data->c->p_num = ft_atoi(av[1]);
	data->c->must_eat_times = 0x7FFFFFFF;
	if (ac == 6)
		data->c->must_eat_times = ft_atoi(av[5]);
	data->c->times = ft_memalloc(sizeof(long long) * E_ACTIONS_NUM);
	if (!data->c->times)
	{
		free(data->c);
		free(data);
		return (0);
	}
	data->c->times[EAT] = (long long)ft_atoi(av[3]) * 1000LL;
	data->c->times[SLEEP] = (long long)ft_atoi(av[4]) * 1000LL;
	data->c->times[THINK] = data->c->times[EAT] - THINK_DIFF;
	data->c->times[DIE] = (long long)ft_atoi(av[2]) * 1000LL;
	return (1);
}

int	parse_const(t_data *data, char **av, int ac)
{
	int	i;
	int	n;

	if (ac < 5 || ac > 6)
		return (print_usage());
	data->c = (t_const *)ft_memalloc(sizeof(t_const));
	if (!data->c)
	{
		free(data);
		return (0);
	}
	i = ac;
	while (--i > 0)
	{
		if (ft_strlen(av[i]) == 2 && \
		!ft_memcmp("-d", av[i], sizeof(char) * 2))
			continue ;
		n = ft_atoi(av[i]);
		if (!is_integer(av[i], n) || n < 0)
		{
			handle_error_str("invalid integer: ", av[i]);
			return (0);
		}	
	}
	return (populate_const(data, av, ac));
}
