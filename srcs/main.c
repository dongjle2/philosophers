/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:23 by dongjle2          #+#    #+#             */
/*   Updated: 2024/10/30 01:35:44 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

//./philo [# of philo] [ttd] [tte] [tts] (# each philo eats)
int	main(int argc, char *argv[])
{
	t_input		x;
	t_resources rs;
	printf("%d\n", validate_user_input(argc, argv));
	parse_input(&x, argv);
	mem_alloc(&rs);
	

	return (0);
}

mutex_init(pthread_mutex_t *forks, long num_philos)
{
	long	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	mem_alloc(t_resources *rs, t_input x)
{
	rs->philos = malloc(x.num_philos * sizeof(pthread_t));
	rs->forks = malloc(x.num_philos * sizeof(pthread_mutex_t));
}

int	validate_input(int argc, char *argv[])
{
	return (validate_user_input(argc, argv) && validate_value_range(argv));
}

void	parse_input(t_input *x, char *argv[])
{
	x->num_philos = ft_atol(argv[1]);
	x->ttd = ft_atol(argv[2]);
	x->tte = ft_atol(argv[3]);
	x->tts = ft_atol(argv[4]);
	if (argv[5])
		x->num_each_philo_eats = ft_atol(argv[5]);
	else
		x->num_each_philo_eats = 0;
}