/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_value_range.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:42:14 by dongjle2          #+#    #+#             */
/*   Updated: 2024/12/12 20:15:25 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	ft_atol(char *s)
{
	unsigned long	ret;

	ret = 0;
	while (*s)
	{
		ret = ret * 10 + (*s - '0');
		s++;
	}
	return (ret);
}

int	validate_value_range(int argc, char *argv[])
{
	long	input[5];
	int		i;

	i = 0;
	while (i < argc && argv[i + 1])
	{
		input[i] = ft_atol(argv[i + 1]);
		if (input[i] < 1 || INT32_MAX < input[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
