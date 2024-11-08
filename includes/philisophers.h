/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:20 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/08 01:05:55 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define False 0
#define True 1

typedef struct	s_input
{
	unsigned long	num_philos;
	unsigned long	ttd;
	unsigned long	tte;
	unsigned long	tts;
	int				total_eat;
}				t_input;

typedef struct	s_philos
{
	size_t			num;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	print;
	t_input			*input;
	long			start_time;
	long			last_meal_time;
	int				*death_flag;
	pthread_mutex_t	*total_eat_mutex;
	pthread_mutex_t	*death_flag_mutex;
}				t_philos;

typedef struct s_monitor_rs
{
	t_philos		*philos;
	t_input			*input;
	pthread_t		monitor_thread;
	int				*death_flag;
	pthread_mutex_t	*death_flag_mutex;
}				t_monitor_rs;

typedef struct	s_resources
{
	pthread_t		*thread;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_input			input;
	int				death_flag;
	pthread_mutex_t	death_flag_mutex;
	pthread_mutex_t	total_eat_mutex;
}				t_resources;


//validate_user_input.c
int		validate_user_input(int argc, char *argv[]);
int		validate_argc(int argc);
int		validate_each_argv(char *arg);
int		validate_argv(char *argv[]);
int		ft_isnum(char c);

//validate_value_range.c
int		validate_value_range(char *argv[]);
unsigned long	ft_atol(char *s);

void	mutex_init(t_resources *rs);
int		mem_alloc(t_resources *rs);
void	parse_input(t_input *x, char *argv[]);
void	*routine(void *arg);
void	create_threads(t_resources *rs, t_monitor_rs *monitor);
int		validate_input(int argc, char *argv[]);

//philo_state.c
void 	(*print_log)(void);
int		eat(t_philos *philo);
void	ft_sleep(t_philos *philo);
void	think(t_philos *philo);
void	print_status(t_philos *philo, const char *status);
void	decrement_total_eat(t_philos *philo);
//main.c
long	get_time_in_ms();

//sleep.c
void	ft_usleep(long time_to_sleep);