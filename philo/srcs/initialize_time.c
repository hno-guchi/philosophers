/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/22 14:55:53 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initialize_set_zero(t_time *rules)
{
	rules->num_philos = 0;
	rules->time_die = 0;
	rules->time_eat = 0;
	rules->time_sleep = 0;
	rules->num_must_eat = 0;
}

void	initialize_time(t_time *rules, int argc, char **argv)
{
	initialize_set_zero(rules);
	rules->num_philos = ft_atoi(argv[1]);
	rules->time_die = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		rules->num_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		rules->num_must_eat = -1;
	}
}
