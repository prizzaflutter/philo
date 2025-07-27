/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:44:33 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/26 14:14:49 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_config
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			mini_meals;
	int				simulation_end;
	long			start_time;
	t_philo			*philosopher;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	philo_died;
}	t_config;

struct s_philo
{
	int				id;
	pthread_t		th;
	t_config		*config;
	long			last_time_eat;
	long			meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
};

long	ft_atoi(const char *str);
long	getcurrenttime(void);
int		ft_usleep(long msecond, t_config *config);
void	print_mutex(t_philo *philo, const char *message);
void	philo_eat(t_philo *philo);
int		simulation_checker(t_config *config);
void	philo_sleep(t_philo *philo);
void	*monitory(void *arg);
void	destory_forks(int i, t_config *config);
void	join_philo(t_config *config);
void	free_config(t_config *config, int how_many);
void	join_and_free(t_config *config, int l);
int		init_config(char **args, t_config *config);
void	free_all(t_config *config);
int		monitory_thread(t_config *config);
void	*philo_routine(void *philo);
int		ft_isdigit(int c);

#endif