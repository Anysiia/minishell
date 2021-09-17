/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_weak_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:08:18 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/17 17:45:52 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_variable_len(t_expand *tmp, const char *arg)
{
	int	len;

	len = 0;
	while (arg[tmp->j + len] && (arg[tmp->j + len] != '$'
		&& arg[tmp->j + len] != WEAK_QUOTE
		&& arg[tmp->j + len] != STRONG_QUOTE && arg[tmp->j + len] != ' '))
		len++;
	return (len);
}

char	*get_variable_content(t_expand *tmp, const char *arg, char **env)
{
	char	*name;
	int		len;
	int		ret;
	int		i;
	int		index;

	len = get_variable_len(tmp, arg);
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
	ft_putendl(name);
	index = find_variable_index(env, name);
	ft_freestr(&name);
	if (index < 0)
		return (NULL);
	ret = find_variable_value(&name, env[index]);
	return (name);
}

int		add_variable_content(t_expand *tmp, const char *arg, char **env)
{
	char	*content;
	int		len_content;
	int		len_str;

	tmp->j++;
	content = get_variable_content(tmp, arg, env);
	if (!content)
		return (0);
	len_content = ft_strlen(content);
	len_str = ft_strlen(tmp->str);
	if (len_content + len_str == ARG_LEN * tmp->len
		&& up_expand_buffer(tmp, len_content + len_str + 1) == RET_ERROR)
		return (RET_ERROR);
	ft_strlcat(tmp->str, content, ARG_LEN * tmp->len);
	ft_freestr(&content);
	return (len_content);
}


char	*expand_weak_quote(t_expand *tmp, const char *arg, char **env)
{
	int variable_len;

	tmp->j++;
	while (arg[tmp->j] && arg[tmp->j] != WEAK_QUOTE)
	{
		if (arg[tmp->j] == '$')
			variable_len = add_variable_content(tmp, arg, env);
		else
			cat_c_to_str(tmp, arg[tmp->j]);
		tmp->j++;
	}
	return (tmp->str);
}
