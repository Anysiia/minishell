/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:51:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/25 11:31:54 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode the export builtin.
Set export attribute for shell variables.

If export with no args: printenv with sorting variables and 'declare -x ' prefix
Export can add more than one variable.
Format to add a new variable: NAME=[value] or NAME+=[value]
*/

static int	add_value_to_var(t_minishell *minishell, char *to_add, int index)
{
	int		len;
	int		to_add_len;
	int		len_name;
	char	*new;

	if (!ft_test_set(VAR_ENV_SEP, minishell->env[index]))
		minishell->env[index] = ft_strjoin_free_s1(minishell->env[index], "=");
	if (!minishell->env[index])
		builtin_error("export", to_add, NOT_SET, EXIT_FAILURE);
	len = ft_strlen(minishell->env[index]);
	len_name = len_name_env(minishell->env[index]);
	to_add_len = ft_strlen(to_add) - len_name - 2;
	if (len_name == RET_ERROR)
		return (RET_ERROR);
	new = ft_strnew(len + to_add_len + 1);
	if (!new)
		return (RET_ERROR);
	ft_strlcpy(new, minishell->env[index], len + 1);
	ft_strlcat(new, to_add + len_name + 2, len + to_add_len + 1);
	ft_freestr(&minishell->env[index]);
	minishell->env[index] = new;
	return (EXIT_SUCCESS);
}

static char	*remove_first_plus(char *string)
{
	char	*variable;
	int		len;
	int		i;
	int		j;
	bool	plus;

	len = ft_strlen(string);
	variable = ft_strnew(len);
	i = 0;
	j = 0;
	plus = false;
	while (string[i])
	{
		if (string[i] == '+' && !plus)
			plus = true;
		else
			variable[j++] = string[i];
		i++;
	}
	return (variable);
}

static int	export_add(t_minishell *minishell, char *string)
{
	int		line;
	char	*name;
	int		index;
	int		ret;

	ret = len_name_env(string);
	if (ret < 0)
		return (RET_ERROR);
	name = ft_strndup(string, ret);
	if (!name)
		return (ret);
	index = find_variable_index(minishell->env, name);
	ft_freestr(&name);
	if (index == RET_ERROR)
		return (index);
	if (index != NOT_FOUND)
		return (add_value_to_var(minishell, string, index));
	line = ft_len_tab(minishell->env);
	minishell->env = dup_env(minishell->env, line + 1, 1);
	if (!minishell->env)
		return (RET_ERROR);
	minishell->env[line] = remove_first_plus(string);
	if (!minishell->env[line])
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

static void	export_variable(t_minishell *minishell, char *cmd, char *variable)
{
	int		ret;
	int		len;

	if (!variable)
	{
		save_state(true, EXIT_FAILURE);
		return ;
	}
	len = len_name_env(variable);
	if (len == RET_ERROR)
	{
		invalid_id(cmd, variable);
		return ;
	}
	if (variable[len] == '+' && variable[len + 1] && variable[len + 1] == '=')
		ret = export_add(minishell, variable);
	else
		ret = ft_putenv(minishell, variable);
	if (ret == INVALID_ID)
		invalid_id(cmd, variable);
	else if (ret == RET_ERROR)
		builtin_error(cmd, variable, NOT_SET, EXIT_FAILURE);
}

int	export_builtin(int ac, char **av, t_minishell *minishell)
{
	int		i;

	set_state(EXIT_SUCCESS);
	if (ac == NO_ARGS)
		return (print_sort_env(minishell->env));
	i = FIRST_ARG;
	if (av[FIRST_ARG][0] == OPT_INDICATOR)
	{
		invalid_option(av[CMD], av[FIRST_ARG]);
		builtin_usage(av[CMD], "export [name[[+]=value] ...]");
		return (get_state());
	}
	while (i < ac)
	{
		export_variable(minishell, "export", av[i]);
		i++;
	}
	return (get_state());
}
