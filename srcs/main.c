/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:23 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/12 19:19:21 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

//./philo [# of philo] [ttd] [tte] [tts] (# each philo eats)
int	main(int argc, char *argv[])
{
	t_resources		rs;
	t_monitor_rs	monitor;

	if (validate_input(argc, argv) == FALSE)
	{
		write(1, "Invalid input\n", 14);
		return (1);
	}
	parse_input(&rs.input, argv);
	if (mem_alloc(&rs) == FALSE)
		return (1);
	if (mutex_init(&rs) == FALSE)
		return (1);
	if (create_threads(&rs, &monitor) == FALSE)
		return (1);
	if (join_threads(&rs, &monitor) == FALSE)
		return (1);
	ft_usleep(10);
	mutex_collection_destroy(&rs.mutex_collect);
	free_mem_alloc(&rs, 5);
	return (0);
}

int	validate_input(int argc, char *argv[])
{
	return (validate_user_input(argc, argv) \
			&& validate_value_range(argc, argv));
}

void	parse_input(t_input *input, char *argv[])
{
	input->num_philos = ft_atol(argv[1]);
	input->ttd = ft_atol(argv[2]);
	input->tte = ft_atol(argv[3]);
	input->tts = ft_atol(argv[4]);
	if (argv[5])
		input->total_eat = ft_atol(argv[5]) * input->num_philos;
	else
		input->total_eat = -1;
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + (tv.tv_usec) / 1000);
}
