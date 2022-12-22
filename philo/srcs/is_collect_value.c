/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_collect_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/22 14:59:37 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_collect_value(t_time *rules)
{
	if (rules->num_philos <= 0)
	{
		return (false);
	}
	if (rules->time_die <= 0)
	{
		return (false);
	}
	if (rules->time_eat <= 0)
	{
		return (false);
	}
	if (rules->time_sleep <= 0)
	{
		return (false);
	}
	if (rules->num_must_eat != -1)
	{
		if (rules->num_must_eat <= 0)
		{
			return (false);
		}
	}
	return (true);
}
