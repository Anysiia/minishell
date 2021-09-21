/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:44:32 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/21 12:51:37 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_variable_name(t_expand *tmp, const char *arg)
{
	int		len;
	int		i;
	char	*name;

	len = 0;
	while (arg[tmp->j + len] && ft_isalnum(arg[tmp->j + len]))
		len++;
	if (len < 1)
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

int	add_variable_content(t_expand *tmp, const char *arg, char **env)
{
	char	*content;
	int		len_content;
	int		len_str;

	tmp->j++;
	content = get_variable_content(tmp, arg, env);
	if (!content)
		return (NOT_FOUND);
	len_content = ft_strlen(content);
	len_str = ft_strlen(tmp->str);
	if (len_content + len_str >= ARG_LEN * tmp->len)
		if (up_expand_buffer(tmp, len_content + len_str + 1) == RET_ERROR)
			return (RET_ERROR);
	ft_strlcat(tmp->str, content, ARG_LEN * tmp->len);
	ft_freestr(&content);
	return (len_content);
}

int	get_last_exit_status(t_expand *tmp, int mode)
{
	char	*exit_value;
	int		len;

	if (mode == 1)
		tmp->j++;
	exit_value = ft_itoa(get_state());
	if (!exit_value)
		return (RET_ERROR);
	len = ft_strlen(exit_value) + ft_strlen(tmp->str);
	if (len >= ARG_LEN * tmp->len
		&& up_expand_buffer(tmp, len) == RET_ERROR)
	{
		ft_freestr(&exit_value);
		return (RET_ERROR);
	}
	ft_strlcat(tmp->str, exit_value, ARG_LEN * tmp->len);
	ft_freestr(&exit_value);
	return (EXIT_SUCCESS);
}
