#include <stdio.h>
#include <pthread.h>

# define NUM_THREAD 4
# define ADD_NUM 100000

/* 共有データ */
// long long	sum = 0;

/* Mutexオブジェクト */
// pthread_mutex_t	mutex;

/* スレッドに渡すデータ */
typedef struct s_data {
	int				add_num;
	long long		*sum;
	pthread_mutex_t	*mutex;
}	t_data;

void	*add(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	/* add_num回 sum = sum + 1を実行 */
	for (i = 0; i < data->add_num; i++)
	{
		pthread_mutex_lock(data->mutex);
		*data->sum = *data->sum + 1;
		pthread_mutex_unlock(data->mutex);
	}
	return (NULL);
}

int	main(void)
{
	int				i;
	long long		sum;
	pthread_t		thread[NUM_THREAD];
	pthread_mutex_t	mutex;
	t_data			data[NUM_THREAD];

	/* Mutexオブジェクトの初期化 */
	pthread_mutex_init(&mutex, NULL);

	sum = 0;
	for (i = 0; i < NUM_THREAD; i++)
	{
		/* add_numは、NUM_THREADで割り切れることを前提 */
		data[i].add_num = ADD_NUM / NUM_THREAD; // (100000 / 4)
		data[i].sum = &sum;
		data[i].mutex = &mutex;
	}

	/* スレッドの開始 */
	for (i = 0; i < NUM_THREAD; i++)
	{
		pthread_create(&thread[i], NULL, add, &data[i]);
	}

	/* スレッドの終了待ち */
	for (i = 0; i < NUM_THREAD; i++)
	{
		pthread_join(thread[i], NULL);
	}

	/* Mutexオブジェクトの破棄 */
	pthread_mutex_destroy(&mutex);

	/* 計算結果の表示 */
	printf("sum = [%lld]\n", sum);

	return (0);
}
