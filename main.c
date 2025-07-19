/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:24:56 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/19 14:52:24 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	parse_args(char **argv)
{
	int i = 1;
	int num;
	while (argv[i]){
		num = ft_atoi(argv[i]);
		if (num <= 0)
			return (-1);
		i++;
	}
	return (1);
}

void print_config(t_config *config)
{
	if (!config)
	{
		printf("Config is NULL\n");
		return;
	}

	printf("🛠️  Configuration:\n");
	printf("Philosophers Count  : %ld\n", config->nb_philo);
	printf("Time to Die (ms)    : %ld\n", config->time_to_die);
	printf("Time to Eat (ms)    : %ld\n", config->time_to_eat);
	printf("Time to Sleep (ms)  : %ld\n", config->time_to_sleep);
	if (config->mini_meals == -1)
		printf("Minimum Meals       : (not set)\n");
	else
		printf("Minimum Meals       : %ld\n", config->mini_meals);
}


void *philo_routine(void *philo)
{
	t_philo *p;
	p = (t_philo *)philo;
	// if ((p->id % 2) == 0)
	// 	ft_usleep(p->config->time_to_die / 2);
	while (!simulation_checker(p->config))
	{
		if (p->config->nb_philo == 1)
		{
			print_mutex(p, "has taken a fork");
			philo_sleep(p);
			return NULL;
		}
		philo_eat(p);
		philo_sleep(p);
		print_mutex(p, "is thinking");
	}
	return NULL;
}

int init_config(char **args, t_config *config)
{
	int i = 0;
	pthread_t m_thread;
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

	// config->print = malloc(sizeof(pthread_mutex_t));
	// memset(config->print, 0, sizeof(pthread_mutex_t));
	// config->philo_died = malloc(sizeof(pthread_mutex_t));
	// memset(config->philo_died, 0, sizeof(pthread_mutex_t));
	config->forks = malloc (sizeof(pthread_mutex_t) * config->nb_philo);
	memset(config->forks, 0, sizeof(pthread_mutex_t) * config->nb_philo);
	config->philosopher = malloc(sizeof(t_philo) * config->nb_philo);
	memset(config->philosopher, 0, sizeof(t_philo) * config->nb_philo);
	if (!config->philosopher || !config->forks)
		return (-1); 
	if (pthread_mutex_init(&config->print, NULL) != 0)
		return (-1); 
	if (pthread_mutex_init(&config->philo_died, NULL) != 0)
		return (-1);
	while (i < config->nb_philo)
	{
		if (pthread_mutex_init(config->forks + i, NULL) != 0)
		/// destroy mutex
			return (-1);
		i++;
	}
	i = 0;
	t_philo *philo = NULL;
	while (i < config->nb_philo)
	{
		philo = config->philosopher + i;
		philo->config = config;
		philo->id = i + 1;
		philo->last_time_eat = getcurrenttime();
		philo->right_fork = config->forks + i;
		philo->left_fork = config->forks + ((i + 1) % config->nb_philo);
		if (pthread_create(&philo->th, NULL, philo_routine, philo) != 0)
		{
			int j = 0;
			pthread_mutex_lock(&config->philo_died);
			config->simulation_end = 1;
			pthread_mutex_unlock(&config->philo_died);
			while (j < i)
			{
				pthread_join(philo->th, NULL);
				j++;
			}
			/// join
			return (-1);
		}
		i++;
	}
	if (pthread_create(&m_thread, NULL, monitory, config) != 0)
		return  -1;
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

int main (int argc, char **argv)
{
	(void)argc;
	t_config *config;
	config = malloc(sizeof(t_config));
	if (!config)
		return (-1);
	memset(config, 0, sizeof(t_config));
	if (argc != 5 && argc != 6)
		return (printf("invalid arguments number\n"), 1);
	if (parse_args(argv) == -1)
		return (printf("invalid number\n"), 1);
	init_config(argv, config);
	// print_config(config);
	return 1;
}