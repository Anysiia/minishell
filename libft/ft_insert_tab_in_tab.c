/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_tab_in_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:29:20 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:29:23 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**cat_tab(char **dst, char **src, int len)
{
	char	**new;
	int		i;
	int		j;

	new = (char **)malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (dst[++i])
		new[i] = ft_strdup(dst[i]);
	j = -1;
	while (src[++j])
		new[i + j] = ft_strdup(src[j]);
	new[i + j] = NULL;
	return (new);
}

static char	**insert_tab(char **dst, char **src, int pos, int len)
{
	int		i;
	int		j;
	char	**new;

	new = (char **)malloc(sizeof(*new) * (len));
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
		new[i + j] = ft_strdup(dst[i]);
		i++;
	}
	new[i + j] = NULL;
	return (new);
}

char	**ft_insert_tab_in_tab(char **dest, char **src, int pos)
{
	int		len;

	len = ft_len_tab(dest) + ft_len_tab(src);
	if (pos > (int)ft_len_tab(dest))
		return (dest);
	else if (pos == (int)ft_len_tab(dest))
		return (cat_tab(dest, src, len));
	else
		return (insert_tab(dest, src, pos, len));
}
