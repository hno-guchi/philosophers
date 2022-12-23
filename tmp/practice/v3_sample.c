#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

# define DELAY 5000
# define FOOD 10

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define END "\x1b[39m"

struct	s_info;

typedef struct	s_time {
	long long	time_start;
	int			num_philo;
	int			time_sleep;
	int			least_eat;
}	t_time;

typedef struct	s_philo {
	int				index;
	pthread_t		thread_id;
	int				count_eat;
	struct s_info	*info;
}	t_philo;

typedef struct	s_info {
	t_time			times;
	t_philo			philo[300];
	pthread_mutex_t	forks[300];
	pthread_mutex_t	count_eat;
}	t_info;

// count_eating
int	food_on_table(t_philo *philo)
{
	static int	food = FOOD;
	int			myfood;

	pthread_mutex_lock(&philo->info->count_eat);
	if (0 < food)
	{
		food -= 1;
	}
	myfood = food;
	pthread_mutex_unlock(&philo->info->count_eat);
	return (myfood);
}

void	*philosopher(void *data)
{
	int	f;
	struct timeval	time;
	t_philo	*philo;
	int	right_fork;
	int	left_fork;
	long long	pass_time;

	f = 0;
	philo = (t_philo *)data;
	right_fork = philo->index;
	left_fork = philo->index + 1;
	pass_time = 0;
	if (gettimeofday(&time, NULL) == -1)
	{
		return (NULL);
	}
	pass_time = (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000)); 
	printf("%lld	%d	is thinking.\n", pass_time - philo->info->times.time_start, philo->index);
	// 箸が一巡した
	if (left_fork == philo->info->times.num_philo)
	{
		left_fork = 0;
	}
	while ((f = food_on_table(philo)))
	{
		// 箸を取る前にphilo[0]をsleepさせることで、デッドロックを回避
		if ((philo->index % 2) != 0)
		{
			usleep(2);
		}
		pthread_mutex_lock(&philo->info->forks[right_fork]);
		pthread_mutex_lock(&philo->info->forks[left_fork]);
		if (gettimeofday(&time, NULL) == -1)
		{
			pthread_mutex_unlock(&philo->info->forks[right_fork]);
			pthread_mutex_unlock(&philo->info->forks[left_fork]);
			break ;
		}
		pass_time = (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000)); 
		printf("%lld	%d	has taken a fork.\n", pass_time - philo->info->times.time_start, philo->index);
		printf("%lld	%d	has taken a fork.", pass_time - philo->info->times.time_start, philo->index);
		printf("\n");
		printf(GREEN"%lld	%d	is eating."END, pass_time - philo->info->times.time_start, philo->index);
		printf("\n");
		usleep(DELAY * (philo->info->times.least_eat - f + 1));
		pthread_mutex_unlock(&philo->info->forks[right_fork]);
		pthread_mutex_unlock(&philo->info->forks[left_fork]);
	}
	if (gettimeofday(&time, NULL) == -1)
	{
		return (NULL);
	}
	pass_time = (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000)); 
	printf("%lld	%d	is sleeping.\n", pass_time - philo->info->times.time_start, philo->index);
	return (NULL);
}

int	set_times(t_time *times, int argc, char **argv)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		return (1);
	}
	times->time_start = (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000));
	times->num_philo = atoi(argv[1]);
	times->time_sleep = atoi(argv[2]);
	if (argc == 4)
	{
		times->least_eat = atoi(argv[3]);
	}
	else
	{
		times->least_eat = FOOD;
	}
	return (0);
}

int	initialize_info(t_info *info, int argc, char **argv)
{
	int	idx;

	idx = 0;
	if (set_times(&info->times, argc, argv))
	{
		return (1);
	}
	if(pthread_mutex_init(&info->count_eat, NULL))
	{
		return (1);
	}
	while (idx < info->times.num_philo)
	{
		info->philo[idx].index = idx;
		info->philo[idx].info = info;
		info->philo[idx].count_eat = 0;
		if (pthread_mutex_init(&info->forks[idx], NULL))
		{
			return (1);
		}
		idx += 1;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				i;
	t_info			info;

	if (argc != 3 && argc != 4)
	{
		return (0);
	}
	i = 0;
	if (initialize_info(&info, argc, argv))
	{
		return (0);
	}
	for (i = 0; i < info.times.num_philo; i++)
	{
		pthread_create(&info.philo[i].thread_id, NULL, philosopher, (void *)&info.philo[i]);
	}
	for (i = 0; i < info.times.num_philo; i++)
	{
		pthread_join(info.philo[i].thread_id, NULL);
	}
	return (0);
}
