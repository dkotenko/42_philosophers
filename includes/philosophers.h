#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define RED "\033[0;31m"

enum e_actions {
    TAKE_FORK,
    EAT,
    SLEEP,
    THINK,
    DEAD,
    DONE
};

typedef struct	c_args
{
    int 	    	id;
    int 	    	time_to_die;
    int 	    	time_to_eat;
    int 	    	time_to_sleep;
    int 	    	must_eat_times;
    long long       last_meal;
    int             num;
    pthread_t       *phils;
    pthread_mutex_t *forks;
}				t_args;

int	is_integer(char *s, int n);
void	parse_arguments(t_args *args, char **av, int ac);
/*
 * print.c
 */
void print_usage();


/*
 * handle_errors.c
 */
void handle_error(char *message);
void handle_error_int(char *message, int d);
void handle_error_str(char *message, char *s);
void print_action(int phil_num, int action, int fork_id);
void print_usage();

/*
 * ft.c
 */
int         is_integer(char *s, int n);
size_t	    ft_strlen(const char *str);
long long   get_current_time_ms();
void	*ft_memset(void *destination, int c, size_t n);
void	*ft_memalloc(size_t size);
/*
 * main.c
 */
void *philosopher(void *num);
void put_forks (int f1, int f2, pthread_mutex_t *forks);
int is_forks_taken(int id, int first_fork, int second_fork,
    pthread_mutex_t *forks);
#endif