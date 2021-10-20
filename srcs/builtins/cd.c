/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/20 11:43:45 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode builtin Cd.

cd [DIR]

Change the shell working directory.
Change the current directory to DIR. The default DIR is the value of the
HOME shell variable.
cd - will go back to the last folder you looked at, and the pwd is printed.
Returns 0 if the directory is changed.
*/

static int	change_old_pwd(t_minishell *minishell)
{
	char	*content;
	int		ret;

	content = ft_getenv(minishell->env, "PWD");
	if (!content)
		return (RET_ERROR);
	ret = ft_setenv(minishell, "OLDPWD", content, 1);
	ft_freestr(&content);
	return (ret);
}

static int	change_directory(t_minishell *minishell, const char *path)
{
	int		ret;

	ret = chdir(path);
	if (ret == RET_ERROR)
		return (builtin_error("cd", path, strerror(errno), 1));
	ret = change_old_pwd(minishell);
	if (ret == RET_ERROR)
		return (builtin_error("cd", path, strerror(errno), 1));
	if (!ft_strcmp(path, "//"))
		ret = ft_setenv(minishell, "PWD", "//", 1);
	else
		ret = set_pwd(minishell, "PWD");
	if (ret == RET_ERROR)
		return (builtin_error("cd", path, strerror(errno), 1));
	return (EXIT_SUCCESS);
}

static int	go_directory(t_minishell *minishell, const char *var_name)
{
	char	*path;
	int		ret;

	path = ft_getenv(minishell->env, var_name);
	if (!path)
	{
		builtin_error("cd", var_name, NOT_SET, 1);
		return (EXIT_FAILURE);
	}
	ret = change_directory(minishell, path);
	ft_freestr(&path);
	return (ret);
}

int	cd_builtin(int ac, char **av, t_minishell *minishell)
{
	int		ret;
	char	*path;

	set_state(EXIT_SUCCESS);
	if (ac > 2)
		return (argument_error(av[CMD]));
	else if (ac == NO_ARGS || !ft_strcmp(av[FIRST_ARG], "~"))
		ret = go_directory(minishell, "HOME");
	else if (av[FIRST_ARG][0] == OPT_INDICATOR && ft_strlen(av[FIRST_ARG]) > 1)
	{
		invalid_option(av[CMD], av[FIRST_ARG]);
		builtin_usage(av[CMD], "cd [path]");
	}
	else if (!ft_strcmp(av[FIRST_ARG], "-"))
	{
		ret = go_directory(minishell, "OLDPWD");
		path = ft_getenv(minishell->env, "PWD");
		if (ret == EXIT_SUCCESS)
			ft_putendl(path);
		ft_freestr(&path);
	}
	else
		ret = change_directory(minishell, av[FIRST_ARG]);
	return (get_state());
}
