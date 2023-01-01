/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/01 18:37:40 by hnoguchi         ###   ########.fr       */
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

/*
void	*monitoring_count_eat(void *data)
{
	int		i;
	t_info	*info;
	t_philo	*philos;

	i = 0;
	info = (t_info *)data;
	philos = info->philos;
	while (1)
	{
		while (i < info->rules.num_philo)
		{
			pthread_mutex_

			i += 1;
		}
		i = 0;

	}
}
*/

void	*monitoring_death(void *data)
{
	int			i;
	long long	current_time;
	t_info		*info;
	t_philo		*philos;

	i = 0;
	current_time = 0;
	info = (t_info *)data;
	philos = info->philos; 
	while (1)
	{
		// usleep(100);
		while (i < info->rules.num_philo)
		{
			pthread_mutex_lock(&info->died_mutex);
			current_time = get_time_ms();
			if (info->rules.time_die <= (current_time - philos[i].time_last_meal))
			{
				info->died = DEAD;
				printf(RED"%lld	%d	is died.\n"END, (current_time - info->time_start), i);
				pthread_mutex_unlock(&info->died_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&info->died_mutex);
			i += 1;
		}
		i = 0;
	}
	return (NULL);
}

/*
void	*monitoring_death(void *data)
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
		if (info->rules.eat_minimum_times == -1)
		{
			continue ;
		}
		pthread_mutex_lock(&info->count_eat_mutex);
		while (i < info->rules.num_philo)
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
		if (i == info->rules.num_philo)
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
*/

void	join_n_threads(t_info *info, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(info->threads[i], NULL);
		i += 1;
	}
}

void	destroy_all_mutex(t_info *info)
{
	destroy_n_forks_mutex(info, info->rules.num_philo);
	pthread_mutex_destroy(&info->count_eat_mutex);
	pthread_mutex_destroy(&info->died_mutex);
}

void	end_philosophers(t_info *info)
{
	join_n_threads(info, info->rules.num_philo);
	pthread_join(info->death_monitor, NULL);
	destroy_all_mutex(info);
}

/* スレッドの開始 */
int	create_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->rules.num_philo)
	{
		if (pthread_create(&info->threads[i], NULL, philosopher, (void *)&info->philos[i]) != SUCCESS)
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
	if (create_philosophers(info) == ERROR)
	{
		return (ERROR);
	}
	if (pthread_create(&info->death_monitor, NULL, monitoring_death, (void *)info) != SUCCESS)
	{
		join_n_threads(info, info->rules.num_philo);
		return (ERROR);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!is_validation_args(argc, argv))
	{
		printf(RED"[Error]"END); printf(" : is_validation_args();\n");
		return (0);
	}
	if (set_info(&info, argc, argv) == ERROR)
	{
		printf(RED"[Error]"END); printf(" : set_info();\n");
		return (0);
	}
	if (create_threads(&info) == ERROR)
	{
		printf(RED"[Error]"END); printf(" : create_threads();\n");
		destroy_all_mutex(&info);
		return (0);
	}
	end_philosophers(&info);
	// printf(GREEN"[OK]"END); printf(" : end_philosophers();\n");
	return (0);
}

// printf(GREEN"[OK]"END); printf(" : function();\n");
// printf(RED"[Error]"END); printf(" : ();\n");
