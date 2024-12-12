/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:00:20 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/12 20:04:09 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# define FALSE 0
# define TRUE 1
# define INIT_CAPACITY 50
# define EAT		"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIE		"died"
# define FORK	"has taken a fork"

typedef struct s_input
{
	unsigned long	num_philos;
	long			ttd;
	unsigned long	tte;
	unsigned long	tts;
	long			total_eat;
}				t_input;

typedef struct s_philos_data
{
	size_t			num;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_input			*input;
	long			start_time;
	long			last_meal_time;
	int				*death_flag;
	pthread_mutex_t	*total_eat_mutex;
	pthread_mutex_t	*death_flag_mutex;
	pthread_mutex_t	*last_meal_time_mutex;
}				t_philos_data;

typedef struct s_monitor_rs
{
	t_philos_data	*philos_data;
	t_input			*input;
	pthread_t		monitor_thread;
	int				*death_flag;
	pthread_mutex_t	*death_flag_mutex;
}				t_monitor_rs;

typedef struct s_mutex_collection
{
	pthread_mutex_t	**mutexes;
	size_t			count;
	size_t			capacity;
}				t_mutex_collection;

typedef struct s_resources
{
	pthread_t			*thread;
	t_philos_data		*philos_data;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	t_input				input;
	int					death_flag;
	pthread_mutex_t		death_flag_mutex;
	pthread_mutex_t		total_eat_mutex;
	pthread_mutex_t		last_meal_time_mutex;
	t_mutex_collection	mutex_collect;
}				t_resources;

//validate_user_input.c
int				validate_user_input(int argc, char *argv[]);
int				validate_argc(int argc);
int				validate_each_argv(char *arg);
int				validate_argv(char *argv[]);
int				ft_isnum(char c);

//validate_value_range.c
int				validate_value_range(int argc, char *argv[]);
unsigned long	ft_atol(char *s);

void			parse_input(t_input *x, char *argv[]);
void			*routine(void *arg);
int				validate_input(int argc, char *argv[]);

//philo_state.c
int				eat_stage(t_philos_data *philo);
void			ft_sleep(t_philos_data *philo);
void			think(t_philos_data *philo);
void			print_status(t_philos_data *philo, const char *status);

//main.c
long			get_time_in_ms(void);
void			*single_philo_routine(void *arg);

//sleep.c
void			ft_usleep(long time_to_sleep);

//resources.c
int				mem_alloc(t_resources *rs);
void			free_mem_alloc(t_resources *rs, int i);
void			setup_philo_data(t_resources *rs, size_t i, long start_time);
void			init_monitor_thread_data(t_monitor_rs *monitor, \
				t_resources *rs);
int				mutex_init(t_resources *rs);
//utils_mutex.c
void			set_death_flag_on(pthread_mutex_t *death_flag_mutex, \
				int *death_flag);
int				ck_death_flag_on(pthread_mutex_t *death_flag_mutex, \
				int *death_flag);
int				ck_total_eat_value(pthread_mutex_t *total_eat_mutex, \
				long *total_eat);
void			decrement_total_eat(pthread_mutex_t *total_eat_mutex, \
				long *total_eat);
void			print_status(t_philos_data *philo, const char *status);

//utils_eat.c
int				take_forks(t_philos_data *philo);
void			take_forks_single_philo(t_philos_data *philo);
void			update_eat_time(t_philos_data *philo);
void			release_forks(t_philos_data *philo);

//utils_setup.c
void			setup_philo_data(t_resources *rs, size_t i, long start_time);
void			init_monitor_thread_data(t_monitor_rs *monitor, \
				t_resources *rs);

//utils2_mutex.c
int				mutex_init_lib_wrapper(pthread_mutex_t *mutex);
int				init_and_add_mutex(pthread_mutex_t *mutex, \
				t_mutex_collection *collect);
int				mutex_destroy(pthread_mutex_t *mutex_ref, size_t len);
int				mutex_init(t_resources *rs);

//pre_setup_thread_create.c
void			setup_single_philo(t_resources *rs, long start_time);
void			setup_multiple_philos(t_resources *rs, long start_time);

//thread_routines.c
void			*monitor_routine(void *arg);
void			*single_philo_routine(void *arg);
void			*routine(void *arg);

//manage_thread.c
int				create_threads(t_resources *rs, t_monitor_rs *monitor);
int				join_threads(t_resources *rs, t_monitor_rs *monitor);

//libft.c
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);

//mutex_collection.c
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int				mutex_collection_add(t_mutex_collection *array, \
				pthread_mutex_t *mutex);
int				mutex_collection_destroy(t_mutex_collection *collection);
#endif