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

typedef struct s_times {
	long long	start;
	int			num_philos;
	int			limit_die;
	int			eat;
	int			sleep;
	int			count_eat;
}	t_time;

typedef struct	s_philo {
	int				index;
	pthread_t		thread_id;
	int				count_eat;
	long long		time_last_eat;
	struct s_info	*info;
}	t_philo;

typedef struct	s_info {
	t_time			times;
	t_philo			philo[300];
	pthread_mutex_t	forks[300];
	pthread_mutex_t	count_eat;
}	t_info;

long long	get_time_ms()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		return (0);
	}
	return ((long long)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

int	set_times(t_time *times, int argc, char **argv)
{

	if ((times->start = get_time_ms()) == 0)
	{
		return (1);
	}
	times->num_philos = atoi(argv[1]);
	times->limit_die = atoi(argv[2]);
	times->eat = atoi(argv[3]);
	times->sleep = atoi(argv[4]);
	if (argc == 6)
	{
		times->count_eat = atoi(argv[5]);
	}
	else
	{
		times->count_eat = FOOD;
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
	if (pthread_mutex_init(&info->count_eat, NULL))
	{
		return (1);
	}
	while (idx < info->times.num_philos)
	{
		info->philo[idx].index = idx;
		info->philo[idx].info = info;
		info->philo[idx].count_eat = 0;
		info->philo[idx].time_last_eat = 0;
		if (pthread_mutex_init(&info->forks[idx], NULL))
		{
			return (1);
		}
		idx += 1;
	}
	return (0);
}

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

void	finely_usleep(int limit, long long base)
{
	long long	time_ms;

	time_ms = 0;
	while ((time_ms = get_time_ms()) != 0)
	{
		if (limit <= (time_ms - base))
		{
			break ;
		}
		usleep(50);
	}
	return ;
}

void	*philosopher(void *data)
{
	int				f;
	struct timeval	time;
	t_philo			*philo;
	int				right_fork;
	int				left_fork;
	long long		pass_time;

	f = 0;
	philo = (t_philo *)data;
	right_fork = philo->index;
	left_fork = philo->index + 1;
	if ((pass_time = get_time_ms()) == 0)
	{
		return (NULL);
	}
	if (left_fork == philo->info->times.num_philos)
	{
		left_fork = 0;
	}
	while ((f = food_on_table(philo)) != 0)
	{
		if ((philo->index % 2) != 0)
		{
			usleep(200);
		}
		pthread_mutex_lock(&philo->info->forks[right_fork]);
		pthread_mutex_lock(&philo->info->forks[left_fork]);
		if ((pass_time = get_time_ms()) == 0)
		{
			pthread_mutex_unlock(&philo->info->forks[right_fork]);
			pthread_mutex_unlock(&philo->info->forks[left_fork]);
			break ;
		}
		philo->time_last_eat = pass_time;
		printf("%lld	%d	has taken a fork.\n", (long long)(pass_time - philo->info->times.start), philo->index + 1);
		printf("%lld	%d	has taken a fork.\n", (long long)(pass_time - philo->info->times.start), philo->index + 1);
		printf(GREEN"%lld	%d	is eating.\n"END, (long long)(pass_time - philo->info->times.start), philo->index + 1);
		finely_usleep(philo->info->times.eat, pass_time);
		pthread_mutex_unlock(&philo->info->forks[right_fork]);
		pthread_mutex_unlock(&philo->info->forks[left_fork]);
		if ((pass_time = get_time_ms()) == 0)
		{
			return (NULL);
		}
		printf("%lld	%d	is sleeping.\n", (long long)(pass_time - philo->info->times.start), philo->index + 1);
		finely_usleep(philo->info->times.sleep, pass_time);
		if ((pass_time = get_time_ms()) == 0)
		{
			return (NULL);
		}
		printf("%lld	%d	is thinking.\n", (long long)(pass_time - philo->info->times.start), philo->index + 1);

	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	info;

	if (argc != 5 && argc != 6)
	{
		return (0);
	}
	i = 0;
	if (initialize_info(&info, argc, argv))
	{
		return (0);
	}
	for (i = 0; i < info.times.num_philos; i++)
	{
		pthread_create(&info.philo[i].thread_id, NULL, philosopher, (void *)&info.philo[i]);
	}
	for (i = 0; i < info.times.num_philos; i++)
	{
		pthread_join(info.philo[i].thread_id, NULL);
	}
	return (0);
}
