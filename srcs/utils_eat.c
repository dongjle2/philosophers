/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:05:06 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/08 22:05:22 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	take_forks_single_philo(t_philos *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	print_status(philo, FORK);
}

void	take_forks(t_philos *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->forks[0]);
		print_status(philo, FORK);
		pthread_mutex_lock(philo->forks[1]);
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->forks[1]);
		print_status(philo, FORK);
		pthread_mutex_lock(philo->forks[0]);
		print_status(philo, FORK);
	}
}

void	update_eat_time(t_philos *philo)
{
	philo->last_meal_time = get_time_in_ms();
}

void	release_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}