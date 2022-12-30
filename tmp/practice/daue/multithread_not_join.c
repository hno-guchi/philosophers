#include <stdio.h>
#include <pthread.h>

# define NUM 40
# define NUM_THREAD 2

/* thread実行に必要なデータを格納する構造体 */
struct data {
	int	start;		// 計算開始する数
	int	num;		// 計算を行う回数
	int	*result;	// 計算結果を格納するアドレス
};

/* 関数func：スレッドで行う処理 */
/* 引数arg ：スレッドで行う処理に必要な情報 */
void	*func(void *arg)
{
	int	i;
	struct data	*pd = (struct data *)arg;

	/* argに指定された情報に基づいて処理 */
	for (i = pd->start; i < pd->start + pd->num; i++)
	{
		pd->result[i] = i * i * i * i;
	}
	return (NULL);
}

int	main(void)
{
	int			i;					// (NUM - 1)をカウントする変数
	int			result[NUM] = {0};	// 結果を格納する配列
	pthread_t	threads[NUM];		// threadを格納する配列
	struct data	date[NUM_THREAD];	// スレッドを実行する上で必要な情報を格納する配列

	/* １つ目のスレッドを行う上で必要な情報を格納 */
	date[0].start = 0;
	date[0].num = NUM / 2;
	date[0].result = result;
	/* １つ目のスレッドを作成 */
	pthread_create(&threads[0], NULL, func, &date[0]);

	/* ２つ目のスレッドを行う上で必要な情報を格納 */
	date[1].start = NUM / 2;
	date[1].num = NUM / 2;
	date[1].result = result;
	/* ２つ目のスレッドを作成 */
	pthread_create(&threads[1], NULL, func, &date[1]);

	for (i = 0; i < NUM; i++)
	{
		if (i == 10)
		{
			printf("\n");
		}
		printf(" [%d] >", result[i]);
	}

	/* スレッドの終了を待機 */
	// pthread_join(threads[0], NULL);
	// pthread_join(threads[1], NULL);

	return (0);
}
