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

#define MAX 9223372036854775807

static int	ft_atoi(const char *s)
{
	unsigned long long	n;
	int					sign;

	n = 0;
	sign = 1;
	while (*s && ((*s >= 9 && *s <= 13) || *s == ' '))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s && *s >= '0' && *s <= '9')
	{
		n = n * 10 + *s - '0';
		if (n > (unsigned long long)MAX && sign == 1)
			return (-1);
		if (n > (unsigned long long)MAX && sign == -1)
			return (0);
		s++;
	}
	n *= sign;
	return ((int)n);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static size_t	ft_ilen(int n)
{
	size_t		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	is_integer(char *s, int n)
{
	size_t	len;

	len = ft_strlen(s);
	if ((s[0] != '-' && !ft_isdigit(s[0])) || len != ft_ilen(n))
		return (0);
	return (1);
}

int	parse_const(t_data *data, char **av, int ac)
{
	int	i;
	int	n;

	if (ac < 5)
		return (print_usage());
	i = ac;
	while (--i > 0)
	{
		if (ft_strlen(av[i]) == 2 && av[i][0] == '-' && av[i][1] == 'd') {
			data->c->debug = 1;
			continue;
		}
		n = ft_atoi(av[i]);
		if (!is_integer(av[i], n) || n < 0)
			handle_error_str("invalid integer: ", av[i]);
	}
	exit(0);
	data->c = (t_const *)ft_memalloc(sizeof(t_const));
	data->c->p_num = ft_atoi(av[1]);
	data->c->time_to_die = (long long)ft_atoi(av[2]) * 1000LL;
	data->c->time_to_eat = (long long)ft_atoi(av[3]) * 1000LL;
	data->c->time_to_sleep = (long long)ft_atoi(av[4]) * 1000LL;
	if (ac == 6)
		data->c->must_eat_times = ft_atoi(av[5]);
	else
		data->c->must_eat_times = 0x7FFFFFFF;
	return (1);
}
