#include "../philosophers.h"
#include <sys/time.h>
#include <stdio.h>

static long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void print_usage()
{
    printf("USAGE: ./philo_n  number_of_philosophers time_to_die\n"
           "time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
    exit(0);
}

void handle_error(char *message)
{
    printf("Error: %s", message);
    exit(0);
}

void print_action(int phil_num, int action)
{
    printf("%hh %d ", current_timestamp(), phil_num);
    if (action == TAKE_FORK)
        printf("has taken a fork\n");
    else if (action == EAT)
        printf("is eating\n");
    else if (action == SLEEP)
        printf("is sleeping\n");
    else if (action == THINK)
        printf("is thinking\n");
    else if (action == DIE)
        printf("died\n");
}

