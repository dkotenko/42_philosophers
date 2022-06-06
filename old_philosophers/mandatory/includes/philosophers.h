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
# include <stdbool.h>

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define PBUF_SIZE 640

enum e_actions {
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	DONE
};

typedef struct s_args
{
	int				id;
	long long		last_meal;
	int				left_fork;
	int				right_fork;
	pthread_t		*phils;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
}					t_p;

typedef struct s_info
{
	int				must_eat_times;
	t_p				*p_arr;
	int				p_num;
	int				*permissions_to_live;
	int				*permissions_to_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	pthread_t		*phils;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
}					t_info;

int			is_integer(char *s, int n);
void		parse_arguments(t_p *args, char **av, int ac);
/*
 * print.c
 */
void		print_usage(void);

/*
 * handle_errors.c
 */
void		handle_error(char *message);
void		handle_error_int(char *message, int d);
void		handle_error_str(char *message, char *s);
void		print_action(t_p *args, long long time, int action,
				int fork_id);
void		print_usage(void);
void		exit_thread(void);
long long	llmin(long long a, long long b);

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

/*
 * forks.c
 */
void		put_forks(int f1, int f2, pthread_mutex_t *forks);
int			is_forks_taken(t_p *args, int first_fork, int second_fork);
int			get_fork_id(int id, int forks_number, int is_first_fork);
void		usleep_ms(long long ms);
#endif