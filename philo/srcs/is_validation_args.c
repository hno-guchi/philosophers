/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_validation_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 10:19:47 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_collectible_args(int argc, char **argv)
{
	int	i;

	i = 1;
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

static bool	is_rules(t_rules *rules)
{
	if (rules->num_philo <= 0)
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
	if (rules->eat_minimum_times != -1)
	{
		if (rules->eat_minimum_times <= 0)
		{
			return (false);
		}
	}
	return (true);
}

bool	is_validation_args(int argc, char **argv)
{
	t_rules	rules;

	if (!is_collectible_args(argc, argv))
	{
		return (false);
	}
	set_rules(&rules, argc, argv);
	if (!is_rules(&rules))
	{
		return (false);
	}
	return (true);
}
// printf(GREEN"[OK]"END); printf(" : FUNCTION_NAME();\n");
// printf(RED"[Error]"END); printf(" : FUNCTION_NAME();\n");
// printf(RED"[Error]"END); printf(" : is_collectible_args();\n");
// printf(RED"[Error]"END); printf(" : is_rules();\n");
