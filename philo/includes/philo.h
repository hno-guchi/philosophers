/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:34:44 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/30 20:31:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SUCCESS 0
# define ERROR 1
# define DEAD 2
# define FINISH true

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define END "\x1b[39m"

struct	s_info;

typedef struct	s_philo {
	int				index;
	int				right_fork_index;
	int				left_fork_index;
	long long		time_last_meal;
	int				count_eat;
	int				died;
	// bool			full;
	struct s_info	*info;
}	t_philo;

typedef struct	s_rules {
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	eat_minimum_times;
}	t_rules;

typedef struct	s_info {
	t_rules			rules;
	long long		time_start;
	int				died;
	t_philo			philos[300];
	pthread_t		threads[300];
	pthread_t		monitor_thread;
	pthread_mutex_t	forks[300];
	pthread_mutex_t	count_eat_mutex;
	pthread_mutex_t	died_mutex;
}	t_info;

int			ft_atoi(const char *str);
bool		is_atoi(const char *str);
void		destroy_n_forks_mutex(t_info *info, int n);
void		set_rules(t_rules *rules, int argc, char **argv);
int			set_info(t_info *info, int argc, char **argv);
long long	get_time_ms();
void		finely_usleep(int limit, long long base);
bool		is_validation_args(int argc, char **argv);
void		*philosopher(void *data);

#endif
