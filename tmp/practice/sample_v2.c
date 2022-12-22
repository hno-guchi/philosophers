#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

# define PHILOS 5
# define DELAY 5000
# define FOOD 10

int				sleep_seconds = 0;	// 眠る時間（argv[4]）
// pthread_t		philo[PHILOS];		// スレッドの数（argv[1]）
pthread_mutex_t	forks[PHILOS];		// 上記同様（ただし共有資源）
pthread_mutex_t	count_eat;			// 食事回数を数える用

typedef struct	s_time {
	int	num_philo;
	int	time_sleep;
}	t_time;

// count_eating
int	food_on_table(void)
{
	static int	food = FOOD;
	int			myfood;

	pthread_mutex_lock(&count_eat);
	if (0 < food)
	{
		food -= 1;
	}
	myfood = food;
	pthread_mutex_unlock(&count_eat);
	return (myfood);
}

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

void	*philosopher(void *num)
{
	int	i;
	int	f;
	int	id;
	int	right_fork;
	int	left_fork;

	i = 0;
	f = 0;
	id = (int)num;
	right_fork = id;
	left_fork = id + 1;
	printf("[%d] is thinking.\n", id);
	// 箸が一巡した
	if (left_fork == PHILOS)
	{
		left_fork = 0;
	}
	while ((f = food_on_table()))
	{
		// 箸を取る前にphilo[0]をsleepさせることで、デッドロックを回避
		if (id == 1)
		{
			sleep(sleep_seconds);
		}
		grab_fork(id, right_fork);
		grab_fork(id, left_fork);
		printf("[%d] is eating.\n", id);
		usleep(DELAY * (FOOD - f + 1));
		down_forks(left_fork, right_fork);
	}
	printf("[%d] is sleeping.\n", id);
	return (NULL);
}

void	set_times(t_time *times, char **argv)
{
		times->num_philo = atoi(argv[1]);
		times->time_sleep = atoi(argv[2]);
}

int	main(int argc, char **argv)
{
	int				i;
	t_time			times;
	pthread_t		*philo;

	i = 0;
	if (argc != 3)
	{
		return (0);
	}
	set_times(&times, argv);
	philo = (pthread_t *)malloc(sizeof(pthread_t) * times.num_philo);
	if (philo == NULL)
	{
		return (0);
	}
	pthread_mutex_init(&count_eat, NULL);
	for (i = 0; i < times.num_philo; i++)
	{
		pthread_create(&philo[i], NULL, philosopher, (void *)i);
	}
	for (i = 0; i < times.num_philo; i++)
	{
		pthread_join(philo[i], NULL);
	}
	free(philo);
	return (0);
}
