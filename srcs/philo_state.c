/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:01:14 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/11 17:25:46 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

// int	pre_eat(t_philos *philo)
// {
// 	if (ck_death_flag_on(philo->death_flag_mutex, philo->death_flag) == FALSE)
// 		return (FALSE);

// }

int	eat_stage(t_philos *philo)
{
	if (ck_death_flag_on(philo->death_flag_mutex, philo->death_flag) == FALSE)
		return (FALSE);
	take_forks(philo);
	print_status(philo, EAT);
	ft_usleep(philo->input->tte);
	decrement_total_eat(philo->death_flag_mutex, &philo->input->total_eat);
	update_eat_time(philo);
	release_forks(philo);
	return (TRUE);
}

void	ft_sleep(t_philos *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->input->tts);
}

void	think(t_philos *philo)
{
	print_status(philo, THINK);
}
