#include "philosophers.h"
#include <sys/time.h>
#include <stdio.h>

void print_action(int phil_num, int action, int fork_id)
{
    printf("%lld %d ", get_current_time_ms(), phil_num);
    if (action == TAKE_FORK)
        printf("has taken a fork %d\n", fork_id);
    else if (action == EAT)
        printf("is eating\n");
    else if (action == SLEEP)
        printf("is sleeping\n");
    else if (action == THINK)
        printf("is thinking\n");
    else if (action == DEAD)
        printf("died\n");
    else if (action == DONE)
        printf("is done and alive. Congratulations!\n");
}

void print_usage()
{
    printf("%sUSAGE: ./philo_n number_of_philosophers time_to_die" \
           " time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n%s", GREEN, RESET);
    exit(0);
}



