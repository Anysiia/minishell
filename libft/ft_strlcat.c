/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:47:09 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/14 16:13:22 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[i] && i < dstsize)
		i++;
	j = i;
	while (src[i - j] && i < dstsize - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	if (j < dstsize)
		dst[i] = '\0';
	return (j + ft_strlen(src));
}

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(dst);
	while (i < n && src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (dst);
}
