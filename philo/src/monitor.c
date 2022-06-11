#include "philosophers.h"

void    swap(int i, int j, int *number)
{
    int temp;

    temp = number[i];
    number[i] = number[j];
    number[j] = temp;
}

void quicksort(int *A, int len, t_phi *phi) {
  if (len < 2) return;
 
  long long pivot = phi[A[len / 2]].last_meal ;
 
  int i, j;
  for (i = 0, j = len - 1; ; i++, j--) {
    while (phi[A[i]].last_meal < pivot)
        i++;
    while (phi[A[j]].last_meal > pivot)
        j--;
 
    if (i >= j)
        break;
 
    int temp = A[i];
    A[i]     = A[j];
    A[j]     = temp;
  }
 
  quicksort(A, i, phi);
  quicksort(A + i, len - i, phi);
}

int     *init_arr(t_data *data)
{
    int *arr;
    int i;

    arr = (int *)ft_memalloc(sizeof(int) * data->c->p_num);
    i = -1;
    while (++i < data->c->p_num) {
        arr[i] = i + 1;
    }
    return (arr);
}

void    print_arr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void    bubble_sort(int *arr, int size, t_phi *phi)
{
    int sorted;
    int i;
    int phi_index;
    int phi_index_next;

    sorted = 1;
    while (sorted) {
        sorted = 0;
        i = -1;
        while (++i < size - 1) {
            phi_index = arr[i];
            phi_index_next = arr[i + 1];
            if (phi[phi_index].last_meal > phi[phi_index_next].last_meal) {
                swap(i, i + 1, arr);
                sorted = 1;
            }
        }
    }
}

void    set_meal_ended(t_data *data, int val)
{
    while (pthread_mutex_lock(data->meal_mutex))
        ;
    data->mon->meal_ended = val;
    pthread_mutex_unlock(data->meal_mutex);
}

void    book_fork()
{
    
}

void    *monitor(void *data_pointer)
{
    t_data *data;
    int i;
    int j;
    int *arr;
    int started_meal;
    
    data = (t_data *)data_pointer;
    arr = init_arr(data);
    while (data->mon->done_num < data->c->p_num) {
        if (data->mon->meal_ended) {
            
            quicksort(arr, data->c->p_num / 2, data->phi);
            set_meal_ended(data, 0);
        }
        j = -1;
        started_meal = 0;
        while (++j < data->c->p_num) {
            i = arr[j];
            //printf("%d %d\n", data->mon->can_take_fork[1],data->mon->can_take_fork[2]);
            if (data->phi[i].status == THINK) {
                if (data->mon->can_take_fork[data->phi[i].left_fork] == 0 &&
                    data->mon->can_take_fork[data->phi[i].right_fork] == 0) {
                        give_forks(data->phi[i].left_fork,\
                         data->phi[i].right_fork, i, data->mon);
                        data->phi[i].status = EAT;
                        started_meal++;
                }
            }
        }
        
    }
        //quicksort(arr, data->c->p_num, data->phi);
    return (0);
}