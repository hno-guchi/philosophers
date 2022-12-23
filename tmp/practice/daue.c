#include <stdio.h>
#include <pthread.h>

# define NUM_THREAD 4
# define ADD_NUM 100000

// 共有データ
long long	sum = 0;

// Mutex object
pthread_mutex_t	mutex;

// スレッドに渡すデータ
typedef struct thread_data {
	int	addNum;
}	THREAD_DATA;

void	*add(void *arg) {
	int	i;
	THREAD_DATA	*data = (THREAD_DATA *)arg;;

	// addNum回 sum = sum + 1を実行
	for (i = 0; i < data->addNum; i++) {
		// 排他制御部分
		pthread_mutex_lock(&mutex);
		sum = sum + 1;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(void) {
	pthread_t	thread[NUM_THREAD];
	THREAD_DATA	data[NUM_THREAD];
	int			i;

	// Initialize Mutex object
	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < NUM_THREAD; i++) {
		// ADD_NUMは、NUM_THREADで割り切れることを前提
		data[i].addNum = ADD_NUM / NUM_THREAD;
	}

	// スレッドの開始
	for (i = 0; i < NUM_THREAD; i++) {
		pthread_create(&thread[i], NULL, add, &data[i]);
	}

	// スレッドの終了待ち
	for (i = 0; i < NUM_THREAD; i++) {
		pthread_join(thread[i], NULL);
	}

	// Destroy mutex object
	pthread_mutex_destroy(&mutex);

	// 計算結果の表示
	printf("sum = [%lld]\n", sum);

	return (0);
}
