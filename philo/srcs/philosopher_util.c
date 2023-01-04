/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 11:04:10 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_info_died(t_info *info)
{
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == DEAD)
	{
		pthread_mutex_unlock(&info->died_mutex);
		return (true);
	}
	pthread_mutex_unlock(&info->died_mutex);
	return (false);
}

bool	is_eaten_at_least_n_times(t_info *info, t_philo *philo)
{
	if (info->rules.eat_minimum_times == -1)
	{
		return (false);
	}
	if (info->rules.eat_minimum_times <= philo->count_eat)
	{
		return (true);
	}
	return (false);
}

bool	is_finish(t_info *info, t_philo *philo)
{
	if (is_info_died(info))
	{
		return (true);
	}
	if (is_eaten_at_least_n_times(info, philo))
	{
		return (true);
	}
	return (false);
}

void	finely_usleep(int limit, long long base)
{
	long long	time_ms;

	time_ms = get_time_ms();
	while (time_ms != 0)
	{
		if (limit <= (time_ms - base))
		{
			return ;
		}
		usleep(50);
		time_ms = get_time_ms();
	}
	return ;
}

void	try_usleep_200(int index)
{
	if ((index % 2) != 0)
	{
		usleep(200);
	}
}
