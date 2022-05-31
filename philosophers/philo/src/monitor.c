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

void    populate_queue(t_queue *q)
{
    int i;

    i = 0;
    while (i < q->count)
    {
        q->data[i] = i + 1;
        i++;
    }
}

void    monitor(void *monitor_info)
{
    t_mon *info;
    int i;
    int j;
    int eat_started_num;
    int id;

    info = (t_mon *)monitor_info;
    t_queue *q = t_queue_init(info->p_num);
    populate_queue(q);

    while (!is_all_status(info->status, DEAD, info->p_num) && \
    !is_all_status(info->status, DONE, info->p_num)) {
        eat_started_num = 0;
        i = 0;
        while (++j < info->p_num + 1 && eat_started_num <= info->p_num / 2 ) {
            i = q->data[j];
            if (info->p_arr[q->data[i]]->status == THINK) {
                if (info->is_fork_clean[info->p_arr[i]->first_fork] &&
                    info->is_fork_clean[info->p_arr[i]->second_fork]) {
                        info->can_eat[i] = 1;
                        t_queue_add(q, t_queue_get(q));
                        eat_started_num++;
                        //info->is_fork_clean[info->p_arr[i]->first_fork] = 0;
                        //info->is_fork_clean[info->p_arr[i]->second_fork] = 0;
                    }
                }
            } else if (info->p_arr[i]->status == EAT) {
                if (info->can_eat[i]) {
                    info->can_eat[i] = 0;
                }
            }
        }
        
    }
}