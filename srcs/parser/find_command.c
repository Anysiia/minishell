/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:21:50 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/07 15:26:40 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_return(char *path, char **list, char *tmp, int ret)
{
	if (path)
		ft_freestr(&path);
	if (list)
		ft_free_tab(list);
	if (tmp)
		ft_freestr(&tmp);
	return (ret);
}

static char	*join_path(t_env *envp, char *path_env, char *cmd)
{
	char	*relative_path;
	int		len;
	char	*path;

	relative_path = expand_relative_path(envp, path_env);
	if (!relative_path)
		return (NULL);
	len = ft_strlen(relative_path) + ft_strlen(cmd) + 2;
	path = ft_strnew(len);
	if (!path)
	{
		ft_freestr(&relative_path);
		return (NULL);
	}
	ft_strlcpy(path, relative_path, len);
	ft_strlcat(path, "/", len);
	ft_strlcat(path, cmd, len);
	return (path);
}

static int	search_binary(t_env *envp, t_cmd *cmd)
{
	char	*path;
	char	*tmp;
	char	**path_list;
	int		i;

	path = ft_getenv(envp, "PATH");
	if (!path)
		return (EXIT_FAILURE);
	path_list = ft_split(path, ':');
	if (!path_list)
		return (free_return(path, NULL, NULL, EXIT_FAILURE));
	i = 0;
	while (path_list && path_list[i])
	{
		tmp = join_path(envp, path_list[i], cmd->av[CMD]);
		if (!is_file(tmp))
		{
			ft_freestr(&cmd->binary);
			cmd->binary = tmp;
			return (free_return(path, path_list, NULL, EXIT_SUCCESS));
		}
		ft_freestr(&tmp);
		i++;
	}
	return (free_return(path, path_list, tmp, EXIT_FAILURE));
}

int	is_file(const char *name)
{
	struct stat	buffer;
	int			ret;

	ret = stat(name, &buffer);
	if (ret != -1)
	{
		if (S_ISDIR(buffer.st_mode) != 0)
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	find_command(t_env *envp, t_cmd *cmd)
{
	int		ret;
	char	*new;

	if (!cmd || !cmd->av[CMD])
		return ;
	cmd->binary = ft_strdup(cmd->av[CMD]);
	ret = is_builtin(cmd);
	if (ret == EXIT_SUCCESS)
		return ;
	if (!ft_strcmp(".", cmd->av[CMD]))
		return ;
	if (ft_test_set('.', cmd->av[CMD]))
	{
		new = expand_relative_path(envp, cmd->av[CMD]);
		if (new)
		{
			ft_freestr(&cmd->binary);
			cmd->binary = new;
		}
		return ;
	}
	if (is_file(cmd->av[CMD]))
		search_binary(envp, cmd);
}
