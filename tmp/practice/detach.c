#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * #include <pthread.h>
 * int	pthread_detach(pthread_t thread);
 * 
 * DESCRIPTION
 * The function is used to indicate to the implementation that storage for the thread [thread] can be reclaimed when the thread terminates.
 *
 * RETURN VALUES
 * If successful, the function will return 0.
 * Otherwise an error number will be returned to indicate the error.
 * */

void	*thread_func(void *arg)
{
	(void)arg;
	printf("Thread 1 returning\n");
	return ((void *)1);
}

int	main(void)
{
	int		err;
	pthread_t	new_tid_1;
	void		*thread_return;
	
	err = pthread_create(&new_tid_1, NULL, thread_func, NULL);
	if (err != 0)
	{
		strerror(1); return (0);
	}
	// err = pthread_detach(new_tid_1);
	err = pthread_join(new_tid_1, &thread_return);
	if (err != 0)
	{
		strerror(1); return (0);
	}
	// err = pthread_join(new_tid_1, &thread_return);
	err = pthread_detach(new_tid_1);
	if (err != 0)
	{
		printf("err is [%d]\n", err);
		strerror(1); return (0);
	}
	sleep(1);
	printf("err is [%d]\n", err);
	return (0);
}
