#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>

#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define RED "\033[0;31m"

enum e_actions {
    TAKE_FORK,
    EAT,
    SLEEP,
    THINK,
    DIE
};

typedef struct	c_args
{
    int 		phil_num;
    int 		time_to_die;
    int 		time_to_eat;
    int 		time_to_sleep;
    int 		must_eat_times;
}				t_args;

int	is_integer(char *s, int n);
void	parse_arguments(t_args *args, char **av, int ac);
/*
 * print.c
 */
void print_usage();

void handle_error(char *message);
void handle_error_int(char *message, int d);
void handle_error_str(char *message, char *s);
void print_action(int phil_num, int action);
void print_usage();
size_t		ft_strlen(const char *str);
#endif