/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_value_range.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:42:14 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/09 22:13:22 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

unsigned long	ft_atol(char *s)
{
	long	ret;

	ret = 0;
	while (*s)
	{
		ret = ret * 10 + (*s - '0');
		s++;
	}
	return (ret);
}

int	validate_value_range(char *argv[])
{
	long	input[5];
	int		num_input;
	int		i;

	i = 0;
	if (argv[5])
		num_input = 4;
	else
		num_input = 5;
	while (i < num_input)
	{
		input[i] = atol(argv[i + 1]);
		if (input[i] < 2 || INT32_MAX < input[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
