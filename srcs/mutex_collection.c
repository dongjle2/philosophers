/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_collection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:36:10 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/12 20:15:11 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memmove(new_ptr, ptr, old_size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}

int	mutex_collection_add(t_mutex_collection *array, pthread_mutex_t *mutex)
{
	size_t			new_capacity;
	pthread_mutex_t	**new_mutexes;

	if (array->count == array->capacity)
	{
		new_capacity = array->capacity * 2;
		new_mutexes = ft_realloc(array->mutexes, \
							array->capacity * sizeof(pthread_mutex_t *), \
							new_capacity * sizeof(pthread_mutex_t *));
		if (new_mutexes == NULL)
		{
			printf("malloc failed\n");
			return (FALSE);
		}
		array->mutexes = new_mutexes;
		array->capacity = new_capacity;
	}
	array->mutexes[array->count++] = mutex;
	return (TRUE);
}

int	mutex_collection_destroy(t_mutex_collection *collection)
{
	size_t	i;

	i = 0;
	while (i < collection->count)
	{
		if (pthread_mutex_destroy(collection->mutexes[i]) != 0)
		{
			printf("Failed to destroy mutex at index %zu\n", i);
		}
		i++;
	}
	free(collection->mutexes);
	collection->mutexes = NULL;
	collection->count = 0;
	collection->capacity = 0;
	return (TRUE);
}
