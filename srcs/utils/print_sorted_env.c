/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:51:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/11 15:39:47 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**sort_env(char **env)
{
	char	**sorted_env;
	int		i;
	int		j;

	sorted_env = dup_env(env, ft_len_tab(env), 0);
	if (!sorted_env)
	{
		print_error(MALLOC_DUP_ENV, true);
		return (NULL);
	}
	i = 0;
	while (sorted_env[i])
	{
		j = 0;
		while (sorted_env[j])
		{
			if (ft_strcmp(sorted_env[i], sorted_env[j]) < 0)
				ft_strswap(&(sorted_env[i]), &(sorted_env[j]));
			j++;
		}
		i++;
	}
	return (sorted_env);
}

static char	*add_backslash(char *value)
{
	int		i;
	int		j;
	char	*new;

	j = ft_strlen(value);
	i = 0;
	while (value[i])
		if (value[i++] == BACKSLASH)
			j++;
	new = ft_strnew(j + 1);
	if (!new)
	{
		ft_freestr(&value);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == BACKSLASH)
			new[j++] = value[i];
		new[j++] = value[i++];
	}
	ft_freestr(&value);
	return (new);
}

static int	print_value(char *variable)
{
	int		ret;
	int		i;
	size_t	len;
	char	*value;

	if (!variable)
		return (RET_ERROR);
	ret = EXIT_SUCCESS;
	i = len_name_env(variable);
	len = ft_strlen(variable) - i;
	value = ft_substr(variable, (i + 1), len);
	if (value == NULL)
		return (RET_ERROR);
	if (ft_test_set(BACKSLASH, value))
	{
		value = add_backslash(value);
		if (!value)
			return (RET_ERROR);
	}
	printf("declare -x %.*s=\"%s\"\n", i, variable, value);
	ft_freestr(&value);
	return (ret);
}

static int	print_env_sorted(char **env)
{
	int		i;
	int		ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (!env)
		return (RET_ERROR);
	while (env[i] && ret >= 0)
	{
		if (!ft_test_set(VAR_ENV_SEP, env[i]))
			printf("declare -x %s\n", env[i]);
		else if (ft_strncmp(env[i], "_=", 2))
			ret = print_value(env[i]);
		i++;
	}
	return (ret);
}

int	print_sort_env(char **env)
{
	char	**new_env;
	int		ret;

	new_env = sort_env(env);
	if (!new_env)
		return (EXIT_SUCCESS);
	ret = print_env_sorted(new_env);
	ft_free_tab(new_env);
	if (ret < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
