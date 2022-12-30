/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_validation_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/30 19:39:23 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_collectible_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		return (false);
	}
	while (i < argc)
	{
		if (!is_atoi(argv[i]))
		{
			return (false);
		}
		i += 1;
	}
	return (true);
}

static bool	is_arguments(int argc, char **argv)
{
	t_rules	rules;

	set_rules(&rules, argc, argv);
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

bool	is_validation_args(int argc, char **argv)
{
	
	if (!is_collectible_args(argc, argv))
	{
		return (false);
	}
	if (!is_rules(argc, argv))
	{
		return (false);
	}
	return (true);
}
