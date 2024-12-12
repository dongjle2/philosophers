/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:01:14 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/12 20:15:07 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	eat_stage(t_philos_data *philo)
{
	if (ck_death_flag_on(philo->death_flag_mutex, philo->death_flag) == FALSE)
		return (FALSE);
	if (take_forks(philo) == FALSE)
		return (2);
	print_status(philo, EAT);
	ft_usleep(philo->input->tte);
	decrement_total_eat(philo->total_eat_mutex, &philo->input->total_eat);
	update_eat_time(philo);
	release_forks(philo);
	return (TRUE);
}

void	ft_sleep(t_philos_data *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->input->tts);
}

void	think(t_philos_data *philo)
{
	print_status(philo, THINK);
}
