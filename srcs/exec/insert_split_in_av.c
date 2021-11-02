/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_split_in_av.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:21:40 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/02 17:21:43 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**check_fail(char **new, int len_tab)
{
	int		i;
	bool	to_free;

	i = 0;
	to_free = false;
	while (i < len_tab - 1)
	{
		if (!new[i])
			to_free = true;
		i++;
	}
	if (to_free == true)
	{
		i = 0;
		while (i < len_tab - 1)
		{
			ft_freestr(&new[i]);
			i++;
		}
		new = ft_free_tab(new);
	}
	return (new);
}

char	**insert_split_in_av(char **av, char **split, int index)
{
	char	**new;
	int		len_tab;
	int		i;
	int		j;

	if (!av || !split || index > (int)ft_len_tab(av))
		return (NULL);
	len_tab = ft_len_tab(av) + ft_len_tab(split);
	new = (char **)malloc(sizeof(*new) * len_tab);
	if (!new)
		return (NULL);
	new[len_tab - 1] = NULL;
	i = -1;
	j = 0;
	while (++i < index && av[i])
		new[i] = ft_strdup(av[i]);
	--i;
	while (++j && split[j])
		new[i + j] = ft_strdup(split[j]);
	--j;
	while (++i && av[i])
		new[i + j] = ft_strdup(av[i]);
	return (check_fail(new, len_tab));
}
