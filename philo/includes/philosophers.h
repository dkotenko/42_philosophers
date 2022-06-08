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

# define here() printf("here\n")

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
} 					t_const;

typedef struct s_mon_info
{
	int				*is_alive;
	int				*can_eat;
	int				*can_take_fork;
	int				done_num;
	int				dead_num;
	int				meal_started;
}					t_mon;

typedef struct s_phi
{
	int				id;
	int				is_alive;
	int				left_fork;
	int				right_fork;
	int				status;
	int				must_eat_times;
	long long		last_meal;
}					t_phi;

typedef struct	s_data
{
	t_const			*c;
	t_mon			*mon;
	t_phi			*phi;
	pthread_mutex_t	*done_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_t		*pthread_mon;
	pthread_t		*pthread_phi;
	int				my_id;
}					t_data;

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
int			is_forks_taken(t_data *data, int first_fork, \
	int second_fork, int p_id);
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
void    set_meal_started(t_data *data, int val);
/*
 * monitor.c
 */

void    	*monitor(void *data_pointer);

/*
 * forks.c
 */
void		put_forks(int f1, int f2, t_mon *monitor);
int			get_fork_id(int id, int forks_number, int is_first_fork);
void		usleep_ms(long long ms);
void		take_forks(int f1, int f2, int id, t_mon *monitor);

/*
 * parse_const.c
 */
void	parse_const(t_data *data, char **av, int ac);
#endif