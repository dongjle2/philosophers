/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:01:36 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/09 22:10:09 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	set_death_flag_on(pthread_mutex_t *death_flag_mutex, int *death_flag)
{
	pthread_mutex_lock(death_flag_mutex);
	*death_flag = 1;
	pthread_mutex_unlock(death_flag_mutex);
}

int	ck_death_flag_on(pthread_mutex_t *death_flag_mutex, int *death_flag)
{
	pthread_mutex_lock(death_flag_mutex);
	if (*death_flag)
	{
		pthread_mutex_unlock(death_flag_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(death_flag_mutex);
	return (TRUE);
}

int	ck_total_eat_value(pthread_mutex_t *total_eat_mutex, long *total_eat)
{
	pthread_mutex_lock(total_eat_mutex);
	if (*total_eat != -1 && *total_eat == 0)
	{
		pthread_mutex_unlock(total_eat_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(total_eat_mutex);
	return (TRUE);
}

void	decrement_total_eat(pthread_mutex_t *total_eat_mutex, long *total_eat)
{
	pthread_mutex_lock(total_eat_mutex);
	if (*total_eat > 0)
	{
		(*total_eat)--;
	}
	pthread_mutex_unlock(total_eat_mutex);
}

void	print_status(t_philos *philo, const char *status)
{
	pthread_mutex_lock(philo->death_flag_mutex);
	if (*philo->death_flag == 0)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %zu %s\n", get_time_in_ms() - philo->start_time, philo->num, status);
		pthread_mutex_unlock(&philo->print);
	}
	pthread_mutex_unlock(philo->death_flag_mutex);
}
