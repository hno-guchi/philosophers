/*
 * #include <sys/time.h>
 * int	gettimeofday(struct timeval *restrict tp, void *restrict tzp);
 *
 * DESCRIPTION
 * struct timeval {
 * 		time_t		tv_sec;		// seconds since Jan. 1, 1970
 * 		suseconds_t	tv_usec;	// and microseconds
 * };
 *
 * The [timeval] structure specifies a time value in seconds and microseconds.
 * Tne value in [timeval] are opaque types whose length may vary on different machines.
 * depending on them to have any given length may lead to errors.
 *
 * RETURN
 * A 0 return value indicates that the call succeeded.
 * A -1 return value indicates an error occurred,
 * and in this case an error code is stored into the gloval variable [errno].
 *
 * */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

// int	main(int argc, char **argv)
int	main(void)
{
	struct timeval	time;
	long long		start_time = 0;
	long long		passed_time = 0;
	long long		diff_time = 0;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Wrong argument.\n");
		return (0);
	}
	// ミリ秒(ms)に変換
	start_time = (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000));
	printf("start [%lld]\n", start_time);
	for (int i = 0; i < 10; i++)
	{
		usleep(50000);
		if (gettimeofday(&time, NULL) == -1)
		{
			printf("Wrong argument.\n");
			return (0);
		}
		passed_time = (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000));
		diff_time = (passed_time - start_time) - diff_time;
		printf("[%d]:pass [%3lld] -> [%3lld]\n", i, passed_time - start_time, diff_time);
		diff_time = passed_time - start_time;
	}
	return (0);
}
