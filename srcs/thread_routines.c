/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:44:14 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/12 20:14:49 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	ck_last_meal_time(t_monitor_rs *monitor, size_t i)
{
	long	ret;

	pthread_mutex_lock(monitor->philos_data[i].last_meal_time_mutex);
	ret = monitor->philos_data[i].last_meal_time;
	pthread_mutex_unlock(monitor->philos_data[i].last_meal_time_mutex);
	return (ret);
}

void	*monitor_routine(void *arg)
{
	t_monitor_rs	*monitor;
	size_t			i;

	monitor = (t_monitor_rs *)arg;
	while (42)
	{
		if (!ck_death_flag_on(monitor->death_flag_mutex, monitor->death_flag))
			return (NULL);
		i = 0;
		while (i < monitor->input->num_philos)
		{
			if (monitor->input->ttd < get_time_in_ms() - \
											ck_last_meal_time(monitor, i))
			{
				if (ck_total_eat_value(monitor->philos_data[i].total_eat_mutex, \
									&monitor->philos_data[i].input->total_eat))
					print_status(&monitor->philos_data[i], DIE);
				set_death_flag_on(monitor->death_flag_mutex, \
									monitor->death_flag);
				return (NULL);
			}
			i++;
			usleep(10);
		}
	}
}

void	*single_philo_routine(void *arg)
{
	t_philos_data	*cur;

	cur = (t_philos_data *)arg;
	take_forks_single_philo(cur);
	pthread_mutex_unlock(&cur->forks[0]);
	while (42)
	{
		pthread_mutex_lock(cur->death_flag_mutex);
		if (*cur->death_flag)
		{
			pthread_mutex_unlock(cur->death_flag_mutex);
			return (FALSE);
		}
		pthread_mutex_unlock(cur->death_flag_mutex);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philos_data	*cur;
	int				attempt_to_eat;

	cur = (t_philos_data *)arg;
	while (42)
	{
		if (!ck_death_flag_on(cur->death_flag_mutex, cur->death_flag))
			return (NULL);
		if (!ck_total_eat_value(cur->total_eat_mutex, &cur->input->total_eat))
			return (NULL);
		attempt_to_eat = eat_stage(cur);
		if (attempt_to_eat == FALSE)
			return (NULL);
		else if (attempt_to_eat == TRUE)
		{
			ft_sleep(cur);
			think(cur);
		}
	}
	return (NULL);
}
