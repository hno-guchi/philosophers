#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * int	pthread_join(pthread_t thread, void **value_ptr);
 *
 * DESCRIPTION
 * The function suspends execution of the calling thread until the targe [thread] terminates unless the target [thread] has already terminated.
 *
 * [value_ptr] is store the value passed to function by the terminating thread.
 * When a function returns successfully,
 * the [target] thread has been terminated.
 * If the thread calling function is cancelled, then the target thread is not detached.
 *
 * RETURN VALUES
 * If successful, the function will return 0.
 * Otherwise, an error number will be returned to indicate the error.
 * */

void	*thread_func_1(void *arg)
{
	(void)arg;
	printf("Thread 1 returning\n");
	return ((void *)1);
}

void	*thread_func_2(void *arg)
{
	(void)arg;
	printf("Thread 2 exiting\n");
	pthread_exit((void *)2);
}

int	main(void)
{
	int			err;
	pthread_t	new_tid_1;
	pthread_t	new_tid_2;
	void		*thread_return;

	err = pthread_create(&new_tid_1, NULL, thread_func_1, NULL);
	if (err != 0)
	{
		strerror(1); return (0);
	}
	err = pthread_create(&new_tid_2, NULL, thread_func_2, NULL);
	if (err != 0)
	{
		strerror(1); return (0);
	}
	err = pthread_join(new_tid_1, &thread_return);
	if (err != 0)
	{
		strerror(1); return (0);
	}
	printf("Thread 1 exit code [%ld]\n", (long)thread_return);
	err = pthread_join(new_tid_2, &thread_return);
	if (err != 0)
	{
		strerror(1); return (0);
	}
	printf("Thread 2 exit code [%ld]\n", (long)thread_return);
	return (0);
}
