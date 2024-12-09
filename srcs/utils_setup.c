/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:02:19 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/17 01:29:53 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	setup_philo_data(t_resources *rs, size_t i, long start_time)
{
	rs->philos_data[i].num = i;
	rs->philos_data[i].input = &rs->input;
	rs->philos_data[i].print = rs->print;
	rs->philos_data[i].start_time = start_time;
	rs->philos_data[i].last_meal_time = start_time;
	rs->philos_data[i].total_eat_mutex = &rs->total_eat_mutex;
	rs->philos_data[i].death_flag = &rs->death_flag;
	rs->philos_data[i].death_flag_mutex = &rs->death_flag_mutex;
}

void	init_monitor_thread_data(t_monitor_rs *monitor, t_resources *rs)
{
	monitor->death_flag = &rs->death_flag;
	monitor->death_flag_mutex = &rs->death_flag_mutex;
	monitor->input = &rs->input;
	monitor->philos_data = rs->philos_data;
}
