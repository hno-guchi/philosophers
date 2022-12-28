#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#define PHILOS 5

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define END "\x1b[39m"

struct	s_info;

typedef struct	s_philo {
	int				index;
	int				count_eat;
	int				died;
	struct s_info	*info;
	pthread_t		thread_id;
}	t_philo;

typedef struct	s_info {
	int				died;
	t_philo			philo[PHILOS];
	pthread_mutex_t	forks[PHILOS];
	pthread_mutex_t	count_eat;
}	t_info;

int	initialize_info(t_info *info)
{
	int	idx;

	idx = 0;
	info->died = 0;
	while (idx < PHILOS)
	{
		info->philo[idx].index = idx;
		info->philo[idx].count_eat = 0;
		info->philo[idx].died = 0;
		info->philo[idx].info = info;
		if (pthread_mutex_init(&info->forks[idx], NULL))
		{
			return (1);
		}
		idx += 1;
	}
	if (pthread_mutex_init(&info->count_eat, NULL))
	{
		return (1);
	}
	return (0);
}

void	*do_func(void *data)
{
	t_philo	*philo;
	t_info	*info;
	int		right_fork;
	int		left_fork;

	philo = (t_philo *)data;
	info = philo->info;
	right_fork = philo->index;
	left_fork = philo->index + 1;
	if (left_fork == PHILOS)
	{
		left_fork = 0;
	}
	if ((philo->index % 2) != 0)
	{
		usleep(200);
	}
	while (philo->died == 0)
	{
		pthread_mutex_lock(&info->forks[right_fork]);
		printf("%d	has taken a fork.\n", philo->index);
		pthread_mutex_lock(&info->forks[left_fork]);
		printf("%d	has taken a fork.\n", philo->index);
		pthread_mutex_lock(&info->count_eat);
		printf("%d	is eating.\n", philo->index);
		philo->count_eat += 1;
		usleep(200);
		pthread_mutex_unlock(&info->count_eat);
		pthread_mutex_unlock(&info->forks[right_fork]);
		pthread_mutex_unlock(&info->forks[left_fork]);
		if (philo->count_eat == 3)
		{
			philo->died = 1;
		}
	}
	return (NULL);
}

void	monitoring_threads(t_info *info, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->died == 0)
	{
		while (i < PHILOS && info->died == 0)
		{
			pthread_mutex_lock(&info->count_eat);
			if (philo[i].count_eat == 3)
			{
				printf(RED"%d is died.\n"END, philo[i].index);
				info->died = 1;
						}
			pthread_mutex_unlock(&info->count_eat);
			pthread_mutex_destroy(&info->count_eat);
			i += 1;
		}
		if (info->died == 1)
		{
			break ;
		}
		i = 0;
	}
}

int	main(void)
{
	int		i;
	t_info	info;

	i = 0;
	if (initialize_info(&info))
	{
		return (0);
	}
	for (i = 0; i < PHILOS; i++)
	{
		pthread_create(&info.philo[i].thread_id, NULL, do_func, (void *)&info.philo[i]);
	}
	monitoring_threads(&info, info.philo);
	for (i = 0; i < PHILOS; i++)
	{
		pthread_join(info.philo[i].thread_id, NULL);
	}
	for (i = 0; i < PHILOS; i++)
	{
		pthread_mutex_destroy(&info.forks[i]);
	}
	return (0);
}
