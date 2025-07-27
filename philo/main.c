/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:24:56 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/27 08:44:00 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(char **argv)
{
	int	i;
	int	j;
	int	num;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][0] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (-1);
			j++;
		}
		num = ft_atoi(argv[i]);
		if (num <= 0)
			return (-1);
		i++;
	}
	return (1);
}

int	monitory_thread(t_config *config)
{
	pthread_t	m_thread;

	if (pthread_create(&m_thread, NULL, monitory, config) != 0)
	{
		pthread_mutex_lock(&config->philo_died);
		config->simulation_end = 1;
		pthread_mutex_unlock(&config->philo_died);
		return (destory_forks(config->nb_philo, config),
			join_philo(config), free_config(config, 3), -1);
	}
	pthread_join(m_thread, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	*config;

	if (argc != 5 && argc != 6)
		return (printf("invalid arguments number\n"), 1);
	if (parse_args(argv) == -1)
		return (printf("invalid number\n"), 1);
	config = malloc(sizeof(t_config));
	if (!config)
		return (-1);
	memset(config, 0, sizeof(t_config));
	if (!init_config(argv, config))
		return (free_all(config), 0);
	return (1);
}
