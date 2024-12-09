/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:22:29 by dongjle2          #+#    #+#             */
/*   Updated: 2024/11/13 23:39:45 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philisophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (mem);
	ft_bzero(mem, count * size);
	return (mem);
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (pdst < psrc)
	{
		while (len--)
			*pdst++ = *psrc++;
	}
	else if (psrc < pdst)
	{
		while (len--)
			pdst[len] = psrc[len];
	}
	return (dst);
}
