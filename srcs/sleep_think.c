/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:38:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/25 19:37:55 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

void think(t_philo *philo,  t_simulation *sim)
{
	pthread_mutex_lock(&sim->print_lock);
	printf("%ld philosopher: %d is thinking\n", get_relative_time(*philo), philo->id);
	usleep(sim->time_to_sleep * 1000);
	pthread_mutex_unlock(&sim->print_lock);
}

void philo_sleep(t_philo *philo,  t_simulation *sim)
{
	pthread_mutex_lock(&sim->print_lock);
	printf("%ld philosopher: %d is sleeping\n", get_relative_time(*philo), philo->id);
	usleep(sim->time_to_sleep * 1000);
	pthread_mutex_unlock(&sim->print_lock);
}
