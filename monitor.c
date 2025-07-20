/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:16:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/20 20:39:10 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitory(void *arg)
{
	t_config *config = (t_config *)arg;
	while (!simulation_checker(config))
	{
		int i = 0;
		int philo_counter = 0;
		long time_wait = 0;
		t_philo *philo;
		while (i < config->nb_philo)
		{
			philo = config->philosopher + i;
			pthread_mutex_lock(&config->philo_died);
			time_wait = (getcurrenttime() - philo->last_time_eat);
			pthread_mutex_unlock(&config->philo_died);
			if (time_wait > config->time_to_die)
			{
				print_mutex(philo, "died");
				pthread_mutex_lock(&config->philo_died);
				config->simulation_end = 1;
				pthread_mutex_unlock(&config->philo_died);
				break ;
			}
			
			pthread_mutex_lock(&philo->config->philo_died);
			if (config->mini_meals != -1 &&  philo->meals_eaten >= config->mini_meals)
			{
				philo_counter++;
			}
			pthread_mutex_unlock(&philo->config->philo_died);
		 	i++;
		}
		if (philo_counter == config->nb_philo)
		{
			pthread_mutex_lock(&config->philo_died);
			config->simulation_end = 1;
			pthread_mutex_unlock(&config->philo_died);
		}
		usleep(100);
	}
	return NULL;
}