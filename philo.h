# ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_philo t_philo;

typedef struct s_config{
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	mini_meals;
	int		simulation_end;
	long	start_time;
	t_philo	*philosopher;
	pthread_mutex_t	*forks;
	pthread_mutex_t print;
	pthread_mutex_t philo_died;
}	t_config;

struct s_philo {
	int				id;
	pthread_t		th;
	t_config		*config;
	long			last_time_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
};


int		ft_atoi(const char *str);
long	getcurrenttime();
int		ft_usleep(size_t msecond);
void	print_mutex(t_philo *philo, const char *message);
void	philo_eat(t_philo *philo);
int		simulation_checker(t_philo *philo);
void	philo_sleep(t_philo *philo);

#endif