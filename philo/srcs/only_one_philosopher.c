/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_one_philosopher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 12:26:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one_philosopher(void *data)
{
	t_philo		*philo;
	t_info		*info;
	long long	time_ms;

	philo = (t_philo *)data;
	info = philo->info;
	time_ms = get_time_ms();
	pthread_mutex_lock(&info->forks[philo->right_fork_index]);
	printf("%lld	%d	has taken a fork\n", time_ms - info->time_start,
		philo->index);
	pthread_mutex_unlock(&info->died_mutex);
	finely_usleep(info->rules.time_die, time_ms);
	time_ms = get_time_ms();
	printf(RED"%lld	%d	is died\n"END,
		(time_ms - info->time_start), philo->index);
	return (NULL);
}
