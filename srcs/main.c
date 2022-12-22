/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:10:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/22 12:15:33 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

int	print_error_message(char *message)
{
	printf("%s\n", message);
	return (0);
}

int	main(int argc, char *argv)
{
	if (argc < 5 || 6 < argc)
	{
		return (print_error_message("Wrong argument!!"));
	}
	// initialize_philo(argv);
	// execute_philo
	// finish_philo
	return (0);
}
