/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:46:43 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/02 11:47:45 by cmorel-a         ###   ########.fr       */
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

int	change_directory(t_minishell *minishell, const char *path)
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
