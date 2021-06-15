/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:16:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/03/22 15:25:15 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	check_overflow(long int init, int to_add, int sign)
{
	if (init > OVF_LONG)
	{
		errno = ERANGE;
		if (sign == 1)
			return (LONG_MAX);
		if (sign == -1)
			return (LONG_MIN);
	}
	if (init == OVF_LONG)
	{
		if (sign == 1 && to_add > 7)
		{
			errno = ERANGE;
			return (LONG_MAX);
		}
		if (sign == -1 && to_add > 8)
		{
			errno = ERANGE;
			return (LONG_MIN);
		}
	}
	return (-1);
}

long int	ft_atol(const char *str)
{
	long int	tmp;
	int			sign;
	long int	overflow;

	tmp = 0;
	sign = 1;
	overflow = -1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (tmp >= OVF_LONG)
			overflow = check_overflow(tmp, *str - 48, sign);
		if (overflow != -1)
			return (overflow);
		tmp = tmp * 10 + (*str - 48);
		str++;
	}
	return (tmp * sign);
}
