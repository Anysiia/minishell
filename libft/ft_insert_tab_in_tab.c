/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_tab_in_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:03:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/22 17:07:29 by cmorel-a         ###   ########.fr       */
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
	j = 0;
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

	new = (char **)malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 1;
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
