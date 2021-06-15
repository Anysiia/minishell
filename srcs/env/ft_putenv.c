/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:34:50 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/25 11:16:27 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	replace_var_env(t_minishell *minishell, const char *str, int index)
{
	ft_freestr(&minishell->env[index]);
	minishell->env[index] = ft_strdup(str);
	if (!minishell->env[index])
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

int	ft_putenv(t_minishell *minishell, char *string)
{
	int		line;
	char	*name;
	int		index;
	int		ret;

	if (!string)
		return (RET_ERROR);
	ret = find_variable_name(&name, string);
	if (ret == RET_ERROR || ret == INVALID_ID)
		return (ret);
	index = find_variable_index(minishell->env, name);
	ft_freestr(&name);
	if (index == RET_ERROR)
		return (index);
	if (index != NOT_FOUND)
		return (replace_var_env(minishell, string, index));
	line = ft_len_tab(minishell->env);
	minishell->env = dup_env(minishell->env, line + 1, 1);
	if (!minishell->env)
		return (RET_ERROR);
	minishell->env[line] = ft_strdup(string);
	if (!minishell->env[line])
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}
