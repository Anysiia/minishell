/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:14:21 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/25 17:19:34 by cmorel-a         ###   ########.fr       */
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

static int	get_content(char *variable, char **content, int len_name)
{
	int		len;

	len = ft_strlen(variable);
	if (!variable[len_name])
		return (EXIT_SUCCESS);
	*content = ft_strnew(len - len_name);
	if (!*content)
		return (RET_ERROR);
	if (variable[len_name] == '=')
		ft_strlcpy(*content, variable + len_name + 1, len - len_name);
	else if (variable[len_name] == '+' && variable[len_name + 1]
		&& variable[len_name + 1] == '=')
		ft_strlcpy(*content, variable + len_name + 2, len - len_name);
	else
	{
		ft_freestr(content);
		return (INVALID_ID);
	}
	return (EXIT_SUCCESS);
}

static char	*get_name(char *variable, int len_name)
{
	char	*name;

	name = ft_strnew(len_name + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, variable, len_name + 1);
	return (name);
}

static int	export_variable(t_minishell *minishell, char *variable)
{
	int		ret;
	int		len;
	char	*name;
	char	*content;

	len = len_name_env(variable);
	if (len == RET_ERROR)
		return (INVALID_ID);
	name = get_name(variable, len);
	if (!name)
		return (RET_ERROR);
	content = NULL;
	ret = get_content(variable, &content, len);
	if (ret != EXIT_SUCCESS)
	{
		ft_freestr(&name);
		return (ret);
	}
	if (variable[len] == '+' && variable[len + 1] && variable[len + 1] == '=')
		ret = ft_setenv(minishell, name, content, true);
	else
		ret = ft_setenv(minishell, name, content, false);
	return (ret);
}

int	export_builtin(int ac, char **av, t_minishell *minishell)
{
	int		i;
	int		ret;

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
		ret = export_variable(minishell, av[i]);
		if (ret == INVALID_ID)
			invalid_id(av[CMD], av[i]);
		else if (ret == RET_ERROR)
			builtin_error("export", av[i], NOT_SET, EXIT_FAILURE);
		i++;
	}
	return (get_state());
}
