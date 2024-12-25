/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:26:14 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/25 19:20:55 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"


int init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	// memory allocation for aray of mutex representing fork (this locks the resource)
	sim->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* sim->num_of_philos);
	if (!sim->forks)
	{
		perror("mutex malloc failed");
		return (1);
	}
		
	// memory allocation for each mutex!
	while (i < sim->num_of_philos)
	{
		//init mutex for each fork
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_simulation *sim, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = (t_philo *)(malloc(sizeof(t_philo) * sim->num_of_philos));
	if (!*philos)
	{
		perror("malloc failed for philos");
		return (1);
	}
	memset(*philos, 0, sizeof(t_philo) * sim->num_of_philos); // Zero all fields
	while (i < sim->num_of_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal = sim->start_time;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].sim = sim;
		if (pthread_create(&(*philos)[i].thread, NULL, philo_routine,(void *) &(*philos)[i]))
		{
			//free(philos);
			return (1);
		}
		printf("Initializing philosopher %d with ID: %d\n", i, (*philos)[i].id);
		i++;
	}
	return (0);
}

void init_simulation(char **argv, t_simulation *sim)
{
	sim->num_of_philos = atoi(argv[1]);
	sim->time_to_die = atoi(argv[2]);
	sim->time_to_eat = atoi(argv[3]);
	sim->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		sim->must_eat_count = atoi(argv[5]);
	else
		sim->must_eat_count = -1;
	sim->start_time = get_time_in_ms();
	
}

void run_simulation(char **argv)
{
	t_simulation	sim;
	t_philo			*philos;
	int				i;

	i = 0;

	init_simulation(argv, &sim);
	init_forks(&sim);
	init_philos(&sim, &philos);
	while (i < sim.num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	//handle_finish(&sim, &philos);
	
	
}
