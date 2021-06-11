#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct	c_args
{
	int 		phil_num;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		must_eat_times;
}				t_args;


number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int	is_integer(char *s, int n);
#endif