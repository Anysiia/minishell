/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:40:14 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:40:17 by cmorel-a         ###   ########.fr       */
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
