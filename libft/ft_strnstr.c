/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:40:33 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:40:36 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *s, size_t len)
{
	size_t	i;
	size_t	j;

	if (s[0] == '\0')
		return ((char *)&str[0]);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == s[j] && (i + j < len))
		{
			if (s[j + 1] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
