/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_death.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 12:28:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_over_eat_times(int limit, int count)
{
	if (limit == -1)
	{
		return (false);
	}
	if (count < limit)
	{
		return (false);
	}
	return (true);
}

static int	check_died(t_info *info, t_philo *philo)
{
	long long	current_time;

	current_time = 0;
	pthread_mutex_lock(&info->died_mutex);
	current_time = get_time_ms();
	if (info->rules.time_die
		<= (current_time - philo->time_last_meal))
	{
		info->died = DEAD;
		if (!is_over_eat_times(info->rules.eat_minimum_times,
				philo->count_eat))
		{
			printf(RED"%lld	%d	is died\n"END,
				(current_time - info->time_start), philo->index);
		}
		pthread_mutex_unlock(&info->died_mutex);
		return (DEAD);
	}
	pthread_mutex_unlock(&info->died_mutex);
	return (ALIVE);
}

void	*monitoring_death(void *data)
{
	int			i;
	int			flag_death;
	t_info		*info;
	t_philo		*philos;

	i = 0;
	flag_death = ALIVE;
	info = (t_info *)data;
	philos = info->philos;
	while (1)
	{
		while (i < info->rules.num_philo)
		{
			flag_death = check_died(info, &philos[i]);
			if (flag_death == DEAD)
			{
				return (NULL);
			}
			i += 1;
		}
		i = 0;
	}
	return (NULL);
}
// printf(RED"%lld %d is died.\n"END, current_time, i);
// printf(GREEN"[OK]"END); printf(" : function();\n");
// printf(RED"[Error]"END); printf(" : ();\n");
