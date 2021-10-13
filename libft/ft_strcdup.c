/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:38:01 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:38:04 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *str, char c)
{
	char	*dup;
	int		len;
	int		i;

	if (!str)
		return (ft_strnew(1));
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	dup = (char *)malloc(sizeof(*dup) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
