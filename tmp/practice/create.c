#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * man 3 pthread_create
 * int	pthread_create(
 * 					pthread_t *thread
 * 					, const pthread_attr_t *attr
 * 					, void *(start_routine)(void *)
 * 					, void *arg
 * );
 *
 * Create a new thread of execution.
 *
 * pthread_t *restrict	tidp
 * Successful completion pthread_create() will store the [tid] of the new thread in the location specified by [thread].
 *
 * const pthread_attr_t	*attr
 * [attr] specifies attributes of new thread.
 * If [attr] is NULL, the default attributes are used.
 * If the attributes specified by [attr] are modified later, the thread's attributes are not affected.
 *
 * void *(start_routine)(void *)
 * The thread is created executing [start_routine] with [arg] as its sole argument.
 *
 * void	*arg
 *
 * RETURN VALUES
 * If successful, the function will return [0].
 * Otherwise an error number will be returned to indicate the error.
 *
 * ERRORS
 * [EAGAIN]
 * [EPERM]
 * [EINVAL]
 */

void	print_ids(const char *s)
{
	pid_t		p_id;
	pthread_t	t_id;

	p_id = getpid();
	t_id = pthread_self();
	printf("%s p_id [%lu] | t_id [%lu] (0x%lx)\n", s, (unsigned long)p_id, (unsigned long)t_id, (unsigned long)t_id);
}

void	*thread_func(void *arg)
{
	(void)arg;
	print_ids("new  thread : ");
	return ((void *)0);
}

int	main(void)
{
	int			err;
	pthread_t	new_t_id;
	// exit.c
	// void		*thread_return;

	err = pthread_create(&new_t_id, NULL, thread_func, NULL);
	if (err != 0)
	{
		strerror(1);
		return (0);
	}
	print_ids("main thread : ");
	sleep(1);
	// exit.c
	/*
	err = pthread_join(new_t_id, &thread_return);
	if (err != 0)
	{
		strerror(1); return (0);
	}
	printf("Thread 1 exit code [%ld]\n", (long)thread_return);
	*/
	return (0);
}
