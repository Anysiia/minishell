/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:57:38 by user42            #+#    #+#             */
/*   Updated: 2021/10/04 14:49:12 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	search_binary(char **env, t_cmd *cmd)
{
	char	*path;
	char	*tmp;
	char	**path_list;
	int		i;

	path = ft_getenv(env, "PATH");
	if (!path)
		return (EXIT_FAILURE);
	path_list = ft_split(path, ':');
	if (!path_list)
		return (free_return(path, NULL, NULL, EXIT_FAILURE));
	i = 0;
	while (path_list && path_list[i])
	{
		tmp = join_var(path_list[i], "/", cmd->av[CMD]);
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

void	find_command(char **env, t_cmd *cmd)
{
	int		ret;
	char	*new;

	if (!cmd || !cmd->av[CMD])
		return ;
	cmd->binary = ft_strdup(cmd->av[CMD]);
	ret = is_builtin(cmd);
	if (ret == EXIT_SUCCESS)
		return ;
	if (ft_test_set('.', cmd->av[CMD]))
	{
		new = expand_relative_path(env, cmd);
		if (new)
		{
			ft_freestr(&cmd->binary);
			cmd->binary = new;
		}
		return ;
	}
	if (is_file(cmd->av[CMD]))
		search_binary(env, cmd);
}
