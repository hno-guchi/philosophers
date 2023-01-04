/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 12:34:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_philosophers(t_info *info)
{
	join_n_threads(info, info->rules.num_philo);
	pthread_join(info->death_monitor, NULL);
	destroy_all_mutex(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!is_validation_args(argc, argv))
	{
		return (0);
	}
	if (set_info(&info, argc, argv) == ERROR)
	{
		return (0);
	}
	if (create_threads(&info) == ERROR)
	{
		destroy_all_mutex(&info);
		return (0);
	}
	end_philosophers(&info);
	return (0);
}
// printf(GREEN"[OK]"END); printf(" : function();\n");
// printf(RED"[Error]"END); printf(" : ();\n");
