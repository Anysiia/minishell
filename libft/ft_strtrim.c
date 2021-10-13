/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:41:01 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:41:04 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		len;
	int		i;
	int		size;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = len - 1;
	while (i >= 0 && (ft_test_set(s1[i], set)))
	{
		len--;
		i--;
	}
	i = 0;
	while (s1[i] && (ft_test_set(s1[i], set)))
		i++;
	if (i > len)
		size = 0;
	else
		size = len - i;
	s2 = ft_substr(s1, i, size);
	return (s2);
}
