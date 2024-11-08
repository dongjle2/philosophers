/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:01:14 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/08 01:00:17 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

/*
int	eat(t_philos *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->forks[1]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	ft_usleep(philo->input->tte);
	if (decrement_total_eat(philo) == False)
		return(False);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	return (True);
}
*/

void	take_forks(t_philos *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->forks[0]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->forks[1]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->forks[1]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->forks[0]);
		print_status(philo, "has taken a fork");
	}
}
int	eat(t_philos *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	ft_usleep(philo->input->tte);
	decrement_total_eat(philo);
	//update_eat_time();
	philo->last_meal_time = get_time_in_ms() - philo->last_meal_time;
	printf("%lu\n", philo->last_meal_time);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	return (True);
}

void	decrement_total_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->total_eat_mutex);
	if (philo->input->total_eat > 0)
	{
		philo->input->total_eat--;
		// printf("Remaining meals: %d\n", philo->input->total_eat);
	}
	pthread_mutex_unlock(philo->total_eat_mutex);
}

void	ft_sleep(t_philos *philo)
{
	// printf("%lu begin sleep\n", philo->num);
	print_status(philo, "is sleeping");
	// printf("asdf\n");
	ft_usleep(philo->input->tts);
	// printf("asdf\n");
}

void	think(t_philos *philo)
{
	// printf("%lu begin think\n", philo->num);
	print_status(philo, "is thinking");
	// ft_usleep(philo->input->tts * 1000);
}

void	print_status(t_philos *philo, const char *status)
{
	pthread_mutex_lock(&philo->print);
	printf("%lu %zu %s\n", get_time_in_ms() - philo->start_time, philo->num, status);
	pthread_mutex_unlock(&philo->print);
}
