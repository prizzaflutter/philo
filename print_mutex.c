/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:12:49 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/19 11:21:04 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_philo *philo, const char *message)
{
	pthread_mutex_lock(philo->config->print);
	printf("%ld %d %s\n", (getcurrenttime - (philo->config->start_time)), philo->id, message);
	pthread_mutex_unlock(philo->config->print);
}
