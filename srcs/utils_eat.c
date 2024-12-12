/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:05:06 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/12 15:59:21 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	take_forks_single_philo(t_philos_data *philo)
{
	pthread_mutex_lock(&philo->forks[0]);
	print_status(philo, FORK);
}

int	take_forks(t_philos_data *philo)
{
	int	l;
	int	r;

	l = philo->num;
	r = (philo->num + 1) % philo->input->num_philos;
	if (philo->num % 2 == 0)
	{
		ft_usleep(10);
		pthread_mutex_lock(&philo->forks[l]);
		pthread_mutex_lock(&philo->forks[r]);
		print_status(philo, FORK);
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[r]);
		print_status(philo, FORK);
		pthread_mutex_lock(&philo->forks[l]);
		print_status(philo, FORK);
	}
	return (TRUE);
}

void	update_eat_time(t_philos_data *philo)
{
	pthread_mutex_lock(philo->last_meal_time_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(philo->last_meal_time_mutex);
}

void	release_forks(t_philos_data *philo)
{
	int	l;
	int	r;

	l = philo->num;
	r = (philo->num + 1) % philo->input->num_philos;
	if (philo->num % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks[l]);
		pthread_mutex_unlock(&philo->forks[r]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[r]);
		pthread_mutex_unlock(&philo->forks[l]);
	}
}
