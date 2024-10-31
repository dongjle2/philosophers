/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:01:14 by dongjle2          #+#    #+#             */
/*   Updated: 2024/10/31 23:30:29 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->forks[0]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->forks[1]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	usleep(philo->input->tte * 1000);
	pthread_mutex_unlock(&philo->forks[0]);
	pthread_mutex_unlock(&philo->forks[1]);
}

void	ft_sleep(t_philos *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->input->tts * 1000);
}

void	think(t_philos *philo)
{
	print_status(philo, "is thinking");
	usleep(philo->input->tts * 1000);
}

void	print_status(t_philos *philo, const char *status)
{
	pthread_mutex_lock(&philo->print);
	printf("%lld %zu %s\n", current_timestamp_in_milliseconds(), philo->num, status);
	pthread_mutex_unlock(&philo->print);
}
