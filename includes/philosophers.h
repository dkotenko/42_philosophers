#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

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

/*
 * print.c
 */
void print_usage();
void handle_error(char *message);
void print_action(int phil_num, int action);
#endif