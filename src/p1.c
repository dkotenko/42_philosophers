#include "philosophers.h"

int main(int ac, char **av)
{
	t_args args;
    int i;

	parse_arguments(&args, av, ac);
    args.phils = (pthread_t *)ft_memalloc(sizeof(pthread_t) * (args.num + 1));
    args.forks = (pthread_mutex_t *)ft_memalloc(sizeof(pthread_mutex_t) * 
        (args.num + 1));
    i = 0;
    args.phils[i] = 0;
    args.last_meal = get_current_time_ms();
    printf("%lld\n", args.last_meal);
    while (++i < args.num + 1)
    {
        args.id = i;
        pthread_mutex_init (&args.forks[i], NULL);
        pthread_create (&args.phils[i], NULL, philosopher, &args);
        pthread_join (args.phils[i], NULL);
    }
    
	return (0);
}

int get_fork_id(int id, int forks_number, int is_first_fork)
{
    if (id % 2)
    {
        if (is_first_fork)
            return ((id + 1) % (forks_number + 1));
        else
            return id;
    }
    else
    {
        if (is_first_fork)
            return id;
        else
            return ((id + 1) % (forks_number + 1));
    }
    return (0);
}

void    check_death(t_args *args)
{
    if(args->last_meal + (long long)args->time_to_die < get_current_time_ms())
    {
        printf("%lld %lld\n", args->last_meal, get_current_time_ms());
        print_action(args->id, DEAD, 0);
        pthread_exit(0);
    }
}

void    *philosopher(void *arg)
{
    int first_fork;
    int second_fork;
    t_args *args;

    args = (t_args *)arg;
    printf("%d\n", args->id);
    first_fork = get_fork_id(args->id, args->num, 1);
    second_fork = get_fork_id(args->id, args->num, 0);
    while (args->must_eat_times)
    {
        check_death(args);
        if (!is_forks_taken(args->id, first_fork, second_fork, args->forks))
            continue;
        print_action(args->id, EAT, 0);
        usleep(args->time_to_eat);
        put_forks(first_fork, second_fork, args->forks);
        args->must_eat_times--;
        print_action(args->id, SLEEP, 0);
        usleep (args->time_to_sleep);
        print_action(args->id, THINK, 0);
    }
    print_action(args->id, DONE, 0);
    return (0);
}

/*
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
*/

int is_forks_taken(int id, int first_fork, int second_fork,
    pthread_mutex_t *forks)
{
    int first_result;
    int second_result;

    first_result = pthread_mutex_lock(&forks[first_fork]);
    if (!first_result)
    {
        second_result = pthread_mutex_lock(&forks[second_fork]);
        if (!second_result)
        {
            print_action(id, TAKE_FORK, first_fork);
            print_action(id, TAKE_FORK, second_fork);
            return 1;
        }
        else
            pthread_mutex_unlock(&forks[first_fork]);
    }
    return 0;
}

void put_forks (int f1, int f2, pthread_mutex_t *forks)
{
    pthread_mutex_unlock (&forks[f1]);
    pthread_mutex_unlock (&forks[f2]);
}