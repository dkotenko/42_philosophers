/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create2dchararr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 22:02:50 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_fork_id(int id, int forks_number, int is_left_fork)
{
	if (is_left_fork) {
		return id;
	} else {
		if (id == forks_number) {
			return (1);
		}
		return id + 1;
	}
}

int		take_forks(t_data *data, int left_fork, int right_fork, int p_id)
{
	sem_wait(data->forks_sem[left_fork]->sem);
	print_action(data->print_sem->sem, p_id, TAKE_FORK, left_fork);
	sem_wait(data->forks_sem[right_fork]->sem);
	print_action(data->print_sem->sem, p_id, TAKE_FORK, right_fork);
	print_action(data->print_sem->sem, p_id, EAT, 0);
	data->phi[p_id].must_eat_times--;
	sem_post(data->meals_sem->sem);
	data->phi[p_id].status = SLEEP;
	return (1);
}

void	put_forks(int left_fork, int right_fork, t_data *data)
{
	sem_post(data->forks_sem[left_fork]->sem);
	sem_post(data->forks_sem[right_fork]->sem);
}