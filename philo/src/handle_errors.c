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

int		handle_error(char *message)
{
	printf("%sError: %s%s\n", RED, message, RESET);
	return (1);
}

int		handle_error_int(char *message, int d)
{
	printf("%sError: %s: %d%s\n", RED, message, d, RESET);
	return (1);
}

void	handle_error_malloc()
{
	asm volatile(
	"movl $0x2000001, %eax;"
  	"movl $1, %ebx;"
  	"syscall"
	);
}

int		handle_error_str(char *message, char *s)
{
	printf("%sError: %s: %s%s\n", RED, message, s, RESET);
	return (1);
}

