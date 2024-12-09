/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:28:40 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/09 03:18:39 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

int	mem_alloc(t_resources *rs)
{
	rs->thread = ft_calloc(rs->input.num_philos + 1, sizeof(pthread_t));
	if (rs->thread == NULL)
		return (FALSE);
	rs->philos_data = ft_calloc(\
							rs->input.num_philos + 1, sizeof(t_philos_data));
	if (rs->philos_data == NULL)
	{
		free_mem_alloc(rs, 1);
		return (FALSE);
	}
	rs->forks = ft_calloc(rs->input.num_philos + 1, sizeof(pthread_mutex_t));
	if (rs->forks == NULL)
	{
		free_mem_alloc(rs, 2);
		return (FALSE);
	}
	rs->mutex_collect.mutexes = ft_calloc(INIT_CAPACITY, \
											sizeof(pthread_mutex_t *));
	if (rs->mutex_collect.mutexes == NULL)
	{
		return (free_mem_alloc(rs, 3), FALSE);
	}
	rs->mutex_collect.count = 0;
	rs->mutex_collect.capacity = INIT_CAPACITY;
	return (TRUE);
}

void	free_mem_alloc(t_resources *rs, int i)
{
	if (3 <= i)
		free(rs->mutex_collect.mutexes);
	if (2 <= i)
		free(rs->forks);
	if (1 <= i)
		free(rs->philos_data);
	if (0 <= i)
		free(rs->thread);
}
