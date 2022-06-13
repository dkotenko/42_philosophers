#include "philosophers.h"

void	init_arr(t_data *data)
{
    int *arr;
    int i;
    
	arr = data->mon->arr;
    i = -1;
    while (++i < data->c->p_num) {
        arr[i] = i + 1;
    }
}

void    print_arr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void    set_meal_started(t_data *data, int val)
{
    //pthread_mutex_lock(data->meal_mutex);
    data->mon->meal_started = val;
    //pthread_mutex_unlock(data->meal_mutex);
}
void	give_forks(int f1, int f2, int id, t_mon *monitor)
{
	monitor->can_take_fork[f1] = id;
	monitor->can_take_fork[f2] = id;
}

int     get_max_faze(int p_num)
{
    if (p_num == 1) {
        return PHASE_ONE;
    }
    if (p_num % 2 == 0) {
        return PHASE_TWO;
    }
    return PHASE_THREE;
}

static void set_meal_order(t_data *data, int *can_take_fork, int p_num, long long int *last_phase_check)
{
    int     curr_p_ind;
    t_phi   *curr_p;
    int     meal_count;
    int     i;

    i = 0;
    meal_count = p_num / 2;
    while(meal_count--) {
        curr_p_ind = data->mon->curr_phase + i * 2;
        curr_p = &data->phi[curr_p_ind];
        can_take_fork[curr_p->left_fork] = curr_p_ind;
        can_take_fork[curr_p->right_fork] = curr_p_ind;
        i++;
    }
    data->mon->curr_phase++;
    if (data->mon->curr_phase > get_max_faze(data->c->p_num)) {
        data->mon->curr_phase = PHASE_ONE;
    }
    *last_phase_check = get_current_time_us();
}

void    *monitor(void *data_pointer)
{
    t_data *data;
    long long last_phase_check;
    
    data = (t_data *)data_pointer;
    data->mon->curr_phase = PHASE_ONE;
    set_meal_order(data, data->mon->can_take_fork, data->c->p_num, &last_phase_check);
    while (data->mon->done_num < data->c->p_num) {
        //printf("%lld\n",last_phase_check + data->c->time_to_eat / 2);
	    //printf("%lld\n",get_current_time_us());
        if (get_current_time_us() >= last_phase_check + data->c->time_to_eat) {
            set_meal_order(data, data->mon->can_take_fork, data->c->p_num, &last_phase_check);
        }
    }
    return (0);
}