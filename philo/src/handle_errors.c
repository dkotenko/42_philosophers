/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/29 19:08:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/syscall.h>

int	handle_error(char *message)
{
	printf("%sError: %s%s\n", RED, message, RESET);
	return (0);
}

int	handle_error_str(char *message, char *s)
{
	printf("%sError: %s: %s%s\n", RED, message, s, RESET);
	return (0);
}

int	set_first_death(t_data *data)
{
	int	is_first;

	is_first = 0;
	pthread_mutex_lock(data->death_mutex);
	if (data->mon->first_death == 0)
	{
		data->mon->first_death = 1;
		is_first = 1;
	}
	pthread_mutex_unlock(data->death_mutex);
	return (is_first);
}

int	is_first_death(t_data *data)
{
	int	val;

	pthread_mutex_lock(data->death_mutex);
	val = data->mon->first_death;
	pthread_mutex_unlock(data->death_mutex);
	return (val);
}
