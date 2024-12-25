/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:12:16 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/25 19:23:47 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

int	case_even(t_philo philo, t_simulation *sim)
{
	long	timeout_ms;
	long	start_time;

	timeout_ms = 10;
	start_time = get_time_in_ms();
	pthread_mutex_lock(&sim->forks[philo.id % sim->num_of_philos]);
	pthread_mutex_lock(&sim->print_lock);
	printf("%ld philosopher: %d has taken right fork \n", get_time_in_ms(), philo.id);
	pthread_mutex_unlock(&sim->print_lock);
	while (pthread_mutex_lock(&sim->forks[philo.id - 1]) != 0)
	{
		if (get_time_in_ms() - start_time >= timeout_ms)
		{
			pthread_mutex_unlock(&sim->forks[philo.id % sim->num_of_philos]);
			return (0);
		}
	}
	pthread_mutex_lock(&sim->print_lock);
	printf("%ld philosopher: %d has taken left fork \n", get_time_in_ms(), philo.id);
	pthread_mutex_unlock(&sim->print_lock);
	return (1);
}

int	case_odd(t_philo philo, t_simulation *sim)
{
	long	timeout_ms;
	long	start_time;

	timeout_ms = 10;
	start_time = get_time_in_ms();
	pthread_mutex_lock(&sim->forks[philo.id - 1]);
	pthread_mutex_lock(&sim->print_lock);
	printf("%ld philosopher: %d has taken left fork \n", get_time_in_ms(), philo.id);
	pthread_mutex_unlock(&sim->print_lock);
	while (pthread_mutex_lock(&sim->forks[philo.id % sim->num_of_philos]))
	{
		if (get_time_in_ms() - start_time >= timeout_ms)
		{
			pthread_mutex_unlock(&sim->forks[philo.id - 1]);
			return (0);
		}
	}
	pthread_mutex_lock(&sim->print_lock);
	printf("%ld philosopher: %d has taken right fork \n", get_time_in_ms(), philo.id);
	pthread_mutex_unlock(&sim->print_lock);
	return (1);
}

void	eat(t_philo *philo, t_simulation *sim)
{
	pthread_mutex_lock(&sim->print_lock); // locks printing
	printf("%ld philosopher: %d is eating, has eaten %d times \n", get_time_in_ms(), philo->id, philo->meals_eaten);
	usleep(sim->time_to_eat * 1000);
	// converts ms to micro, sleeps for that time
	pthread_mutex_unlock(&sim->print_lock);
	// unlocks
	philo->last_meal = get_time_in_ms();
	// sets last meal time to now
	philo->meals_eaten++;
	// increases meak eaten count
	pthread_mutex_unlock(&sim->forks[(*philo).id % sim->num_of_philos]);
	// unlocks both forks
	pthread_mutex_unlock(&sim->forks[(*philo).id - 1]);
}

int	try_get_forks(t_philo *philo, t_simulation *sim)
{
	int	has_both_forks;

	if (philo_is_even((*philo)))
		has_both_forks = case_even(*philo, sim);
	else
		has_both_forks = case_odd(*philo, sim);
	if (has_both_forks)
		return (1);
	else
		return (0);
}

void	*philo_routine(void *arg)
{
	// if this is true, call eat
	t_philo		*philo;
	t_simulation *sim;

	philo = (t_philo *)(arg);
	sim = (t_simulation *)philo->sim;
	while (sim->must_eat_count == -1
		|| philo->meals_eaten < sim->must_eat_count)
	{
		if (try_get_forks(philo, sim))
		{
			eat(philo, sim);
			think(philo, sim);
			philo_sleep(philo, sim);
		}
		else
		{
			think(philo, sim);
			philo_sleep(philo, sim);
		};
	}
	return 0 ;
}
