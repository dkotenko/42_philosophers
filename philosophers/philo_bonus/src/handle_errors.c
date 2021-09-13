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

void	handle_error(char *message)
{
	printf("%sError: %s%s", RED, message, RESET);
	exit(0);
}

void	handle_error_int(char *message, int d)
{
	printf("%sError: %s: %d%s", RED, message, d, RESET);
	exit(0);
}

void	handle_error_str(char *message, char *s)
{
	printf("%sError: %s: %s%s", RED, message, s, RESET);
	exit(0);
}

void	wait_n_exit(t_args *args)
{
	int	status;

	while (args->num-- > 0)
		wait(&status);
	exit(0);
}
