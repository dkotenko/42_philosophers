#include "philosophers.h"

/*

**
** one print mutex version
**

void	*printer(void *data_pointer)
{
	t_dlist 		temp;
	t_data			*data;
	t_dlist_node	*node;

	//printf("%lu\n", sizeof(void *));
	//printf("%lu\n", sizeof(t_data));
	//printf("%lu\n", sizeof(t_dlist_node));
	data = (t_data *)data_pointer;
	ft_memset(&temp, 0, sizeof(t_dlist));
	while (data->mon->done_num < data->c->p_num) {
		if (data->pq->size > 0) {
			pthread_mutex_lock(data->print_mutex);
			ft_memcpy(&temp, data->pq, sizeof(t_dlist));
			ft_memset(data->pq, 0, sizeof(t_dlist));
			pthread_mutex_unlock(data->print_mutex);
		}
		while (temp.size > 0) {
			
			node = temp.head;
			
			printf("%s", (char *)node->data);
			t_dlist_pop(&temp, node);
			free(node->data);
			free(node);
		}
	}
	return 0;
}
*/

void	*printer(void *data_pointer)
{
	t_dlist 		temp;
	t_data			*data;
	t_dlist_node	*node;
	int				i;

	//printf("%lu\n", sizeof(void *));
	//printf("%lu\n", sizeof(t_data));
	//printf("%lu\n", sizeof(t_dlist_node));
	data = (t_data *)data_pointer;
	ft_memset(&temp, 0, sizeof(t_dlist));
	
	while (data->mon->done_num < data->c->p_num) {
		i = 0;
		while (++i < data->c->p_num + 1) {
			if (data->phi[i].pq->size > 0) {
				
				pthread_mutex_lock(data->phi[i].print_mutex);
				ft_memcpy(&temp, data->phi[i].pq, sizeof(t_dlist));
				ft_memset(data->phi[i].pq, 0, sizeof(t_dlist));
				pthread_mutex_unlock(data->phi[i].print_mutex);
			}	
			while (temp.size > 0) {
				node = temp.head;
				printf("%s", (char *)node->data);
				t_dlist_pop(&temp, node);
				free(node->data);
				free(node);
			}
		}
		
	}
	return 0;
}