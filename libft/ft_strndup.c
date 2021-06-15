/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:33:26 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/01/13 14:43:48 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	size_t	i;
	char	*s2;

	i = 0;
	if (!s1)
		return (NULL);
	s2 = (char *)malloc(sizeof(*s2) * (size + 1));
	if (!s2)
		return (NULL);
	while (s1[i] && i < size)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
