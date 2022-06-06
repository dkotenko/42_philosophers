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
}

void    populate_queue(t_queue *q, int size)
{
    int i;

    i = 0;
    while (i < size)
    {   
        t_queue_add(q, i + 1);
        i++;
    }
}

void    *monitor(void *data_pointer)
{
    t_data *data;
    int i;
    int j;
    int eat_started_num;

    data = (t_data *)data_pointer;
    t_queue *q = t_queue_init(data->c->p_num);
    populate_queue(q, data->c->p_num);

    while (data->mon->done_num < data->c->p_num) {
        //print_queue(q);
        eat_started_num = 0;
        j = 0;
        while (++j < data->c->p_num + 1 && eat_started_num <= data->c->p_num / 2 ) {
            i = q->data[j];
            if (data->phi[i].status == THINK) {
                if (data->mon->can_take_fork[data->phi[i].left_fork] == 0 &&
                    data->mon->can_take_fork[data->phi[i].right_fork] == 0) {
                        
                        data->mon->can_take_fork[data->phi[i].left_fork] = data->phi[i].id;
                        data->mon->can_take_fork[data->phi[i].right_fork] = data->phi[i].id;
                        t_queue_add(q, t_queue_get(q));
                        eat_started_num++;
                }
            }
        }
    }
    return (0);
}