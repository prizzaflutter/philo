/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:38:13 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/22 11:09:54 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destory_forks(int i, t_config *config)
{
	int	j;

	j = 0;
	pthread_mutex_destroy(&config->print);
	pthread_mutex_destroy(&config->philo_died);
	while (j < i)
	{
		pthread_mutex_destroy(config->forks + j);
		j++;
	}
}

void	join_philo(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nb_philo)
	{
		pthread_join(config->philosopher->th + i, NULL);
		i++;
	}
}

void	free_config(t_config *config, int how_many)
{
	if (how_many == 1)
		free(config);
	else if (how_many == 2)
	{
		free(config->forks);
		free(config);
	}
	else
	{
		free(config->forks);
		free(config->philosopher);
		free(config);
	}
}

void	join_and_free(t_config *config, int l)
{
	int		a;
	t_philo	*philo;

	a = 0;
	pthread_mutex_lock(&config->philo_died);
	config->simulation_end = 1;
	pthread_mutex_unlock(&config->philo_died);
	while (a < l)
	{
		philo = config->philosopher + a;
		pthread_join(philo->th, NULL);
		a++;
	}
	destory_forks(config->nb_philo, config);
	free_config(config, 3);
}

void	free_all(t_config *config)
{
	destory_forks(config->nb_philo, config);
	free(config->forks);
	free(config->philosopher);
	free(config);
}
