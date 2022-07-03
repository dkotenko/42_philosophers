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
# include <stdlib.h>

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"

# define ERR_MALLOC "Can't allocate memory"
# define ERR_MALLOC_SIZE "Invalid malloc size"

# define THINK_DIFF 0
# define MIN_WAIT 30

enum e_fork_status {
	OCCUPIED,
	AVAILABLE,
	FORK_STATUS_NUM
};

enum e_actions {
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	DONE,
	DIE,
	ALIVE,
	E_ACTIONS_NUM
};

typedef struct s_const {
	long long		*times;
	int				must_eat_times;
	int				p_num;
}					t_const;

typedef struct s_mon_info
{
	int				done_num;
	int				first_death;
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
	int				order_start;
	int				*order_arr;
	int				first_eat;
}					t_phi;

typedef struct s_data
{
	t_const			*c;
	t_mon			*mon;
	t_phi			*phi;
	pthread_mutex_t	*done_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks_mutexes;
	pthread_mutex_t	*can_take_fork_mutexes;
	pthread_t		*pthread_phi;
	int				my_id;
	int				*can_take_fork;
	struct s_data	*data_arr;
}					t_data;

int			do_take(t_data *data, int left_fork, int right_fork, int p_id);

/*
 * init.c
 */
int			is_mutexes_init(t_data *data);
int			init_data(t_data *data);

/*
 * forks.c
 */
void		put_forks(int f1, int f2, t_data *data);
int			get_fork_id(int id, int forks_number, int is_left_fork);

/*
 * time.c
 */
void		usleep_ms(long long ms);
long long	get_current_time_ms(void);
long long	get_current_time_us(void);

/*
 * print.c
 */
int			print_usage(void);
void		print_action(t_data *data, int phil_num,
				int action, int first_death);

/*
 * handle_errors.c
 */
int			handle_error(char *message);
int			handle_error_str(char *message, char *s);

/*
 * main.c
 */
void		*philosopher(void *num);

/*
 * monitor.c
 */
int			*generate_order_arr(int size);
int			is_dead(t_data *data, t_phi *me);
void		set_next_order(t_data *data, t_phi *me);
void		set_first_eat(t_phi *me);

/*
 * parse_const.c
 */
int			is_const_parsed(t_data *data, char **av, int ac);

/*
 * forks.c
 */
int			is_fork_available(t_data *data, int fork_num);
void		occupy_fork(t_data *data, int fork_num);
void		release_fork(t_data *data, int fork_num);
int			take_forks(t_data *data, int left_fork, int right_fork, int p_id);
/*
 * validation.c
 */
int			is_const_valid(t_const *c, int ac, char **av);

void		print_arr(int *arr, int size);

/*
** ft_more.c
*/
int			is_integer(char *s, int n);
size_t		ft_ilen(int n);
int			ft_isdigit(int c);
int			ft_atoi(const char *s);

/*
** free.c
*/
void		free_all(t_data *data);
void		free_if(void *p);
void		free_data(t_data *data);
int			is_first_death(t_data *data);
int			set_first_death(t_data *data);

#endif