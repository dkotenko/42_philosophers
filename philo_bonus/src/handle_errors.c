/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/16 20:25:04 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_error(char *message)
{
	printf("%sError: %s%s\n", RED, message, RESET);
	exit(0);
}

void	handle_error_int(char *message, int d)
{
	printf("%sError: %s: %d%s\n", RED, message, d, RESET);
	exit(0);
}

void	handle_error_str(char *message, char *s)
{
	printf("%sError: %s: %s%s\n", RED, message, s, RESET);
	exit(0);
}

void	wait_n_exit(t_data *data)
{
	int	status;

	while (data->c->p_num-- > 0)
		wait(&status);
	exit(0);
}

void	wait_end(t_data *data)
{
	int		status;
	int		status_counter;
	int		i;

	status = -1;
	status_counter = 0;
	while (status_counter < data->c->p_num)
	{
		i = 0;
		while (++i < data->c->p_num + 1)
		{
			waitpid(data->processes_phi[i], &status, WNOHANG);
			if (status == 256)
				kill_all(data);
			else if (status == 0)
			{
				status_counter++;
				status = -1;
			}
		}		
	}
}
