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

# define _GNU_SOURCE

# include "libft.h"
# include <pthread.h>

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
	int				debug;
}					t_const;

typedef struct s_order
{
	int				*arr;
	int				start;
}					t_order;

typedef struct s_mon_info
{
	int				*can_take_fork;
	int				done_num;
	int				dead_num;
	int				meal_started;
	int				meals_counter;
	int				start_ordering;
	t_order			*order;
}					t_mon;

typedef struct s_phi
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				status;
	int				must_eat_times;
	long long		last_meal;
}					t_phi;

typedef struct s_data
{
	t_const			*c;
	t_mon			*mon;
	t_phi			*phi;
	pthread_mutex_t	*done_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*meals_mutex;
	pthread_mutex_t	*forks_mutexes;
	pthread_t		*pthread_print;
	pthread_t		*pthread_mon;
	pthread_t		*pthread_phi;
	int				my_id;

}					t_data;

int			is_integer(char *s, int n);
int			is_forks_taken(t_data *data, int left_fork, \
	int right_fork, int p_id);
/*
 * print.c
 */
int			print_usage(void);
void		*printer(void *data_pointer);
/*
 * handle_errors.c
 */
void		handle_error(char *message);
void		handle_error_int(char *message, int d);
void		handle_error_str(char *message, char *s);
void		print_action(pthread_mutex_t *print_mutex, \
int phil_num, int action, int fork_id);

/*
 * main.c
 */
void		*philosopher(void *num);
/*
 * monitor.c
 */

void		*monitor(void *data_pointer);

/*
 * forks.c
 */
void		put_forks(int f1, int f2, t_data *data);
int			get_fork_id(int id, int forks_number, int is_left_fork);
void		usleep_ms(long long ms);
void		give_forks(int f1, int f2, int id, t_mon *monitor);

/*
 * parse_const.c
 */
int			parse_const(t_data *data, char **av, int ac);
int			take_forks(t_data *data, int left_fork, int right_fork, int p_id);
void		set_meal_order(t_data *data, int *can_take_fork);
/*
 * validation.c
 */
int			is_const_valid(t_const *c, int ac, char **av);
long long	get_current_time_ms(void);
long long	get_current_time_us(void);

void		print_arr(int *arr, int size);
int			*generate_order_arr(int size);
void		increase_meals_counter(t_mon *mon, pthread_mutex_t *m, int p_num);
#endif