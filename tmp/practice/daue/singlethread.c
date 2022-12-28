#include <stdio.h>

# define NUM 40

int	main(void)
{
	// 0からNUM-1をカウントする変数
	int	i;
	// 結果を格納する配列
	int	result[NUM];

	// 0からNUM-1の4乗を計算して配列に格納
	for (i = 0; i < NUM; i++)
	{
		result[i] = i * i * i * i;
	}
	return (0);
}
