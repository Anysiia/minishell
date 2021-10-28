/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/28 17:14:20 by cmorel-a         ###   ########.fr       */
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

static int	set_pwd(t_minishell *minishell, bool special_case)
{
	char	path[PATH_MAX];
	char	*path2;
	char	*duppwd;

	duppwd = ft_strdup("PWD");
	if (!duppwd)
		return (RET_ERROR);
	if (special_case == true)
		path2 = ft_strdup("//");
	else
	{
		if (!getcwd(path, PATH_MAX))
			return (RET_ERROR);
		path2 = ft_strdup(path);
	}
	if (!path2)
	{
		ft_freestr(&duppwd);
		return (RET_ERROR);
	}
	return (ft_setenv(minishell, duppwd, path2, false));
}

static int	change_old_pwd(t_minishell *minishell)
{
	char	*dupoldpwd;
	char	*content;
	char	path[PATH_MAX];
	int		ret;

	dupoldpwd = ft_strdup("OLDPWD");
	if (!dupoldpwd)
		return (RET_ERROR);
	content = ft_getenv(minishell->envp, "PWD");
	if (!content && !getcwd(path, PATH_MAX))
	{
		if (!getcwd(path, PATH_MAX))
			return (RET_ERROR);
		return (ft_setenv(minishell, dupoldpwd, content, false));
	}
	ret = ft_setenv(minishell, dupoldpwd, content, false);
	return (ret);
}

static int	change_directory(t_minishell *minishell, const char *path)
{
	int		ret;

	ret = change_old_pwd(minishell);
	if (ret == RET_ERROR)
		return (builtin_error("cd", path, strerror(errno), 1));
	ret = chdir(path);
	if (ret == RET_ERROR)
		return (builtin_error("cd", path, strerror(errno), 1));
	if (!ft_strcmp(path, "//"))
		ret = set_pwd(minishell, true);
	else
		ret = set_pwd(minishell, false);
	if (ret == RET_ERROR)
		return (builtin_error("cd", path, strerror(errno), 1));
	return (EXIT_SUCCESS);
}

static int	go_directory(t_minishell *minishell, const char *var_name)
{
	char	*path;
	int		ret;

	path = ft_getenv(minishell->envp, var_name);
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
	if (!av[FIRST_ARG])
		ret = go_directory(minishell, "HOME");
	else if (av[FIRST_ARG][0] == OPT_INDICATOR && ft_strlen(av[FIRST_ARG]) > 1)
	{
		invalid_option(av[CMD], av[FIRST_ARG]);
		builtin_usage(av[CMD], "cd [path]");
	}
	else if (!ft_strcmp(av[FIRST_ARG], "-"))
	{
		ret = go_directory(minishell, "OLDPWD");
		path = ft_getenv(minishell->envp, "PWD");
		if (ret == EXIT_SUCCESS)
			ft_putendl(path);
		ft_freestr(&path);
	}
	else
		ret = change_directory(minishell, av[FIRST_ARG]);
	return (get_state());
}
