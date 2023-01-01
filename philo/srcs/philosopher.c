/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/01 20:23:19 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_info_died(t_info *info)
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

static bool	is_finish(t_info *info, t_philo *philo)
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

static void	try_has_taken_a_fork(t_info *info, t_philo *philo, int fork_index)
{
	long long		time_ms;

	time_ms = 0;
	pthread_mutex_lock(&info->forks[fork_index]);
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == DEAD)
	{
		pthread_mutex_unlock(&info->died_mutex);
		pthread_mutex_unlock(&info->forks[fork_index]);
	}
	else
	{
		time_ms = get_time_ms();
		printf("%lld	%d	has taken a fork\n", time_ms - info->time_start, philo->index);
		pthread_mutex_unlock(&info->died_mutex);
	}
	return ;
}

static void	try_eat(t_info *info, t_philo *philo)
{
	long long	time_ms;

	time_ms = 0;
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == DEAD)
	{
		pthread_mutex_unlock(&info->died_mutex);
		pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
		pthread_mutex_unlock(&info->forks[philo->left_fork_index]);
	}
	else
	{
		pthread_mutex_lock(&info->count_eat_mutex);
		time_ms = get_time_ms();
		philo->count_eat += 1;
		philo->time_last_meal = time_ms;
		printf(GREEN"%lld	%d	is eating\n"END, time_ms - info->time_start, philo->index);
		pthread_mutex_unlock(&info->count_eat_mutex);
		pthread_mutex_unlock(&info->died_mutex);
		finely_usleep(info->rules.time_eat, philo->time_last_meal);
		pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
		pthread_mutex_unlock(&info->forks[philo->left_fork_index]);
	}
	return ;
}

static void	try_sleeping(t_info *info, int index)
{
	long long	time_ms;

	time_ms = 0;
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == DEAD)
	{
		pthread_mutex_unlock(&info->died_mutex);
	}
	else
	{
		time_ms = get_time_ms();
		printf("%lld	%d	is sleeping\n", time_ms - info->time_start, index);
		pthread_mutex_unlock(&info->died_mutex);
		finely_usleep(info->rules.time_sleep, time_ms);
	}
	return ;
}

static void	try_thinking(t_info *info, int index)
{
	long long	time_ms;

	time_ms = 0;
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == DEAD)
	{
		pthread_mutex_unlock(&info->died_mutex);
	}
	else
	{
		time_ms = get_time_ms();
		printf("%lld	%d	is thinking\n", (time_ms - info->time_start), index);
		pthread_mutex_unlock(&info->died_mutex);
	}
	return ;
}

static void	try_usleep_200(int index)
{
	if ((index % 2) != 0)
	{
		usleep(200);
	}
}

void	*philosopher(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)data;
	info = philo->info;
	try_usleep_200(philo->index);
	while (1)
	{
		try_has_taken_a_fork(info, philo, philo->right_fork_index);
		try_has_taken_a_fork(info, philo, philo->left_fork_index);
		try_eat(info, philo);
		try_sleeping(info, philo->index);
		try_thinking(info, philo->index);
		if (is_finish(info, philo))
		{
			break ;
		}
	}
	return (NULL);
}

// printf(GREEN"%lld	%d	is eating[%d].\n"END, time_ms - info->time_start, philo->index, philo->count_eat);
// printf(GREEN"%lld %d is eating\n"END, time_ms, philo->index);
// printf(GREEN"%lld	%d	is eating[%d].\n"END, time_ms - info->time_start, philo->index, philo->count_eat);
// printf("%lld %d has taken a fork\n", time_ms, philo->index);
// printf("%lld %d is sleeping\n", time_ms, index);
// printf("%lld	%d	is thinking\n", time_ms, index);
