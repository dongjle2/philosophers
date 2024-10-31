/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:23 by dongjle2          #+#    #+#             */
/*   Updated: 2024/10/31 23:57:43 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

//./philo [# of philo] [ttd] [tte] [tts] (# each philo eats)
int	main(int argc, char *argv[])
{
	t_resources rs;
	if (validate_user_input(argc, argv) == 0)
	{
		write(1, "Invalid input\n", 14);
		return (1);
	}
	parse_input(&rs.input, argv);
	mem_alloc(&rs);
	mutex_init(&rs);
	create_threads(&rs);
	int	i = 0;
	while (i < (int)rs.input.num_philos)
	{
		pthread_join(rs.thread[i], NULL);
		i++;
	}

	return (0);
}

void	*routine(void *arg)
{
	t_philos	*cur;

	cur = (t_philos *)arg;
	usleep(cur->num * 100);
	while (42)
	{
		eat(cur);
		ft_sleep(cur);
		think(cur);
	}
}

void	create_threads(t_resources *rs)
{
	size_t	i;

	i = 0;
	while (i < rs->input.num_philos)
	{
		rs->philos[i].num = i;
		rs->philos[i].forks[0] = rs->forks[i];
		rs->philos[i].forks[1] = rs->forks[(i + 1) % rs->input.num_philos];
		rs->philos[i].input = &rs->input;
		rs->philos[i].print = rs->print;
		pthread_create(&rs->thread[i], NULL, routine, &rs->philos[i]);
		i++;
	}
}

void	mutex_init(t_resources *rs)
{
	size_t	i;

	i = 0;
	// printf("%lu\n", num_philos);
	while (i < rs->input.num_philos)
	{
		pthread_mutex_init(&rs->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rs->print, NULL);
}

int	mem_alloc(t_resources *rs)
{
	rs->thread = malloc(rs->input.num_philos * sizeof(pthread_t));
	if (rs->philos == NULL)
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
		input->num_each_philo_eats = ft_atol(argv[5]);
	else
		input->num_each_philo_eats = 0;
	// printf("%lu\n", x->num_philos);
	// printf("%lu\n", x->tts);
}

long long	current_timestamp_in_milliseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}
