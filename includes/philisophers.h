/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:20 by dongjle2          #+#    #+#             */
/*   Updated: 2024/10/30 01:30:06 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define False 0
#define True 1

typedef struct s_input
{
	long	num_philos;
	long	ttd;
	long	tte;
	long	tts;
	long	num_each_philo_eats;
}				t_input;

typedef struct s_resources
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}				t_resources;

//validate_user_input.c
int		validate_user_input(int argc, char *argv[]);
int		validate_argc(int argc);
int		validate_each_argv(char *arg);
int		validate_argv(char *argv[]);
int		ft_isnum(char c);

//validate_value_range.c
int		validate_value_range(char *argv[]);
long	ft_atol(char *s);