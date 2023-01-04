/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 12:26:53 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_pattern_one_philosopher(t_info *info)
{
	if (pthread_create(&info->threads[0], NULL, only_one_philosopher,
			(void *)&info->philos[0]) != SUCCESS)
	{
		return (ERROR);
	}
	return (SUCCESS);
}

static int	create_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->rules.num_philo)
	{
		if (pthread_create(&info->threads[i], NULL, philosopher,
				(void *)&info->philos[i]) != SUCCESS)
		{
			join_n_threads(info, i);
			return (ERROR);
		}
		i += 1;
	}
	return (SUCCESS);
}

int	create_threads(t_info *info)
{
	if (info->rules.num_philo == 1)
	{
		if (create_pattern_one_philosopher(info) == ERROR)
		{
			destroy_all_mutex(info);
			return (ERROR);
		}
	}
	else
	{
		if (create_philosophers(info) == ERROR)
		{
			return (ERROR);
		}
		if (pthread_create(&info->death_monitor, NULL, monitoring_death,
				(void *)info) != SUCCESS)
		{
			join_n_threads(info, info->rules.num_philo);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
