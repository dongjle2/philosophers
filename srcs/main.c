/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:23 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/08 01:03:20 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

//./philo [# of philo] [ttd] [tte] [tts] (# each philo eats)
int	main(int argc, char *argv[])
{
	t_resources rs;
	t_monitor_rs monitor;

	if (validate_user_input(argc, argv) == 0)
	{
		write(1, "Invalid input\n", 14);
		return (1);
	}
	parse_input(&rs.input, argv);
	mem_alloc(&rs);

	mutex_init(&rs);
	create_threads(&rs, &monitor);
	int	i = 0;
	while (i < (int)rs.input.num_philos)
	{
		pthread_join(rs.thread[i], NULL);
		i++;
	}
	pthread_join(monitor.monitor_thread, NULL);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_monitor_rs	*monitor;
	size_t		i;

	monitor = (t_monitor_rs *)arg;
	while (42)
	{
		// printf("monitor_rountine\n");
		pthread_mutex_lock(monitor->death_flag_mutex);
		if (*monitor->death_flag)
		{
			pthread_mutex_unlock(monitor->death_flag_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(monitor->death_flag_mutex);
		exit(1);
		i = 0;
		printf("%lu\n", monitor->input->num_philos);
		while (i < monitor->input->num_philos)
		{
			if ((long)monitor->input->ttd > get_time_in_ms() - monitor->philos[i].last_meal_time)
			{
				print_status(&monitor->philos[i], "is died");
				pthread_mutex_lock(monitor->death_flag_mutex);
				*monitor->death_flag = 1;
				pthread_mutex_unlock(monitor->death_flag_mutex);
				return (NULL);
			}
			i++;
		}
	}
}

void	*routine(void *arg)
{
	t_philos	*cur;

	cur = (t_philos *)arg;
	// usleep(cur->num * 1000);
	while (42)
	{
		pthread_mutex_lock(cur->death_flag_mutex);
		if (*cur->death_flag)
		{
			pthread_mutex_unlock(cur->death_flag_mutex);
			return (NULL);
		}
		// printf("routine\n");
		pthread_mutex_unlock(cur->death_flag_mutex);
		
		pthread_mutex_lock(cur->total_eat_mutex);
		if (cur->input->total_eat != -1 && cur->input->total_eat == 0)
		{
			pthread_mutex_unlock(cur->total_eat_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(cur->total_eat_mutex);
		if (eat(cur) == False)
			return (NULL);
		ft_sleep(cur);
		think(cur);
	}
}
/*
void	init_philo_data(t_philos *philos, size_t i)
{
	*(philos->total_eat) = 0;
	philos->start_time = get_time_in_ms();
}
*/

void	create_threads(t_resources *rs, t_monitor_rs *monitor)
{
	size_t	i;
	long	start_time;
	
	i = 0;
	start_time = get_time_in_ms();
	rs->death_flag = 0;
	while (i < rs->input.num_philos)
	{
		usleep(10);
		rs->philos[i].num = i;
		rs->philos[i].forks[1] = &rs->forks[i];
		rs->philos[i].forks[0] = &rs->forks[(i + 1) % rs->input.num_philos];
		rs->philos[i].input = &rs->input;
		rs->philos[i].print = rs->print;
		rs->philos[i].start_time = start_time;
		rs->philos[i].last_meal_time = start_time;
		rs->philos[i].total_eat_mutex = &rs->total_eat_mutex;
		rs->philos[i].death_flag = &rs->death_flag;
		rs->philos[i].death_flag_mutex = &rs->death_flag_mutex;
		pthread_create(&rs->thread[i], NULL, routine, &rs->philos[i]);
		i++;
	}
	pthread_create(&monitor->monitor_thread, NULL, monitor_routine, monitor);

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

int	mem_alloc(t_resources *rs)
{
	rs->thread = malloc(rs->input.num_philos * sizeof(pthread_t));
	if (rs->thread == NULL)
		return (False);
	rs->philos = malloc(rs->input.num_philos * sizeof(t_philos));
	if (rs->philos == NULL)
		return (False);
	rs->forks = malloc(rs->input.num_philos * sizeof(pthread_mutex_t));
	if (rs->forks == NULL)
		return (False);
	return (True);
}

int	validate_input(int argc, char *argv[])
{
	return (validate_user_input(argc, argv) && validate_value_range(argv));
}

void	parse_input(t_input *input, char *argv[])
{
	input->num_philos = ft_atol(argv[1]);
	input->ttd = ft_atol(argv[2]);
	input->tte = ft_atol(argv[3]);
	input->tts = ft_atol(argv[4]);
	if (argv[5])
		input->total_eat = ft_atol(argv[5]);
	else
		input->total_eat = -1;
}

long	get_time_in_ms()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}
