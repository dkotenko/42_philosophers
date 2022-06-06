#include "philosophers.h"

int is_all_status(int *states, int state, int p_num)
{
    while (p_num > 0) {
        if (states[p_num--] != state) {
            return (0);
        }
    }
    return (1);
}

void    print_queue(t_queue *q)
{
    int i;

    i = 0;
    while (i < q->count) {
        printf("%d ", q->data[i++]);
    }
    printf("\n");
    printf("%d - low, %d - high, %d - count, %d - max\n", q->low, q->high, q->count, q->max);
    
}

void    populate_queue(t_queue *q, int size)
{
    int i;

    i = 0;
    while (i < size)
    {   
        t_queue_add(q, i + 1);
        print_queue(q);
        i++;
    }
}

void    *monitor(void *data_pointer)
{
    t_data *data;
    int i;
    int j;
    int k;
    int eat_started_num;

    data = (t_data *)data_pointer;
    t_queue *q = t_queue_init(data->c->p_num);
    populate_queue(q, data->c->p_num);
    while (data->mon->done_num < data->c->p_num) {
        eat_started_num = 0;
        k = -1;
        j = q->high;
        while (++k < data->c->p_num && eat_started_num <= data->c->p_num / 2 ) {
            i = q->data[j];
            if (data->phi[i].status == THINK) {
                if (data->mon->can_take_fork[data->phi[i].left_fork] == 0 &&
                    data->mon->can_take_fork[data->phi[i].right_fork] == 0) {
                        
                        data->mon->can_take_fork[data->phi[i].left_fork] = data->phi[i].id;
                        data->mon->can_take_fork[data->phi[i].right_fork] = data->phi[i].id;
                        //print_queue(q);
                        int first = t_queue_get(q);
                        //printf("first - %d\n", first);
                        t_queue_add(q, first);
                        //print_queue(q);
                        eat_started_num++;
                }
            }
            j = j - 1 < 0 ? q->count - 1 : j - 1;
        }
    }
    return (0);
}