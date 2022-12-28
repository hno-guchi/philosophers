/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/28 11:01:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	main(void)
{
	// pthread_mutex_t	*fork;
	// pthread_t		*philo;
	pthread_mutex_t	food_lock;
	// int				sleep_seconds;

	// sleep_seconds = 0;
	if (argc != 5 && argc != 6)
	{
		return (0);
	}
	initialize_time(&rules, argc, argv);
	if (!is_collect_value(&rules))
	{
		return (0);
	}
	pthread_mutex_init(&food_lock, NULL);
	create_philos(rules);
	// execute_philo
	// finish_philo
	return (0);
}
*/

bool	is_arguments(int argc, char argv)
{
	int	i;
	int	num_philo;

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
	num_philo = ft_atoi(argv[1]);
	if (300 <= num_philo)
	{
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_time			rules;
	// pthread_mutex_t	*fork;
	// pthread_t		*philo;
	pthread_mutex_t	food_lock;
	// int				sleep_seconds;

	// sleep_seconds = 0;
	if (is_arguments(argc, argv))
	{
		return (0);
	}
	initialize_time(&rules, argc, argv);
	if (!is_collect_value(&rules))
	{
		return (0);
	}
	pthread_mutex_init(&food_lock, NULL);
	create_philos(rules);
	// execute_philo
	// finish_philo
	return (0);
}
	// printf("[OK]"); printf(" : initialize_time();\n");
