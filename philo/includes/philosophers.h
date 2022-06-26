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

# define THINK_DIFF 0

enum e_actions {
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	DONE,
	E_ACTIONS_NUM
};

typedef struct s_const {
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_think;
	int				must_eat_times;
	int				p_num;
	int				debug;
	int				*times;
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
	int				ended_meal;
	int				is_death;
	t_order			**curr_order;
	t_order			**next_order;
}					t_mon;

typedef struct s_phi
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				status;
	int				next_status;
	int				must_eat_times;
	long long		last_meal;
	t_order			*order;
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
	pthread_mutex_t	*ended_meal_mutex;
	pthread_mutex_t	*can_take_fork_mutex;
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
int phil_num, int action, int release_lock);

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
int			is_dead(t_data *data, t_phi *me);
void		die(t_data *data, t_phi *me);
void		increase_ended_meal(t_data *data);
void		reset_ended_meal(t_data *data);

/*
** ft_more.c
*/
int			is_integer(char *s, int n);
size_t		ft_ilen(int n);
int			ft_isdigit(int c);
int			ft_atoi(const char *s);
void		set_next_order(t_data *data, t_phi *me);
#endif