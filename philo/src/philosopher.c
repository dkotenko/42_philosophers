#include "philosophers.h"
#include <limits.h>

int		is_dead(t_data *data, t_phi *me)
{
	return (me->last_meal + data->c->time_to_die <= get_current_time_ms() \
		|| me->status == DEAD);
}

int		had_a_meal(t_data *data, t_phi *me)
{
	long long diff;

	print_action(data->printf_mutex, me->id, EAT, 0);
	diff = get_current_time_ms() - me->last_meal - data->c->time_to_die;
	me->last_meal = get_current_time_ms();
	if (diff >= 0) {
		usleep_ms(diff);
		put_forks(me->left_fork, me->right_fork, data);
		me->status = DEAD;
		return (0);
	} else {
		usleep_ms(data->c->time_to_eat);
	}
	put_forks(me->left_fork, me->right_fork, data);
	me->must_eat_times--;
	return (1);
}

int		had_a_nap(t_data *data, t_phi *me)
{
	long long diff;

	print_action(data->printf_mutex, me->id, SLEEP, 0);
	diff = get_current_time_ms() - me->last_meal - data->c->time_to_die;
	if (diff >= 0) {
		usleep_ms(diff);
		return (0);
	} else {
		usleep_ms(data->c->time_to_sleep);
	}
	return (1);
}

void	set_final_status(t_data *data, t_phi *me)
{
	if (is_dead(data, me)) {
		exit(0);
		me->status = DEAD;
		print_action(data->printf_mutex, me->id, DEAD, 0);
		pthread_mutex_lock(data->dead_mutex);
		data->mon->dead_num++;
		pthread_mutex_unlock(data->dead_mutex);	
	} else {
		me->status = DONE;
		print_action(data->printf_mutex, me->id, DONE, 0);
	}
	me->last_meal = LLONG_MAX;
	pthread_mutex_lock(data->done_mutex);
	data->mon->done_num++;
	pthread_mutex_unlock(data->done_mutex);
}

void	*philosopher(void *data_pointer)
{
	t_data	*data;
	t_phi	*me;

	data = (t_data *)data_pointer;
	me = &data->phi[data->my_id];
	me->id = data->my_id;
	me->status = THINK;
	while (me->must_eat_times && me->status != DEAD)
	{
		if (is_dead(data, me)) {
			break;
		}
		while (!take_forks(data, me->left_fork, me->right_fork, me->id))
			;
		/*
		if (!is_forks_taken(data, me->left_fork, me->right_fork, me->id)) {
			continue;
		}
		*/
		if (!had_a_meal(data, me))
			break;
		if (!had_a_nap(data, me)) {
			break;
		}
		print_action(data->printf_mutex, me->id, THINK, 0);
		me->status = THINK;
	}
	set_final_status(data, me);
	return (0);
}
