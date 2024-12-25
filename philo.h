#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
 #include <pthread.h>

 

typedef struct	s_simulation
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	long			start_time;
	int				sim_active;


}				t_simulation;

 typedef struct s_philo
 {
	pthread_t		thread;
	int				id;
	long			last_meal;
	int				meals_eaten;
	t_simulation	*sim;

	
 }				t_philo;			

void	run_simulation(char **argv);
void	*philo_routine(void *arg);
long	get_time_in_ms(void);
//t_simulation *sim, t_philo **philos
void	handle_finish();
int		philo_is_even(t_philo philo);
void	think(t_philo *philo,  t_simulation *sim);
void	philo_sleep(t_philo *philo,  t_simulation *sim);
void	think(t_philo *philo,  t_simulation *sim);
void	philo_sleep(t_philo *philo,  t_simulation *sim);
#endif


