/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:17:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:17:06 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	replace_value(t_minishell *minishell, int index,
	const char *name, const char *value)
{
	ft_freestr(&minishell->env[index]);
	if (!ft_strcmp(value, EMPTY_STRING))
		minishell->env[index] = ft_strjoin(name, "=");
	else
		minishell->env[index] = join_var(name, "=", value);
	if (!minishell->env[index])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	add_new_variable(t_minishell *minishell, const char *name,
	const char *value)
{
	int		line;

	line = ft_len_tab(minishell->env);
	minishell->env = dup_env(minishell->env, line + 1, 1);
	if (!minishell->env)
		return (RET_ERROR);
	minishell->env[line] = join_var(name, "=", value);
	if (!minishell->env[line])
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

char	*join_var(const char *s1, const char *s2, const char *s3)
{
	char	*new;

	if (!s1 && !s2 && !s3)
		return (NULL);
	new = ft_strjoin(s1, s2);
	if (!new)
		return (NULL);
	new = ft_strjoin_free_s1(new, s3);
	if (!new)
		return (NULL);
	return (new);
}

int	ft_setenv(t_minishell *minishell, const char *name, const char *value,
	int replace)
{
	int		index;

	if (!minishell->env || !name || !value || !ft_strcmp(name, EMPTY_STRING)
		|| ft_test_set(VAR_ENV_SEP, name))
		return (RET_ERROR);
	index = find_variable_index(minishell->env, name);
	if (index >= 0 && replace)
	{
		replace_value(minishell, index, name, value);
		if (!minishell->env[index])
			return (RET_ERROR);
		return (EXIT_SUCCESS);
	}
	else if (index == NOT_FOUND)
		return (add_new_variable(minishell, name, value));
	return (EXIT_SUCCESS);
}
