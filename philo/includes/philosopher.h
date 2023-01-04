/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:34:44 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/04 11:04:08 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

bool	is_info_died(t_info *info);
bool	is_eaten_at_least_n_times(t_info *info, t_philo *philo);
bool	is_finish(t_info *info, t_philo *philo);
void	finely_usleep(int limit, long long base);
void	try_usleep_200(int index);

#endif
