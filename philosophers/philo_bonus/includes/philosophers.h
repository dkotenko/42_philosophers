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

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdarg.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"

enum e_actions {
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	DONE
};

typedef struct c_args
{
	int			id;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			must_eat_times;
	long long	last_meal;
	int			num;
	sem_t		*lock;
	sem_t		*forks;
	sem_t		*print;
	pid_t		*phils;
}					t_args;

int			is_integer(char *s, int n);
void		parse_arguments(t_args *args, char **av, int ac);

/*
 * print.c
 */
void		print_usage(void);
int			sync_printf(pthread_mutex_t *printf_mutex, const char *format, ...);
void		usleep_ms(long long ms);

/*
 * handle_errors.c
 */
void		handle_error(char *message);
void		handle_error_int(char *message, int d);
void		handle_error_str(char *message, char *s);
void		print_action(sem_t *print, int phil_num, int action,
				int fork_id);
void		print_usage(void);

/*
 * ft.c
 */
int			is_integer(char *s, int n);
size_t		ft_strlen(const char *str);
long long	get_current_time_ms(void);
void		*ft_memset(void *destination, int c, size_t n);
void		*ft_memalloc(size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
/*
 * main.c
 */
void		*philosopher(void *num);
void		wait_n_exit(t_args *args);

#endif