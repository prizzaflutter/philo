/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:12:49 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/26 17:51:25 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_philo *philo, const char *message)
{
	if (simulation_checker(philo->config))
		return ;
	pthread_mutex_lock(&philo->config->print);
	if (message[0] == 'd')
	{
		printf("%ld %d %s\n", (getcurrenttime()
				- (philo->config->start_time)), philo->id, message);
		pthread_mutex_lock(&philo->config->philo_died);
		philo->config->simulation_end = 1;
		pthread_mutex_unlock(&philo->config->philo_died);
		pthread_mutex_unlock(&philo->config->print);
		return ;
	}
	if (!simulation_checker(philo->config))
	{
		printf("%ld %d %s\n", (getcurrenttime()
				- (philo->config->start_time)), philo->id, message);
	}
	pthread_mutex_unlock(&philo->config->print);
}

int	simulation_checker(t_config *config)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&config->philo_died);
	ret = config->simulation_end;
	pthread_mutex_unlock(&config->philo_died);
	return (ret);
}
