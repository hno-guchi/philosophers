/*
 * Create died_time.
 */
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
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
	long long		time_last_meal;
	int				count_eat;
	int				died;
	struct s_info	*info;
}	t_philo;

typedef struct	s_info {
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_minimum_times;
	int				died;
	t_philo			philos[PHILOS];
	pthread_t		threads[PHILOS];
	pthread_t		monitor_thread;
	pthread_mutex_t	forks[PHILOS];
	pthread_mutex_t	count_eat_mutex;
	pthread_mutex_t	died_mutex;
}	t_info;

int	initialize_info(t_info *info)
{
	int	idx;

	idx = 0;
	info->num_philo = 5;
	info->time_die = 600;
	info->time_eat = 200;
	info->time_sleep = 200;
	info->died = 0;
	// info->eat_minimum_times = -1;
	info->eat_minimum_times = 3;
	while (idx < PHILOS)
	{
		info->philos[idx].index = idx;
		info->philos[idx].right_fork_index = idx;
		info->philos[idx].left_fork_index = idx + 1;
		info->philos[idx].time_last_meal = 0;
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

long long	get_time_ms()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		return (0);
	}
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	is_died(t_info *info)
{
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == 1)
	{
		pthread_mutex_unlock(&info->died_mutex);
		return (true);
	}
	pthread_mutex_unlock(&info->died_mutex);
	return (false);
}

bool	is_eaten_at_least_n_times(t_info *info, t_philo *philo)
{
	if (info->eat_minimum_times == -1)
	{
		return (false);
	}
	pthread_mutex_lock(&info->count_eat_mutex);
	if (philo->count_eat == info->eat_minimum_times)
	{
		philo->died = 1;
		pthread_mutex_unlock(&info->count_eat_mutex);
		return (true);
	}
	pthread_mutex_unlock(&info->count_eat_mutex);
	return (false);
}

void	try_has_taken_a_fork(t_info *info, int index)
{
	long long		time_ms;

	time_ms = 0;
	pthread_mutex_lock(&info->forks[index]);
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == 1)
	{
		pthread_mutex_unlock(&info->died_mutex);
		pthread_mutex_unlock(&info->forks[index]);
	}
	else
	{
		time_ms = get_time_ms();
		printf("%lld	%d	has taken a fork.\n", time_ms, index);
		pthread_mutex_unlock(&info->died_mutex);
	}
	return ;
}

void	try_eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == 1)
	{
		pthread_mutex_unlock(&info->died_mutex);
		pthread_mutex_unlock(&info->count_eat_mutex);
		pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
		pthread_mutex_unlock(&info->forks[philo->left_fork_index]);
	}
	else
	{
		pthread_mutex_lock(&info->count_eat_mutex);
		philo->count_eat += 1;
		philo->time_last_meal = get_time_ms();
		printf("%lld	%d	is eating[%d].\n", philo->time_last_meal, philo->index, philo->count_eat);
		pthread_mutex_unlock(&info->count_eat_mutex);
		pthread_mutex_unlock(&info->died_mutex);
		usleep(200000);
		pthread_mutex_unlock(&info->forks[philo->right_fork_index]);
		pthread_mutex_unlock(&info->forks[philo->left_fork_index]);
	}
	return ;
}

void	try_sleeping(t_info *info, int index)
{
	long long	time_ms;

	time_ms = 0;
	pthread_mutex_lock(&info->died_mutex);
	if (info->died == 1)
	{
		pthread_mutex_unlock(&info->died_mutex);
	}
	else
	{
		time_ms = get_time_ms();
		printf("%lld	%d	is sleeping.\n", time_ms, index);
		pthread_mutex_unlock(&info->died_mutex);
		usleep(200000);
	}
	return ;
}

void	*philosopher(void *data)
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
		try_has_taken_a_fork(info, philo->right_fork_index);
		try_has_taken_a_fork(info, philo->left_fork_index);
		try_eat(info, philo);
		try_sleeping(info, philo->index);
		if (is_eaten_at_least_n_times(info, philo))
		{
			return (NULL);
		}
		if (is_died(info))
		{
			return (NULL);
		}
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
		pthread_mutex_lock(&info->count_eat_mutex);
		while (i < PHILOS && philos[i].died == 1)
		{
			i += 1;
		}
		pthread_mutex_unlock(&info->count_eat_mutex);
		if (i == PHILOS)
		{
			pthread_mutex_lock(&info->died_mutex);
			printf(RED"Finish.\n"END);
			info->died = 1;
			pthread_mutex_unlock(&info->died_mutex);
			return (NULL);
		}
		i = 0;
		usleep(100);
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
		if (pthread_create(&info->threads[i], NULL, philosopher, (void *)&info->philos[i]))
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
