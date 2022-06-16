#include "philosophers.h"

void    print_arr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void	give_forks(int f1, int f2, int id, t_mon *monitor)
{
	monitor->can_take_fork[f1] = id;
	monitor->can_take_fork[f2] = id;
}

void set_meal_order(t_data *data, int *can_take_fork)
{
    int     curr_p_ind;
    t_phi   *curr_p;
    int     i;
    int     counter;

    curr_p_ind = 0;
    counter = 0;
    i = data->mon->order->start;
    while (++curr_p_ind < data->c->p_num + 1) {
        i = (data->mon->order->start + counter) % data->c->p_num;
        if (data->mon->order->arr[i] == 'E') {
            curr_p = &data->phi[curr_p_ind];
            can_take_fork[curr_p->left_fork] = curr_p_ind;
            can_take_fork[curr_p->right_fork] = curr_p_ind;
        }
        counter++;
    }
    data->mon->order->start--;
    if (data->mon->order->start < 0)
        data->mon->order->start += data->c->p_num;
}

int    *generate_order_arr(int size)
{
    int *order_arr;
    int i;

    order_arr = ft_memalloc(sizeof(int) * size);
    i = 0;
    while (i < size) {
        order_arr[i] = 'E';
        order_arr[i + 1] = 'S';
        i += 2;
    }
    if (size % 2) {
        order_arr[size - 1] = 'S';
        order_arr[size - 2] = 'T';
    }
    return (order_arr);
}

void    increase_meals_counter(t_mon *mon, pthread_mutex_t *m, int p_num)
{
	int temp;

	temp = mon->meals_counter;
	while (1) {
		if (temp == mon->meals_counter) {
			mon->meals_counter++;
			break;
		} else {
			temp = mon->meals_counter;
		}
	}
	if (mon->meals_counter % (p_num / 2) == 0)
        mon->start_ordering = 1;
	/*
    pthread_mutex_lock(m);
    mon->meals_counter++;
    if (mon->meals_counter % (p_num / 2) == 0)
        mon->start_ordering = 1;
    pthread_mutex_unlock(m);
	*/
(void)m;
}

void    *monitor(void *data_pointer)
{
    t_data *data;
    
    data = (t_data *)data_pointer;
    while (data->mon->done_num < data->c->p_num) {
        //printf("%lld\n",last_phase_check + data->c->time_to_eat / 2);
	    //printf("%lld\n",get_current_time_us());
        if (data->mon->start_ordering)
        {
            set_meal_order(data, data->mon->can_take_fork);
			//print_arr(data->mon->can_take_fork, 5);
            data->mon->start_ordering = 0;
        }
    }
    return (0);
}