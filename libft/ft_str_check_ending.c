/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_check_ending.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:37:50 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:37:53 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_check_ending(const char *file, const char *type)
{
	int		len_file;
	int		len_type;
	int		i;
	int		j;

	if (!file || !type)
		return (0);
	len_file = ft_strlen(file);
	len_type = ft_strlen(type);
	if (len_file <= len_type)
		return (0);
	i = len_file - len_type;
	j = 0;
	while (file[i] && j < len_type)
		if (file[i++] != type[j++])
			return (0);
	return (1);
}
