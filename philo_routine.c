/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:52:40 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/22 10:44:20 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_mutex(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_mutex(philo, "has taken a fork");
	print_mutex(philo, "is eating");
	ft_usleep(philo->config->time_to_eat);
	pthread_mutex_lock(&philo->config->philo_died);
	philo->meals_eaten++;
	philo->last_time_eat = getcurrenttime();
	pthread_mutex_unlock(&philo->config->philo_died);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_mutex(philo, "is sleeping");
	ft_usleep(philo->config->time_to_sleep);
}
