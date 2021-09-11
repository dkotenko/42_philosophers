#include "../includes/philosophers.h"

int *get_forks(t_args *args)
{
    int *forks;

    forks = (int *)malloc(sizeof(int) * args->phil_num);
    if (!forks)
        handle_error("Malloc error\n");
    return (forks);
}

void philosopher() {

}

int main(int ac, char **av)
{
	t_args args;

	parse_arguments(&args, av, ac);
    pthread_mutex_init (&food_lock, NULL);
    for (i = 0; i < PHILOS; i++)
        pthread_mutex_init (&fork[i], NULL);
    for (i = 0; i < PHILOS; i++)
        pthread_create (&philo[i], NULL, philosopher, (void *)i);
    for (i = 0; i < PHILOS; i++)
        pthread_join (philo[i], NULL);
    return 0;
	//int forks = get_forks(&args);
	return (0);
}

#include <pthread.h>

#define FOOD 50

pthread_mutex_t fork[PHILOS];
pthread_t philo[PHILOS];
pthread_mutex_t food_lock;
int sleep_seconds = 0;


void *philosopher(void *num)
{
    int id;
    int i; 
    int left_fork;
    int right_fork;

    id = (int)num;
    printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
    right_fork = id;
    left_fork = id + 1;

    /* Wrap around the forks. */
    if (left_fork == PHILOS)
        left_fork = 0;

    while (f = food_on_table ()) {

        /* Thanks to philosophers #1 who would like to take a nap
         * before picking up the forks, the other philosophers
         * may be able to eat their dishes and not deadlock.
         */
        if (id == 1)
            sleep (sleep_seconds);

        get_fork(id, right_fork, "right ");
        get_fork(id, left_fork, "left");

        printf("Philosopher %d: eating.\n", id);
        usleep(DELAY * (FOOD - f + 1));
        put_forks(left_fork, right_fork);
    }

    printf ("Philosopher %d is done eating.\n", id);
    return (NULL);
}

int food_on_table ()
{
    static int food = FOOD;
    int myfood;

    pthread_mutex_lock (&food_lock);
    if (food > 0) {
        food--;
    }
    myfood = food;
    pthread_mutex_unlock (&food_lock);
    return myfood;
}

void get_fork (int phil, int c, char *hand)
{
    pthread_mutex_lock (&fork[c]);
    printf ("Philosopher %d: got %s fork %d\n", phil, hand, c);
}

void put_forks (int c1, int c2)
{
    pthread_mutex_unlock (&fork[c1]);
    pthread_mutex_unlock (&fork[c2]);
}