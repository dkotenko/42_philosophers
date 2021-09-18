/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2021/09/12 16:19:40 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_args_n_arr(t_args *args, t_args *arr)
{
	int	i;

	args->phils = (pthread_t *)ft_memalloc(sizeof(pthread_t) * \
			(args->num + 1));
	args->time_to_think = args->time_to_die - args->time_to_eat - args->time_to_sleep;
	if (args->time_to_think < 0)
		args->time_to_think = 0;
	sem_unlink("forks");
	args->forks = sem_open("forks", O_CREAT, S_IRWXU, args->num);
	sem_unlink("lock");
	args->lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
	sem_unlink("print");
	args->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	args->last_meal = get_current_time_ms();
	i = 0;
	while (++i < args->num + 1)
	{
		ft_memcpy(&arr[i], args, sizeof(t_args));
	}
}

int	main(int ac, char **av)
{
	t_args	args;
	int		i;
	t_args	*arr;

	parse_arguments(&args, av, ac);
	arr = (t_args *)ft_memalloc(sizeof(t_args) * (args.num + 1));
	init_args_n_arr(&args, arr);
	i = 0;
	while (++i < args.num + 1)
	{
		arr[i].id = i;
		pthread_create(&args.phils[i], NULL, philosopher, &arr[i]);
	}
	i = 0;
	while (++i < args.num + 1)
	{
		pthread_join(args.phils[i], NULL);
	}
	exit(0);
	return (0);
}

