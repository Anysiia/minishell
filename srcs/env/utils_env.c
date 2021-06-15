/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:02:32 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 10:09:54 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	len_name_env(const char *name)
{
	size_t	len;

	len = 0;
	if (name[len] && ft_isdigit(name[len]))
		return (RET_ERROR);
	while (name[len] && (ft_isalnum(name[len]) || name[len] == '_'))
		len++;
	return (len);
}

int	find_variable_index(char **env, const char *name)
{
	int	i;
	int	len;

	if (!env || !name)
		return (RET_ERROR);
	i = 0;
	len = len_name_env(name);
	if (name[len])
		return (INVALID_ID);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len))
			return (i);
		i++;
	}
	return (NOT_FOUND);
}

int	find_variable_name(char **name, const char *string)
{
	size_t	len;

	if (!string)
		return (RET_ERROR);
	len = len_name_env(string);
	if (string[len] && string[len] != VAR_ENV_SEP)
		return (INVALID_ID);
	*name = ft_strndup(string, len);
	if (!*name)
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

int	find_variable_value(char **value, const char *string)
{
	int		len_name;
	int		total_len;
	int		value_len;

	if (!string)
		return (RET_ERROR);
	len_name = len_name_env(string);
	if (len_name == RET_ERROR || string[len_name] != VAR_ENV_SEP)
		return (INVALID_ID);
	total_len = ft_strlen(string);
	value_len = total_len - len_name;
	*value = ft_strnew(value_len + 1);
	if (!value)
		return (RET_ERROR);
	ft_strlcpy(*value, string + len_name + 1, value_len);
	return (EXIT_SUCCESS);
}

int	set_pwd(t_minishell *minishell, const char *env_name)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (RET_ERROR);
	return (ft_setenv(minishell, env_name, path, 1));
}
