/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:32:32 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:32:34 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_number(int n)
{
	size_t			i;
	unsigned int	nb;

	i = 1;
	if (n < 0)
	{
		i++;
		nb = -n;
	}
	else
		nb = n;
	while (nb / 10 > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*res;
	size_t			len;
	unsigned int	nb;
	size_t			i;

	len = len_number(n);
	i = 0;
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		nb = -n;
		i = 1;
	}
	else
		nb = n;
	while (len-- > i)
	{
		res[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (res);
}
