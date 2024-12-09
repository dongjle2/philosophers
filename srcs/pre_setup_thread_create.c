/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_setup_thread_create.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:40:20 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/06 00:39:45 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	setup_single_philo(t_resources *rs, long start_time)
{
	size_t	i;

	i = 0;
	rs->philos_data[i].forks[i] = &rs->forks[i];
	setup_philo_data(rs, i, start_time);
	pthread_create(&rs->thread[i], \
						NULL, single_philo_routine, &rs->philos_data[i]);
}

void	setup_multiple_philos(t_resources *rs, long start_time)
{
	size_t	i;

	i = 0;
	while (i < rs->input.num_philos)
	{
		rs->philos_data[i].forks[0] = &rs->forks[i];
		rs->philos_data[i].forks[1] = \
								&rs->forks[(i + 1) % rs->input.num_philos];
		setup_philo_data(rs, i, start_time);
		pthread_create(&rs->thread[i], NULL, routine, &rs->philos_data[i]);
		i++;
	}
}
