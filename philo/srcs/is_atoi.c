/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:37:59 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/12/30 15:24:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"

static bool	is_digits(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		return (false);
	}
	while (ft_isdigit(str[i]))
	{
		i += 1;
	}
	if (str[i] != '\0')
	{
		return (false);
	}
	return (true);
}

static bool	is_change_format(const char *str, int sign)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	if (!is_digits(&str[i]))
		return (false);
	while (ft_isdigit(str[i]))
	{
		if (num <= ((LONG_MAX - (str[i] - '0')) / 10))
		{
			num = (num * 10) + (str[i] - '0');
		}
		else
		{
			return (false);
		}
		i += 1;
	}
	num *= (long long )sign;
	if (num < INT_MIN || INT_MAX < num)
	{
		return (false);
	}
	return (true);
}

static bool	is_sign(const char c)
{
	if (c == '-' || c == '+')
	{
		return (true);
	}
	return (false);
}

static int	proceed_until_space_ends(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
	{
		i += 1;
	}
	return (i);
}

bool	is_atoi(const char *str)
{
	int	i;
	int	sign;

	i = proceed_until_space_ends(str);
	sign = 1;
	if (is_sign(str[i]))
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i += 1;
	}
	return (is_change_format(&str[i], sign));
}
