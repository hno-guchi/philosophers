#include <stdio.h>
#include <pthread.h>

# define NUM_THREAD 4
# define ADD_NUM 100000

struct s_info;

/* スレッドに渡すデータ */
typedef struct s_data {
	int					add_num;
	struct s_info		*info;
}	t_data;

/* スレッドで共有するデータ */
typedef struct s_info {
	t_data			data[NUM_THREAD];
	pthread_t		threads[NUM_THREAD];
	pthread_mutex_t	mutex;	// Mutex オブジェクト
	long long		sum;	// 共有データ
}	t_info;

void	*add(void *arg)
{
	int		i;
	t_data	*data;
	t_info	*info;

	data = (t_data *)arg;
	info = (t_info *)data->info;
	/* add_num回 sum = sum + 1を実行 */
	for (i = 0; i < data->add_num; i++)
	{
		pthread_mutex_lock(&info->mutex);
		info->sum = info->sum + 1;
		pthread_mutex_unlock(&info->mutex);
	}
	return (NULL);
}

int	main(void)
{
	int		i;
	t_info	info;

	// t_infoの初期化
	/* Mutexオブジェクトの初期化 */
	pthread_mutex_init(&info.mutex, NULL);

	info.sum = 0;
	for (i = 0; i < NUM_THREAD; i++)
	{
		/* add_numは、NUM_THREADで割り切れることを前提 */
		info.data[i].add_num = ADD_NUM / NUM_THREAD; // (100000 / 4)
		info.data[i].info = &info;
	}

	/* スレッドの開始 */
	for (i = 0; i < NUM_THREAD; i++)
	{
		pthread_create(&info.threads[i], NULL, add, &info.data[i]);
	}

	/* スレッドの終了待ち */
	for (i = 0; i < NUM_THREAD; i++)
	{
		pthread_join(info.threads[i], NULL);
	}

	/* Mutexオブジェクトの破棄 */
	pthread_mutex_destroy(&info.mutex);

	/* 計算結果の表示 */
	printf("info.sum = [%lld]\n", info.sum);

	return (0);
}
