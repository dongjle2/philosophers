/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:04:20 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/15 00:10:43 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

int	mutex_init_lib_wrapper(pthread_mutex_t *mutex)
{
	int	ret_val;

	ret_val = pthread_mutex_init(mutex, NULL);
	if (ret_val != 0)
	{
		printf("pthread_mutex_init failed\n");
		return (FALSE);
	}
	return (TRUE);
}

int	init_and_add_mutex(pthread_mutex_t *mutex, t_mutex_collection *collect)
{
	int	ret_init;
	int	ret_add;

	ret_init = mutex_init_lib_wrapper(mutex);
	if (ret_init == FALSE)
	{
		mutex_collection_destroy(collect);
		return (FALSE);
	}
	ret_add = mutex_collection_add(collect, mutex);
	if (ret_add == FALSE)
		return (FALSE);
	return (TRUE);
}

int	mutex_destroy(pthread_mutex_t *mutex_ref, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (pthread_mutex_destroy(&mutex_ref[i]) != 0)
		{
			printf("mutex locked but try to destroy\n");
		}
		i++;
	}
	return (TRUE);
}

int	mutex_init(t_resources *rs)
{
	size_t	i;
	int		ret_init_and_add;

	i = 0;
	while (i < rs->input.num_philos)
	{
		ret_init_and_add = init_and_add_mutex(&rs->forks[i], \
											&rs->mutex_collect);
		if (ret_init_and_add == FALSE)
			return (FALSE);
		i++;
	}
	if (init_and_add_mutex(&rs->print, &rs->mutex_collect) == FALSE)
		return (FALSE);
	if (init_and_add_mutex(&rs->total_eat_mutex, &rs->mutex_collect) == FALSE)
		return (FALSE);
	if (init_and_add_mutex(&rs->death_flag_mutex, &rs->mutex_collect) == FALSE)
		return (FALSE);
	return (TRUE);
}
