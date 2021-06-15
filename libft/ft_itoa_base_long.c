/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:30:46 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/01/13 15:04:04 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_number(long long int n, size_t size)
{
	size_t	i;

	if (n < 0)
	{
		i = 2;
		n = -n;
	}
	else
		i = 1;
	while (n / size > 0)
	{
		i++;
		n = n / size;
	}
	return (i);
}

char	*ft_itoa_llbase(long long int n, char *base)
{
	char	*res;
	size_t	len;
	size_t	size;
	size_t	i;

	size = ft_check_base(base);
	if (!size)
		return (NULL);
	len = len_number(n, size);
	res = ft_strnew(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		i = 1;
		res[0] = '-';
		n = -n;
	}
	while (len-- > i)
	{
		res[len] = base[n % size];
		n = n / size;
	}
	return (res);
}
