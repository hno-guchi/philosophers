/*
 * Create monitoring_thread
 */

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

/* スレッドに渡すデータ */
typedef struct	s_philo {
	int				index;
	int				right_fork_index;
	int				left_fork_index;
	int				count_eat;
	int				died;
	struct s_info	*info;
}	t_philo;

typedef struct	s_info {
	t_philo			philos[PHILOS];
	pthread_t		threads[PHILOS];
	pthread_t		monitor_thread;
	pthread_mutex_t	forks[PHILOS];
	pthread_mutex_t	count_eat_mutex;
	pthread_mutex_t	died_mutex;
	int				died;
}	t_info;

int	initialize_info(t_info *info)
{
	int	idx;

	idx = 0;
	info->died = 0;
	while (idx < PHILOS)
	{
		info->philos[idx].index = idx;
		info->philos[idx].right_fork_index = idx;
		info->philos[idx].left_fork_index = idx + 1;
		info->philos[idx].count_eat = 0;
		info->philos[idx].died = 0;
		info->philos[idx].info = info;
		if (pthread_mutex_init(&info->forks[idx], NULL))
		{
			// mutex_destroy(); * idx;
			return (1);
		}
		idx += 1;
	}
	info->philos[idx - 1].left_fork_index = 0;
	if (pthread_mutex_init(&info->count_eat_mutex, NULL))
	{
		// mutex_destroy(); * idx;
		return (1);
	}
	if (pthread_mutex_init(&info->died_mutex, NULL))
	{
		// mutex_destroy(); * idx;
		return (1);
	}
	return (0);
}

void	*do_func(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)data;
	info = philo->info;
	if ((philo->index % 2) != 0)
	{
		usleep(200);
	}
	while (1)
	{
		pthread_mutex_lock(&info->died_mutex);
		if (info->died == 1)
		{
			pthread_mutex_unlock(&info->died_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&info->died_mutex);
		pthread_mutex_lock(&info->count_eat_mutex);
		if (philo->count_eat == 3)
		{
			philo->died = 1;
			pthread_mutex_unlock(&info->count_eat_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&info->count_eat_mutex);
		pthread_mutex_lock(&info->forks[philo->right_fork_index]);
		pthread_mutex_lock(&info->died_mutex);
		if (info->died == 1)
		{
			pthread_mutex_unlock(&info->died_mutex);
			pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
			return (NULL);
		}
		pthread_mutex_unlock(&info->died_mutex);
		printf("%d	has taken a fork.\n", philo->index);
		pthread_mutex_lock(&info->forks[philo->left_fork_index]);
		pthread_mutex_lock(&info->died_mutex);
		if (info->died == 1)
		{
			pthread_mutex_unlock(&info->died_mutex);
			pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
			pthread_mutex_unlock(&info->forks[philo->left_fork_index]);
			return (NULL);
		}
		pthread_mutex_unlock(&info->died_mutex);
		printf("%d	has taken a fork.\n", philo->index);
		pthread_mutex_lock(&info->died_mutex);
		if (info->died == 1)
		{
			pthread_mutex_unlock(&info->died_mutex);
			pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
			pthread_mutex_unlock(&info->forks[philo->left_fork_index]);
			return (NULL);
		}
		pthread_mutex_unlock(&info->died_mutex);
		pthread_mutex_lock(&info->count_eat_mutex);
		philo->count_eat += 1;
		printf("%d	is eating[%d].\n", philo->index, philo->count_eat);
		pthread_mutex_unlock(&info->count_eat_mutex);
		usleep(200000);
		pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
		pthread_mutex_unlock(&info->forks[philo->left_fork_index]);
		usleep(200000);
		pthread_mutex_lock(&info->died_mutex);
		if (info->died == 1)
		{
			pthread_mutex_unlock(&info->died_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&info->died_mutex);
	}
	return (NULL);
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
		while (i < PHILOS)
		{
			pthread_mutex_lock(&info->count_eat_mutex);
			if (philos[i].died == 1)
			{
				pthread_mutex_unlock(&info->count_eat_mutex);
				pthread_mutex_lock(&info->died_mutex);
				printf(RED"%d is died.\n"END, philos[i].index);
				info->died = 1;
				pthread_mutex_unlock(&info->died_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&info->count_eat_mutex);
			i += 1;
		}
		i = 0;
		usleep(50);
	}
	return (NULL);
}

/* スレッドの開始 */
int	create_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < PHILOS)
	{
		if (pthread_create(&info->threads[i], NULL, do_func, (void *)&info->philos[i]))
		{
			// pthread_join(); * i;
			return (1);
		}
		i += 1;
	}
	return (0);
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
	if (create_philosophers(&info))
	{
		return (0);
	}
	if (pthread_create(&info.monitor_thread, NULL, monitoring, (void *)&info))
	{
		// pthread_join(); * i;
		return (0);
	}
	// finish_philo;
	for (i = 0; i < PHILOS; i++)
	{
		pthread_join(info.threads[i], NULL);
	}
	for (i = 0; i < PHILOS; i++)
	{
		pthread_mutex_destroy(&info.forks[i]);
	}
	pthread_join(info.monitor_thread, NULL);
	pthread_mutex_destroy(&info.count_eat_mutex);
	pthread_mutex_destroy(&info.died_mutex);
	return (0);
}
