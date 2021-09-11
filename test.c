#include <pthread.h>
#include <stdio.h>

void philosopher(void *args)
{
    int id = (int)args;
    sleep(5);
    printf("%d Hello!\n", id);

}

#define PHILOS 2
pthread_t philo[PHILOS];

int main()
{
    int i;
    //pthread_mutex_init (&food_lock, NULL);

    /*for (i = 0; i < PHILOS; i++)
        pthread_mutex_init (&fork[i], NULL); */
    for (i = 0; i < PHILOS; i++) {
        pthread_create (&philo[i], NULL, philosopher, (void *)i);
        printf("\t%d\n", i);
    }
    for (i = 0; i < PHILOS; i++) {
        pthread_join (philo[i], NULL);
    }

    return 0;
    //int forks = get_forks(&args);
    return (0);
}

