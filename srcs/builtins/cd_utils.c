/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:46:43 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/05 13:32:39 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (ft_setenv(minishell, dupoldpwd, content, false));
}

int	change_directory(t_minishell *minishell, const char *path)
{
	int		ret;

	change_old_pwd(minishell);
	ret = chdir(path);
	if (ret == RET_ERROR)
		return (builtin_error("cd", path, strerror(errno), 1));
	if (!ft_strcmp(path, "//"))
		set_pwd(minishell, true);
	else
		set_pwd(minishell, false);
	return (EXIT_SUCCESS);
}

int	go_directory(t_minishell *minishell, const char *var_name)
{
	char	*path;

	path = ft_getenv(minishell->envp, var_name);
	if (!path)
		return (builtin_error("cd", var_name, NOT_SET, 1));
	change_directory(minishell, path);
	ft_freestr(&path);
	return (EXIT_SUCCESS);
}

void	cd_minus(t_minishell *minishell)
{
	char	*path;

	if (go_directory(minishell, "OLDPWD"))
	{
		g_state = EXIT_FAILURE;
		return ;
	}
	path = ft_getenv(minishell->envp, "PWD");
	if (path)
		ft_putendl_fd(path, STDOUT_FILENO);
	else
		g_state = EXIT_FAILURE;
	ft_freestr(&path);
}
