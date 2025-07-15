/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:24:56 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/15 16:18:55 by iaskour          ###   ########.fr       */
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

/// philosopher routine

// void *philosopher_routine(void *arg)
// {
// 	(void)arg;
// }

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
	
}

int init_config(char **args, t_config *config)
{
	int i = 0;
	config->nb_philo = ft_atoi(args[1]);
	config->time_to_die = ft_atoi(args[2]);
	config->time_to_eat = ft_atoi(args[3]);
	config->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		config->mini_meals = ft_atoi(args[5]);
	else
		config->mini_meals = -1;
	config->forks = malloc (sizeof(pthread_mutex_t) * config->nb_philo);
	config->philosopher = malloc(sizeof(t_philo) * config->nb_philo);
	if (!config->philosopher || !config->forks)
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
		philo->id = i + 1;
		philo->last_time_eat = getcurrenttime();
		if (pthread_create(&config->philosopher->th, NULL, philo_routine, philo) != 0)
			/// join
			return (-1);
		i++;
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
	if (argc != 5 && argc != 6)
		return (printf("invalid arguments number\n"), 1);
	if (parse_args(argv) == -1)
		return (printf("invalid number\n"), 1);
	/// initialization
	init_config(argv, config);
	print_config(config);
	return 1;
}