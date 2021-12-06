/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:23:30 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/06 08:45:46 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_last_folder(char *cmd_name)
{
	int		len;

	if (!cmd_name)
		return (NULL);
	len = ft_strlen(cmd_name);
	while (len >= 0 && cmd_name[len] != '/')
		cmd_name[len--] = '\0';
	len = ft_strlen(cmd_name);
	if (len != 0 && cmd_name[len - 1] == '/')
		cmd_name[len - 1] = '\0';
	return (cmd_name);
}

static char	*add_last_folder(char *cmd_name, char *new_folder)
{
	int	len;

	if (!cmd_name || !new_folder)
		return (cmd_name);
	len = ft_strlen(cmd_name);
	if (len == 0 || (len != 0 && cmd_name[len - 1] != '/'))
		cmd_name[len] = '/';
	ft_strlcat(cmd_name, new_folder, PATH_MAX);
	return (cmd_name);
}

static char	*get_path(t_env *envp, char *cmd_name, char **split_path)
{
	char	*home;
	int		i;

	i = 0;
	while (split_path[i])
	{
		if (!ft_strcmp(split_path[i], ".."))
			cmd_name = remove_last_folder(cmd_name);
		else if (!ft_strcmp(split_path[i], "~"))
		{
			ft_bzero(cmd_name, PATH_MAX);
			home = ft_getenv(envp, "HOME");
			ft_strlcpy(cmd_name, home, ft_strlen(home));
			ft_freestr(&home);
		}
		else if (ft_strcmp(split_path[i], "."))
			cmd_name = add_last_folder(cmd_name, split_path[i]);
		i++;
	}
	return (cmd_name);
}

static char	*get_pwd(t_env *envp, t_cmd *cmd, char **split, char *cmd_name)
{
	char	*pwd;

	pwd = ft_getenv(envp, "PWD");
	if (!pwd)
	{
		ft_free_tab(split);
		ft_freestr(&cmd_name);
		return (ft_strdup(cmd->av[CMD]));
	}
	ft_bzero(cmd_name, PATH_MAX);
	ft_strlcpy(cmd_name, pwd, PATH_MAX);
	ft_freestr(&pwd);
	return (cmd_name);
}

char	*expand_relative_path(t_env *envp, t_cmd *cmd)
{
	char	**split;
	char	*cmd_name;

	if (!ft_test_set('/', cmd->av[CMD]))
		return (ft_strdup(cmd->av[CMD]));
	cmd_name = ft_strnew(PATH_MAX);
	if (!cmd_name)
		return (ft_strdup(cmd->av[CMD]));
	split = ft_split(cmd->av[CMD], '/');
	if (!split)
	{
		ft_freestr(&cmd_name);
		return (ft_strdup(cmd->av[CMD]));
	}
	if (split[0] && (!ft_strcmp("..", split[0]) || !ft_strcmp(".", split[0])))
		get_pwd(envp, cmd, split, cmd_name);
	cmd_name = get_path(envp, cmd_name, split);
	split = ft_free_tab(split);
	return (cmd_name);
}
