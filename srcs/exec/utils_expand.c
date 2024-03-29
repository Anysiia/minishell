/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:21:00 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/08 13:28:18 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_variable_name(t_expand *tmp, const char *arg)
{
	int		len;
	int		i;
	char	*name;

	len = 0;
	while (arg[tmp->j + len] && char_var(arg[tmp->j + len]))
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

char	*get_variable_content(t_expand *tmp, const char *arg, t_env *env)
{
	char	*name;
	char	*content;

	name = get_variable_name(tmp, arg);
	if (!name)
		return (NULL);
	content = ft_getenv(env, name);
	ft_freestr(&name);
	return (content);
}

int	expand_tilde(t_expand *tmp, const char *arg, t_env *envp)
{
	char	*content;
	int		len;

	if (tmp->j == 0 && (!arg[1] || arg[1] == '/'))
	{
		content = ft_getenv(envp, "HOME");
		if (!content)
			return (cat_c_to_str(tmp, arg[tmp->j]));
		len = ft_strlen(content) + ft_strlen(tmp->str);
		if (len >= ARG_LEN * tmp->len)
			if (up_expand_buffer(tmp, len + 1) == RET_ERROR)
				return (RET_ERROR);
		ft_strlcat(tmp->str, content, ARG_LEN * tmp->len);
		ft_freestr(&content);
		return (EXIT_SUCCESS);
	}
	else
		return (cat_c_to_str(tmp, arg[tmp->j]));
}

int	get_last_exit_status(t_expand *tmp)
{
	char	*exit_value;
	int		len;

	tmp->j++;
	exit_value = ft_itoa(g_state);
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

int	char_var(int c)
{
	return ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || c == '_');
}
