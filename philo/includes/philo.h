/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:34:44 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/22 14:54:41 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

typedef struct s_time {
	int	num_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_must_eat;
}	t_time;

int		ft_atoi(const char *str);
void	initialize_time(t_time *rules, int argc, char **argv);
bool	is_collect_value(t_time *rules);


#endif
