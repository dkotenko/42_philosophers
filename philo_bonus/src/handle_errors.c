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
