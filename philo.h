# ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo_config{
	long	time_to_eat;
	long	time_to_die;
	long	time_to_slepp;
	long	mini_meals;
	pthread_mutex_t 	left_fork;
	pthread_mutex_t		right_fork;
}	config;

typedef struct s_philo {
	long	id;

}	t_philo;


#endif