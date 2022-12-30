/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/30 20:31:06 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_rules(t_rules *rules, int argc, char **argv)
{
	rules->num_philo = ft_atoi(argv[1]);
	rules->time_die = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
	{
		rules->eat_minimum_times = -1;
	}
	else if (argc == 6)
	{
		rules->eat_minimum_times = ft_atoi(argv[5]);
	}
}

void	destroy_n_forks_mutex(t_info *info, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i += 1;
	}
}

int	set_philo(t_info *info, t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < info->num_philo)
	{
		philos[idx]->index = idx;
		philos[idx]->right_fork_index = idx;
		philos[idx]->left_fork_index = idx + 1;
		philos[idx]->time_last_meal = info->time_start;
		philos[idx]->count_eat = 0;
		philos[idx]->died = 0;
		// philos[idx]->full = false;
		philos[idx]->info = info;
		if (pthread_mutex_init(&info->forks[idx], NULL) != 0)
		{
			destroy_n_forks_mutex(info, idx);
			return (ERROR);
		}
		idx += 1;
	}
	philos[idx - 1]->left_fork_index = 0;
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
