#include <stdlib.h>
#include <pthread.h>

struct	foo {
	int	f_count;
	pthread_mutex_t	f_lock;
	int	f_id;
	// 必要なものが続く
};

// オブジェクトを割り付ける
struct foo	*foo_alloc(int id)
{
	struct foo	*fp;

	if (fp = malloc(sizeof(struct foo)) != NULL)
	{
		fp->count = 1;
		fp->id = id;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
		{
			free(fp);
			return (NULL);
		}
		// 初期化が続く
	}
	return (fp);
}

// オブジェクトへの参照を追加
void	foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count += 1;
	pthread_mutex_unlock(&fp->f_lock);
}

// オブジェクトへの参照を解放
void	foo_rele(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	if ((fp->f_count - 1) == 0)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
	else
	{
		pthread_mutex_unlock(&fp->f_lock);
	}
}
