/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_line_in_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:03:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/07/20 15:15:45 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_remove_line_on_tab(char **tabl, int index)
{
	int		len;
	char	**new;
	int		i;

	len = ft_len_tab(tabl);
	if (len < 2 || index > len - 1 || index < 0)
	{
		ft_free_tab(tabl);
		return (NULL);
	}
	new = (char **)malloc(sizeof(*new) * len);
	if (!new)
		return (NULL);
	i = 0;
	while (tabl && tabl[i])
	{
		if (i < index)
			new[i] = ft_strdup(tabl[i]);
		else
			new[i - 1] = ft_strdup(tabl[i]);
		i++;
	}
	tabl[i] = NULL;
	ft_free_tab(tabl);
	return (new);
}
