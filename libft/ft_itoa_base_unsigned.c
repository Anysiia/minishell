/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:32:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:32:55 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_number(unsigned int n, size_t size)
{
	size_t	i;

	i = 1;
	while (n / size > 0)
	{
		i++;
		n = n / size;
	}
	return (i);
}

char	*ft_itoa_ubase(unsigned int n, char *base)
{
	char	*res;
	size_t	len;
	size_t	size;

	size = ft_check_base(base);
	if (!size)
		return (0);
	len = len_number(n, size);
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len-- > 0)
	{
		res[len] = base[n % size];
		n = n / size;
	}
	return (res);
}
