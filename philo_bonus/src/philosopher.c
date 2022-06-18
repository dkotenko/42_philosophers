#include "philosophers.h"
#include <limits.h>

int	is_dead(t_data *data, t_phi *me)
{
	return (me->last_meal + data->c->time_to_die <= get_current_time_us() \
		|| me->status == DEAD);
}

int	had_a_meal(t_data *data, t_phi *me)
{
	long long	diff;

	sem_wait(data->forks_common->sem);
	print_action(data->print_sem->sem, me->id, TAKE_FORK);
	if (data->c->p_num < 2)
		return (data->phi[me->id].status = DEAD);
	sem_wait(data->forks_common->sem);
	print_action(data->print_sem->sem, me->id, TAKE_FORK);
	print_action(data->print_sem->sem, me->id, EAT);
	diff = get_current_time_us() - me->last_meal - data->c->time_to_die;
	me->last_meal = get_current_time_us();
	if (diff >= 0)
	{
		usleep(diff);
		me->status = DEAD;
	}
	else
	{	
		data->phi[me->id].must_eat_times--;
		data->phi[me->id].status = SLEEP;
		usleep(data->c->time_to_eat - (get_current_time_us() - me->last_meal));
	}
	sem_post(data->forks_common->sem);
	sem_post(data->forks_common->sem);
	return (1);
}

int	had_a_nap(t_data *data, t_phi *me)
{
	long long	diff;

	print_action(data->print_sem->sem, me->id, SLEEP);
	diff = get_current_time_us() - me->last_meal - data->c->time_to_die;
	if (diff >= 0)
	{
		usleep(diff);
		me->status = DEAD;
		return (0);
	}
	else
	{
		usleep(data->c->time_to_sleep);
	}
	return (1);
}

void	set_final_status(t_data *data, t_phi *me)
{
	if (is_dead(data, me))
	{
		me->status = DEAD;
		print_action(data->print_sem->sem, me->id, DEAD);
	}
	else
	{
		me->status = DONE;
		print_action(data->print_sem->sem, me->id, DONE);
	}
	sem_post(data->done_sem->sem);
}

void	*philosopher(t_data *data)
{
	t_phi	*me;

	sem_wait(data->done_sem->sem);
	me = &data->phi[data->my_id];
	me->id = data->my_id;
	me->status = THINK;
	me->last_meal = get_current_time_us();
	while (me->must_eat_times && me->status != DEAD)
	{
		if (is_dead(data, me))
			break ;
		had_a_meal(data, me);
		if (is_dead(data, me))
			break ;
		had_a_nap(data, me);
		if (is_dead(data, me))
			break ;
		print_action(data->print_sem->sem, me->id, THINK);
		me->status = THINK;
	}
	set_final_status(data, me);
	return (0);
}
