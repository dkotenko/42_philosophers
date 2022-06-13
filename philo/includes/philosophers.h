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

#define _GNU_SOURCE

# include "dlist.h"
# include <pthread.h>

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

enum e_meal_phases {
	PHASE_ONE	= 1,
	PHASE_TWO	= 2,
	PHASE_THREE	= 3
};

typedef struct s_const {
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_times;
	int				p_num;
	int				debug;
} 					t_const;



typedef struct s_mon_info
{
	int				*is_alive;
	int				*can_eat;
	int				*can_take_fork;
	int				*arr;
	int				done_num;
	int				dead_num;
	int				meal_started;
	int				curr_phase;
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
	t_dlist			*pq;
	pthread_mutex_t	*print_mutex;
}					t_phi;

typedef struct	s_data
{
	t_const			*c;
	t_mon			*mon;
	t_phi			*phi;
	pthread_mutex_t	*done_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t *forks_mutexes;
	pthread_mutex_t *print_mutexes;
	pthread_t		*pthread_print;
	pthread_t		*pthread_mon;
	pthread_t		*pthread_phi;
	t_dlist			*pq;
	int				my_id;

}					t_data;

/*
typedef struct s_queue {
	int *data;  // указатель на данные
	int low;        // указатель на нижнюю границу
	int high;       // указатель на верхнюю границу
	int count;      // количество элементов в очереди
	int max;        // максимальное количество элементов
}
					t_queue;
*/

int			is_integer(char *s, int n);
int			is_forks_taken(t_data *data, int left_fork, \
	int right_fork, int p_id);
/*
 * print.c
 */
int		print_usage(void);
void    *printer(void *data_pointer);
/*
 * handle_errors.c
 */
void		handle_error(char *message);
void		handle_error_int(char *message, int d);
void		handle_error_str(char *message, char *s);
void		print_action(pthread_mutex_t *print_mutex, 
int phil_num, int action, int fork_id);


/*
 * main.c
 */
void		*philosopher(void *num);
void    set_meal_started(t_data *data, int val);
/*
 * monitor.c
 */

void    	*monitor(void *data_pointer);
void    set_meal_started(t_data *data, int val);

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
int		parse_const(t_data *data, char **av, int ac);
int		take_forks(t_data *data, int left_fork, int right_fork, int p_id);

/*
 * validation.c
 */
int			is_const_valid(t_const *c, int ac, char **av);
long long	get_current_time_ms(void);
long long	get_current_time_us(void);


void    print_arr(int *arr, int size);
#endif