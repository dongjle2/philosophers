/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:28:40 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/11 20:52:11 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

int	mem_alloc(t_resources *rs)
{
	rs->thread = malloc(rs->input.num_philos * sizeof(pthread_t));
	if (rs->thread == NULL)
		return (FALSE);
	rs->philos = malloc(rs->input.num_philos * sizeof(t_philos_data));
	if (rs->philos == NULL)
		return (FALSE);
	rs->forks = malloc(rs->input.num_philos * sizeof(pthread_mutex_t));
	if (rs->forks == NULL)
		return (FALSE);
	return (TRUE);
}

void	free_mem_alloc(t_resources *rs)
{
	free(rs->thread);
	free(rs->philos);
	free(rs->forks);
}

void	init_philo_data(t_resources *rs, size_t i, long start_time)
{
	rs->philos[i].num = i;
	rs->philos[i].input = &rs->input;
	rs->philos[i].print = rs->print;
	rs->philos[i].start_time = start_time;
	rs->philos[i].last_meal_time = start_time;
	rs->philos[i].total_eat_mutex = &rs->total_eat_mutex;
	rs->philos[i].death_flag = &rs->death_flag;
	rs->philos[i].death_flag_mutex = &rs->death_flag_mutex;
}

void	init_monitor_thread_data(t_monitor_rs *monitor, t_resources *rs)
{
	monitor->death_flag = &rs->death_flag;
	monitor->death_flag_mutex = &rs->death_flag_mutex;
	monitor->input = &rs->input;
	monitor->philos = rs->philos;
}

void	mutex_init(t_resources *rs)
{
	size_t	i;

	i = 0;
	while (i < rs->input.num_philos)
	{
		pthread_mutex_init(&rs->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rs->print, NULL);
	pthread_mutex_init(&rs->total_eat_mutex, NULL);
	pthread_mutex_init(&rs->death_flag_mutex, NULL);
}
