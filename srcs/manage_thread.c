/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:20:01 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/15 00:07:48 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

int	join_threads(t_resources *rs, t_monitor_rs *monitor)
{
	size_t	i;

	i = 0;
	while (i < rs->input.num_philos)
	{
		if (pthread_join(rs->thread[i], NULL) != 0)
		{
			mutex_collection_destroy(&rs->mutex_collect);
			return (FALSE);
		}
		i++;
	}
	if (pthread_join(monitor->monitor_thread, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

int	create_threads(t_resources *rs, t_monitor_rs *monitor)
{
	long	start_time;

	start_time = get_time_in_ms();
	rs->death_flag = 0;
	if (rs->input.num_philos == 1)
		setup_single_philo(rs, start_time);
	else
		setup_multiple_philos(rs, start_time);
	init_monitor_thread_data(monitor, rs);
	if (pthread_create(&monitor->monitor_thread, NULL, \
		monitor_routine, monitor) != 0)
	{
		printf("pthread_create failed\n");
		mutex_collection_destroy(&rs->mutex_collect);
		return (FALSE);
	}
	return (TRUE);
}
