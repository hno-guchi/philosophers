/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/30 15:06:02 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		return (0);
	}
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}
