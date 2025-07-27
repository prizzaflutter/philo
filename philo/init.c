/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:36:16 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/27 09:13:40 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	first_init(char **args, t_config *config)
{
	config->nb_philo = ft_atoi(args[1]);
	config->time_to_die = ft_atoi(args[2]);
	config->time_to_eat = ft_atoi(args[3]);
	config->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		config->mini_meals = ft_atoi(args[5]);
	else
		config->mini_meals = -1;
	config->simulation_end = 0;
	config->start_time = getcurrenttime();
	config->forks = malloc(sizeof(pthread_mutex_t) * config->nb_philo);
	if (!config->forks)
		return (free(config), -1);
	memset(config->forks, 0, sizeof(pthread_mutex_t) * config->nb_philo);
	config->philosopher = malloc(sizeof(t_philo) * config->nb_philo);
	if (!config->philosopher)
		return (free_config(config, 2), -1);
	memset(config->philosopher, 0, sizeof(t_philo) * config->nb_philo);
	if (pthread_mutex_init(&config->print, NULL) != 0)
		return (free_config(config, 3), -1);
	if (pthread_mutex_init(&config->philo_died, NULL) != 0)
		return (pthread_mutex_destroy(&config->print),
			free_config(config, 3), -1);
	return (1);
}

int	init_philo(t_config *config)
{
	t_philo	*philo;
	int		l;

	philo = NULL;
	l = 0;
	while (l < config->nb_philo)
	{
		philo = config->philosopher + l;
		philo->config = config;
		philo->id = l + 1;
		philo->last_time_eat = getcurrenttime();
		philo->right_fork = config->forks + l;
		philo->left_fork = config->forks + ((l + 1) % config->nb_philo);
		if (pthread_create(&philo->th, NULL, philo_routine, philo) != 0)
			return (join_and_free(config, l), -1);
		l++;
	}
	return (1);
}

int	init_config(char **args, t_config *config)
{
	int		i;
	int		k;
	t_philo	*philo;

	i = 0;
	k = 0;
	if (first_init(args, config) == -1)
		return (-1);
	while (i < config->nb_philo)
	{
		if (pthread_mutex_init(config->forks + i, NULL) != 0)
			return (destory_forks(i, config), free_config(config, 3), -1);
		i++;
	}
	if (init_philo(config) == -1 || monitory_thread(config) == -1)
		return (-1);
	while (k < config->nb_philo)
	{
		philo = config->philosopher + k;
		pthread_join(philo->th, NULL);
		k++;
	}
	return (0);
}
