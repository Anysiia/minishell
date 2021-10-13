/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:18 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:35:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	const char	*ls;
	char		*ld;

	if (!dst && !src)
		return (dst);
	d = (char *)dst;
	s = src;
	ls = s + (len - 1);
	ld = d + (len - 1);
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
		while (len--)
			*ld-- = *ls--;
	return (dst);
}
