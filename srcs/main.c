/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:17:13 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/12/25 19:26:34 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../philo.h"


int main(int argc, char **argv)
{
	if (argc == 6 ||argc == 5)
	{
		run_simulation(argv);
		return (0);
	}
	else
		return (1);
}




