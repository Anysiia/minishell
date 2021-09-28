/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:44:32 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/28 11:36:43 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_variable_name(t_expand *tmp, const char *arg)
{
	int		len;
	int		i;
	char	*name;

	len = 0;
	while (arg[tmp->j + len]
		&& (ft_isalnum(arg[tmp->j + len]) || arg[tmp->j + len] == '_'))
		len++;
	if (len < 1 || ft_isdigit(arg[tmp->j]))
		return (NULL);
	name = ft_strnew(len + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = arg[tmp->j];
		i++;
		tmp->j++;
	}
	tmp->j--;
	return (name);
}

char	*get_variable_content(t_expand *tmp, const char *arg, char **env)
{
	char	*name;
	char	*content;
	int		ret;
	int		index;

	name = get_variable_name(tmp, arg);
	if (!name)
		return (NULL);
	index = find_variable_index(env, name);
	ft_freestr(&name);
	if (index < 0)
		return (NULL);
	ret = find_variable_value(&content, env[index]);
	return (content);
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
	return (new);
}
