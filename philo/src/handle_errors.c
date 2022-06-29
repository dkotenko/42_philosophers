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
	return (1);
}

int	handle_error_int(char *message, int d)
{
	printf("%sError: %s: %d%s\n", RED, message, d, RESET);
	return (1);
}

int	handle_error_str(char *message, char *s)
{
	printf("%sError: %s: %s%s\n", RED, message, s, RESET);
	return (1);
}
