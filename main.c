/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:24:56 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/20 22:26:02 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(char **argv)
{
	int	i;
	int	num;

	i = 1;
	while (argv[i]){
		num = ft_atoi(argv[i]);
		if (num <= 0)
			return (-1);
		i++;
	}
	return (1);
}

void	*philo_routine(void *philo)
{
	t_philo	*p;
	p = (t_philo *)philo;
	if ((p->id % 2) == 0)
		ft_usleep(p->config->time_to_eat / 2);
	while (!simulation_checker(p->config))
	{
		if (p->config->nb_philo == 1)
		{
			print_mutex(p, "has taken a fork");
			philo_sleep(p);
			return (NULL);
		}
		philo_eat(p);
		philo_sleep(p);
		print_mutex(p, "is thinking");
	}
	return (NULL);
}

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
	int i = 0;
	while (i < config->nb_philo)
	{
		pthread_join(config->philosopher->th + i, NULL);
		i++;
	}
}

int init_config(char **args, t_config *config)
{
	int	i;
	int	l;
	int	a;
	pthread_t m_thread;

	i = 0;
	l = 0;
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
	config->forks = malloc (sizeof(pthread_mutex_t) * config->nb_philo);
	if (!config->forks)
		return (free(config), -1);
	memset(config->forks, 0, sizeof(pthread_mutex_t) * config->nb_philo);
	config->philosopher = malloc(sizeof(t_philo) * config->nb_philo);
	if (!config->philosopher)
	{
		free(config->forks);
		free(config);
		return (-1);
	}
	memset(config->philosopher, 0, sizeof(t_philo) * config->nb_philo);; 
	if (pthread_mutex_init(&config->print, NULL) != 0)
		return (free(config->forks), free(config->philosopher), free(config), -1); 
	if (pthread_mutex_init(&config->philo_died, NULL) != 0)
		return (pthread_mutex_destroy(&config->print), free(config->forks), free(config->philosopher), free(config), -1);
	while (i < config->nb_philo)
	{
		if (pthread_mutex_init(config->forks + i, NULL) != 0)
			return (destory_forks(i, config), free(config->forks), free(config->philosopher), free(config),  -1);
		i++;
	}
	t_philo *philo = NULL;
	while (l < config->nb_philo)
	{
		philo = config->philosopher + l;
		philo->config = config;
		philo->id = l + 1;
		philo->last_time_eat = getcurrenttime();
		philo->right_fork = config->forks + l;
		philo->left_fork = config->forks + ((l + 1) % config->nb_philo);
		if (pthread_create(&philo->th, NULL, philo_routine, philo) != 0)
		{
			a = 0;
			pthread_mutex_lock(&config->philo_died);
			config->simulation_end = 1;
			pthread_mutex_unlock(&config->philo_died);
			while (a < l)
			{
				pthread_join(philo->th, NULL);
				a++;
			}
			return (destory_forks(i, config), free(config->forks), free(config->philosopher), free(config), -1);
		}
		l++;
	}
	if (pthread_create(&m_thread, NULL, monitory, config) != 0)
		return  (destory_forks(i , config), config->simulation_end = 1, join_philo(config), free(config->forks), free(config->philosopher), free(config), -1);
	pthread_join(m_thread, NULL);
	int k = 0;
	while (k < config->nb_philo)
	{
		philo = config->philosopher + k;
		pthread_join(philo->th, NULL);
		k++;
	}
	return (1);
}

void free_all(t_config *config)
{
	int i = 0; 
	while (i < config->nb_philo)
	{
		i++;
	}
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
	if (init_config(argv, config))
	{
		free_all(config);
	}
	return (1);
}