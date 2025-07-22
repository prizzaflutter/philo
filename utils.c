/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:53:32 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/22 10:42:22 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getcurrenttime(void)
{
	struct timeval	eval;

	if (gettimeofday(&eval, NULL) == -1)
		return (printf("error geting time of today\n"), 1);
	return (eval.tv_sec * 1000 + eval.tv_usec / 1000);
}

int	ft_usleep(long msecond)
{
	long	curr_time;

	curr_time = getcurrenttime();
	while ((getcurrenttime() - curr_time) < msecond)
		usleep(300);
	return (0);
}
