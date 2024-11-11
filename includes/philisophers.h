/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:20 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/11 20:49:00 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

#define EAT		"is eating"
#define SLEEP	"is sleeping"
#define THINK	"is thinking"
#define DIE		"is died"
#define FORK	"has taken a fork"

typedef struct	s_input
{
	unsigned long	num_philos;
	long			ttd;
	unsigned long	tte;
	unsigned long	tts;
	long			total_eat;
}				t_input;

typedef struct	s_philos_data
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
}				t_philos_data;

typedef struct s_monitor_rs
{
	t_philos_data	*philos;
	t_input			*input;
	pthread_t		monitor_thread;
	int				*death_flag;
	pthread_mutex_t	*death_flag_mutex;
}				t_monitor_rs;

typedef struct	s_resources
{
	pthread_t		*thread;
	t_philos_data	*philos;
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
int				validate_value_range(int argc, char *argv[]);
unsigned long	ft_atol(char *s);

void	parse_input(t_input *x, char *argv[]);
void	*routine(void *arg);
void	create_threads(t_resources *rs, t_monitor_rs *monitor);
int		validate_input(int argc, char *argv[]);

//philo_state.c
int		eat_stage(t_philos_data *philo);
void	ft_sleep(t_philos_data *philo);
void	think(t_philos_data *philo);
void	print_status(t_philos_data *philo, const char *status);

//main.c
long	get_time_in_ms();

//sleep.c
void	ft_usleep(long time_to_sleep);

//resources.c
int		mem_alloc(t_resources *rs);
void	free_mem_alloc(t_resources *rs);
void	init_philo_data(t_resources *rs, size_t i, long start_time);
void	init_monitor_thread_data(t_monitor_rs *monitor, t_resources *rs);
void	mutex_init(t_resources *rs);

//utils_mutex.c
void	set_death_flag_on(pthread_mutex_t *death_flag_mutex, int *death_flag);
int		ck_death_flag_on(pthread_mutex_t *death_flag_mutex, int *death_flag);
int		ck_total_eat_value(pthread_mutex_t *total_eat_mutex, long *total_eat);
void	decrement_total_eat(pthread_mutex_t *total_eat_mutex, long *total_eat);
void	print_status(t_philos_data *philo, const char *status);

//utils_eat.c
void	take_forks(t_philos_data *philo);
void	take_forks_single_philo(t_philos_data *philo);
void	update_eat_time(t_philos_data *philo);
void	release_forks(t_philos_data *philo);
void	release_forks_single_philo(t_philos_data *philo);
