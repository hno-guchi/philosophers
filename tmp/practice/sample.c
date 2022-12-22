// https://docs.oracle.com/cd/E19205-01/820-1219/gepji/index.html

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

# define PHILOS 5
# define DELAY 5000
# define FOOD 10

void	*philosopher(void *id);
void	grab_chopstick(int, int, char *);
void	down_chopsticks(int, int);
int		food_on_table(void);

pthread_mutex_t	chopstick[PHILOS];
pthread_t		philo[PHILOS];
pthread_mutex_t	food_lock;
int				sleep_seconds = 0;

int	main(int args, char **argv)
{
	int	i;

	if (args == 2)
	{
		sleep_seconds = atoi(argv[1]);
	}
	pthread_mutex_init(&food_lock, NULL);
	for (i = 0; i < PHILOS; i++)
	{
		pthread_create(&philo[i], NULL, philosopher, (void *)i);
	}
	for (i = 0; i < PHILOS; i++)
	{
		pthread_join(philo[i], NULL);
	}
	return (0);
}

void	*philosopher(void *num)
{
	int	i;
	int	f;
	int	id;
	int	right_chopstick;
	int	left_chopstick;

	i = 0;
	f = 0;
	id = (int)num;
	right_chopstick = id;
	left_chopstick = id + 1;
	printf("Philo [%d] is thinking.\n", id);
	// 箸が一巡した
	if (left_chopstick == PHILOS)
	{
		left_chopstick = 0;
	}
	while ((f = food_on_table()))
	{
		// 箸を取る前にうたた寝をする哲学者１のおかげで、他の哲学者は、デッドロックに陥ることなく食事ができる。
		if (id == 1)
		{
			sleep(sleep_seconds);
		}
		grab_chopstick(id, right_chopstick, "right");
		grab_chopstick(id, left_chopstick, "left");
		printf("Philo [%d] is eating.\n", id);
		usleep(DELAY * (FOOD - f + 1));
		down_chopsticks(left_chopstick, right_chopstick);
	}
	printf("Philo [%d] is sleeping.\n", id);
	return (NULL);


}

int	food_on_table()
{
	static int	food = FOOD;
	int			myfood;

	pthread_mutex_lock(&food_lock);
	if (0 < food)
	{
		food -= 1;
	}
	myfood = food;
	pthread_mutex_unlock(&food_lock);
	return (myfood);
}

void	grab_chopstick(int phil, int c, char *hand)
{
	pthread_mutex_lock(&chopstick[c]);
	printf("Philo [%d] has taken a [%s] fork. [%d]\n", phil, hand, c);
}

void	down_chopsticks(int c1, int c2)
{
	pthread_mutex_unlock(&chopstick[c1]);
	pthread_mutex_unlock(&chopstick[c2]);
}
