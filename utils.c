/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:53:32 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/15 13:35:13 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief custimise usleep to use milliseconds


size_t getcurrenttime()
{
	struct timeval eval;

	if (gettimeofday(&eval, NULL) == -1)
		return (printf("error geting time of today\n"), 1);
	return (eval.tv_sec * 1000 + eval.tv_usec / 1000);
}

int ft_usleep(size_t msecond)
{
	size_t curr_time = getcurrenttime();
	while ((getcurrenttime() - curr_time) < msecond)
		usleep(300);
	return 0;
}