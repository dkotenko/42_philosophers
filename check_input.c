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

/*
4 [5] args
number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/

void	parse_arguments(t_args *args, char **av, int ac)
{
	int i;
	int n;

	i = -1;
	while (++i < ac - 1)
	{
		n = ft_atoi(av[i]);
		if (!is_integer(av[i], n) || n <= 0)
			handle_error(string_builder("invalid integer: ", av[i]));  
	}
	args->phil_num = av[1];
	args->time_to_die = av[2];
	args->time_to_eat = av[3];
	args->time_to_sleep = av[4];
	if (ac == 6)
		args->must_eat_times = av[5];
	else
		args->must_eat_times = 0;
}