/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 12:30:45 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_philo(t_info *info, t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < info->rules.num_philo)
	{
		philos[idx].index = idx;
		philos[idx].right_fork_index = idx;
		philos[idx].left_fork_index = idx + 1;
		philos[idx].time_last_meal = info->time_start;
		philos[idx].count_eat = 0;
		philos[idx].info = info;
		if (pthread_mutex_init(&info->forks[idx], NULL) != 0)
		{
			destroy_n_forks_mutex(info, idx);
			return (ERROR);
		}
		idx += 1;
	}
	philos[idx - 1].left_fork_index = 0;
	return (SUCCESS);
}

int	set_info(t_info *info, int argc, char **argv)
{
	set_rules(&info->rules, argc, argv);
	info->died = 0;
	info->time_start = get_time_ms();
	if (set_philo(info, info->philos) == ERROR)
	{
		return (ERROR);
	}
	if (pthread_mutex_init(&info->count_eat_mutex, NULL) != SUCCESS)
	{
		destroy_n_forks_mutex(info, info->rules.num_philo);
		return (ERROR);
	}
	if (pthread_mutex_init(&info->died_mutex, NULL) != SUCCESS)
	{
		destroy_n_forks_mutex(info, info->rules.num_philo);
		pthread_mutex_destroy(&info->count_eat_mutex);
		return (ERROR);
	}
	return (SUCCESS);
}
