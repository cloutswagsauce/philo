/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:45:47 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/25 16:56:32 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"

long get_time_in_ms(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_sec * 1000 + time.tv_sec / 1000;
}

void handle_finish()
{
	//t_simulation *sim, t_philo **philos
	// free dynamically stored memory
	//  destry mutexes
}

int	philo_is_even(t_philo philo)
{
	if (philo.id % 2 == 0)
		return (1);
	return (0);
}