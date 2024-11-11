/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_user_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:17:41 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/11 20:32:19 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

int	validate_user_input(int argc, char *argv[])
{
	return (validate_argc(argc) && validate_argv(argv));
}

int	validate_argc(int argc)
{
	if (argc < 5 || 6 < argc)
		return (FALSE);
	return (TRUE);
}

int	validate_each_argv(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isnum(arg[i]))
			return FALSE;
		i++;
	}
	return (TRUE);
}

int	validate_argv(char *argv[])
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (validate_each_argv(argv[i]))
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

int	ft_isnum(char c)
{
	if ('0' <= c && c <= '9')
		return (TRUE);
	return (FALSE);
}
