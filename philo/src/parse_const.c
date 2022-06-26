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

void	populate_const(t_data *data, char **av, int ac)
{
	data->c->p_num = ft_atoi(av[1]);
	data->c->time_to_die = (long long)ft_atoi(av[2]) * 1000LL;
	data->c->time_to_eat = (long long)ft_atoi(av[3]) * 1000LL;
	data->c->time_to_sleep = (long long)ft_atoi(av[4]) * 1000LL;
	data->c->time_to_think = data->c->time_to_eat - THINK_DIFF;
	data->c->must_eat_times = 0x7FFFFFFF;
	if (ac == 6)
		data->c->must_eat_times = ft_atoi(av[5]);
	data->c->times = ft_memalloc(sizeof(int) * E_ACTIONS_NUM);
	data->c->times[EAT] = data->c->time_to_eat;
	data->c->times[SLEEP] = data->c->time_to_sleep;
	data->c->times[THINK] = data->c->time_to_think;
}

int	parse_const(t_data *data, char **av, int ac)
{
	int	i;
	int	n;

	if (ac < 5 || ac > 6)
		return (print_usage());
	data->c = (t_const *)ft_memalloc(sizeof(t_const));
	i = ac;
	while (--i > 0)
	{
		if (ft_strlen(av[i]) == 2 && \
		!ft_memcmp("-d", av[i], sizeof(char) * 2))
			continue ;
		n = ft_atoi(av[i]);
		if (!is_integer(av[i], n) || n < 0)
			handle_error_str("invalid integer: ", av[i]);
	}
	populate_const(data, av, ac);
	return (1);
}
