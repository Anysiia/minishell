/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_tab_in_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:03:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/07/20 15:10:33 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_insert_tab_in_tab(char **dest, char **src, int pos)
{
	int		len;
	char	**new;
	int		i;
	int		j;

	len = ft_len_tab(dest) + ft_len_tab(src);
	if (pos > (int)ft_len_tab(dest))
		return (NULL);
	new = (char **)malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i + j < len)
	{
		while (i == pos && j < (int)ft_len_tab(src))
		{
			new[i + j] = ft_strdup(src[j]);
			j++;
		}
		new[i + j] = ft_strdup(dest[i]);
		i++;
	}
	new[i + j] = NULL;
	return (new);
}
