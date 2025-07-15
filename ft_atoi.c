/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:11:50 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/15 13:28:51 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	long	holder;
	int		muns;

	holder = 0;
	while (*str != '\0' && ((*str >= 9 && *str <= 13) || (*str == 32)))
		str++;
	muns = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			muns = -1;
		str++;
	}
	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		if (num < holder)
			return (-(muns + 1) / 2);
		holder = num;
		str++;
	}
	return (num * muns);
}