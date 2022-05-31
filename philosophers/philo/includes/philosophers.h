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

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"

enum e_actions {
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	ALIVE,
	DEAD,
	DONE,
	E_ACTIONS_NUM
};

typedef struct s_const {
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_times;
	int				p_num;
} t_const;

typedef struct c_args
{
	t_const			c;
	int				id;
	int				is_alive;
	int				left_fork;
	int				right_fork;
	int				status;
	long long		last_meal;
	pthread_mutex_t	*printf_mutex;
}					t_args;

typedef struct c_mon_info
{
	int				p_num;
	int				*is_alive;
	int				*can_eat;
	int				*is_fork_clean;
}					t_mon_info;

typedef struct s_queue {
	int *data;  // указатель на данные
	int low;        // указатель на нижнюю границу
	int high;       // указатель на верхнюю границу
	int count;      // количество элементов в очереди
	int max;        // максимальное количество элементов
}					t_queue;

t_queue		*t_queue_init (size_t size);
void		t_queue_add (t_queue *q, int a);
int			t_queue_get (t_queue *q);

int			is_integer(char *s, int n);
void		parse_arguments(t_args *args, char **av, int ac);
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
void		print_action(pthread_mutex_t *m, int phil_num, int action,
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

/*
 * forks.c
 */
void		put_forks(int f1, int f2, pthread_mutex_t *forks);
int			is_forks_taken(t_args *args, int first_fork, int second_fork);
int			get_fork_id(int id, int forks_number, int is_first_fork);
void		usleep_ms(long long ms);
#endif