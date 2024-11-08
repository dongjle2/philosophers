/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:08:49 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/08 00:57:35 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	ft_usleep(long time_to_sleep)
{
	long	start_time;
	
	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time_to_sleep)
	{
		usleep(300);
	}
}