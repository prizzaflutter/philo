/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:52:40 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/27 08:52:00 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->config->nb_philo == 1)
	{
		pthread_mutex_lock(p->right_fork);
		print_mutex(p, "has taken a fork");
		pthread_mutex_unlock(p->right_fork);
		ft_usleep(p->config->time_to_die, p->config);
		return (NULL);
	}
	if ((p->id % 2) == 0)
		ft_usleep(p->config->time_to_eat / 2, p->config);
	while (!simulation_checker(p->config))
	{
		philo_eat(p);
		philo_sleep(p);
		print_mutex(p, "is thinking");
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_mutex(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&philo->config->philo_died);
	philo->last_time_eat = getcurrenttime();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->config->philo_died);
	print_mutex(philo, "is eating");
	ft_usleep(philo->config->time_to_eat, philo->config);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_mutex(philo, "is sleeping");
	ft_usleep(philo->config->time_to_sleep, philo->config);
}
