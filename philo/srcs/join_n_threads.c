/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_n_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 12:32:55 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_n_threads(t_info *info, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(info->threads[i], NULL);
		i += 1;
	}
}
