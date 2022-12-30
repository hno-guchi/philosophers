/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/30 20:31:29 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finely_usleep(int limit, long long base)
{
	long long	time_ms;

	time_ms = 0;
	while ((time_ms = get_time_ms()) != 0)
	{
		if (limit <= (time_ms - base))
		{
			return ;
		}
		usleep(50);
	}
	return ;
}

void	*monitoring(void *data)
{
	int			i;
	t_info		*info;
	t_philo		*philos;

	i = 0;
	info = (t_info *)data;
	philos = info->philos; 
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&info->died_mutex);
		if (info->died == DEAD)
		{
			pthread_mutex_unlock(&info->died_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&info->died_mutex);
		if (info->eat_minimum_times == -1)
		{
			continue ;
		}
		pthread_mutex_lock(&info->count_eat_mutex);
		while (i < info->num_philo)
		{
			if (philos[i].died == DEAD)
			{
				i += 1;
			}
			else
			{
				break ;
			}
		}
		pthread_mutex_unlock(&info->count_eat_mutex);
		if (i == info->num_philo)
		{
			pthread_mutex_lock(&info->died_mutex);
			info->died = DEAD;
			// printf(RED"Finish.\n"END);
			pthread_mutex_unlock(&info->died_mutex);
			return (NULL);
		}
		i = 0;
	}
	return (NULL);
}

void	join_n_threads

/* スレッドの開始 */
int	create_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_create(info->threads[i], NULL, philosopher, (void *)&info->philos[i]) != SUCCESS)
		{
			// pthread_join(); * i;
			join_n_threads(info, i);
			return (ERROR);
		}
		i += 1;
	}
	return (SUCCESS);
}

int	create_threads(t_info *info)
{
	if (create_philosophers(info) == ERROR)
	{
		return (ERROR);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	info;

	i = 0;
	if (is_validation_args(argc, argv))
	{
		return (0);
	}
	if (set_info(&info, argc, argv) == ERROR)
	{
		return (0);
	}
	if (create_threads(&info) == ERROR)
	{
		destroy_n_forks_mutex(&info, info.rules.num_philo);
		pthread_mutex_destroy(&info.count_eat_mutex);
		pthread_mutex_destroy(&info.died_mutex);
		return (0);
	}
	// if (create_philosophers(&info))
	// {
	// 	return (0);
	// }
	// if (pthread_create(&info.monitor_thread, NULL, monitoring, (void *)&info))
	// {
		// pthread_join(); * i;
	// 	return (0);
	// }
	// end_philosophers;
	for (i = 0; i < info.num_philo; i++)
	{
		pthread_join(info.threads[i], NULL);
	}
	for (i = 0; i < info.num_philo; i++)
	{
		pthread_mutex_destroy(&info.forks[i]);
	}
	pthread_join(info.monitor_thread, NULL);
	pthread_mutex_destroy(&info.count_eat_mutex);
	pthread_mutex_destroy(&info.died_mutex);
	return (0);
}

// printf("[OK]"); printf(" : initialize_time();\n");
