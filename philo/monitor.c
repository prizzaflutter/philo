/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:16:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/26 17:45:28 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died_detector(t_philo *philo)
{
	print_mutex(philo, "died");
}

void	monitory_helper(t_config *config, int *philo_counter)
{
	int		i;
	t_philo	*philo;
	long	time_wait;

	i = 0;
	time_wait = 0;
	while (i < config->nb_philo)
	{
		philo = config->philosopher + i;
		pthread_mutex_lock(&config->philo_died);
		time_wait = (getcurrenttime() - philo->last_time_eat);
		pthread_mutex_unlock(&config->philo_died);
		if (time_wait > config->time_to_die)
		{
			philo_died_detector(philo);
			break ;
		}
		pthread_mutex_lock(&config->philo_died);
		if (config->mini_meals != -1
			&& philo->meals_eaten >= config->mini_meals)
			(*philo_counter)++;
		pthread_mutex_unlock(&config->philo_died);
		i++;
	}
}

void	*monitory(void *arg)
{
	t_config	*config;
	int			philo_counter;

	config = (t_config *)arg;
	while (!simulation_checker(config))
	{
		philo_counter = 0;
		monitory_helper(config, &philo_counter);
		if (philo_counter == config->nb_philo)
		{
			pthread_mutex_lock(&config->philo_died);
			config->simulation_end = 1;
			pthread_mutex_unlock(&config->philo_died);
		}
		usleep(100);
	}
	return (NULL);
}
