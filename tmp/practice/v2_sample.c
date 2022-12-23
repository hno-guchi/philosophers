#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

# define DELAY 5000
# define FOOD 50

int				sleep_seconds = 0;	// 眠る時間（argv[4]）

struct	s_info;

typedef struct	s_time {
	int	num_philo;
	int	time_sleep;
}	t_time;

typedef struct	s_philo {
	int				index;
	pthread_t		thread_id;
	struct s_info	*info;
}	t_philo;

typedef struct	s_info {
	t_time			times;
	t_philo			philo[300];		// thread == philo
	pthread_mutex_t	forks[300];		// mutex object
	pthread_mutex_t	count_eat;		// 食事回数を数える用
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

/*
void	grab_fork(int philo, int c)
{
	pthread_mutex_lock(&forks[c]);
	printf("[%d] has taken a fork.\n", philo);
}

void	down_forks(int right, int left)
{
	pthread_mutex_unlock(&forks[right]);
	pthread_mutex_unlock(&forks[left]);
}
*/

void	*philosopher(void *data)
{
	int	i;
	int	f;
	t_philo	*philo;
	int	right_fork;
	int	left_fork;

	i = 0;
	f = 0;
	philo = (t_philo *)data;
	right_fork = philo->index;
	left_fork = philo->index + 1;
	printf("[%d] is thinking.\n", philo->index);
	// 箸が一巡した
	if (left_fork == philo->info->times.num_philo)
	{
		left_fork = 0;
	}
	while ((f = food_on_table(philo)))
	{
		// 箸を取る前にphilo[0]をsleepさせることで、デッドロックを回避
		// if ((philo->index % 2) != 0)
		if (philo->index == 1)
		{
			sleep(sleep_seconds);
		}
		// grab_fork(philo->index, right_fork);
		// grab_fork(philo->index, left_fork);
		pthread_mutex_lock(&philo->info->forks[right_fork]);
		pthread_mutex_lock(&philo->info->forks[left_fork]);
		printf("[%d] has taken a fork.\n", philo->index);
		printf("[%d] has taken a fork.\n", philo->index);
		printf("[%d] is eating.\n", philo->index);
		usleep(DELAY * (FOOD - f + 1));
		pthread_mutex_unlock(&philo->info->forks[right_fork]);
		pthread_mutex_unlock(&philo->info->forks[left_fork]);
		// down_forks(left_fork, right_fork);
	}
	printf("[%d] is sleeping.\n", philo->index);
	return (NULL);
}

void	set_times(t_time *times, char **argv)
{
		times->num_philo = atoi(argv[1]);
		times->time_sleep = atoi(argv[2]);
}

void	initialize_info(t_info *info, int argc, char **argv)
{
	int	idx;

	(void)argc;
	idx = 0;
	set_times(&info->times, argv);
	pthread_mutex_init(&info->count_eat, NULL);
	while (idx < info->times.num_philo)
	{
		info->philo[idx].index = idx;
		info->philo[idx].info = info;
		pthread_mutex_init(&info->forks[idx], NULL);
		idx += 1;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_info			info;

	if (argc != 3)
	{
		return (0);
	}
	i = 0;
	initialize_info(&info, argc, argv);
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
