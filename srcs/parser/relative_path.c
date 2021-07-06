/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:36:24 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/07/06 12:01:33 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_last_folder(char *cmd_name)
{
	int		len;

	if (!cmd_name)
		return (NULL);
	len = ft_strlen(cmd_name);
	while (len > 0 && cmd_name[len] != '/')
		cmd_name[len--] = '\0';
	return (cmd_name);
}

static char	*add_last_folder(char *cmd_name, char *new_folder)
{
	int	len;

	if (!cmd_name || !new_folder)
		return (cmd_name);
	len = ft_strlen(cmd_name);
	if (len != 0 && cmd_name[len - 1] != '/')
		cmd_name[len] = '/';
	ft_strlcat(cmd_name, new_folder, PATH_MAX);
	return (cmd_name);
}

char	*expand_relative_path(char **env, t_cmd *cmd)
{
	char	*cmd_name;
	char	*home;
	char	**split_path;
	int		i;

	i = 0;
	cmd_name = ft_strnew(PATH_MAX);
	split_path = ft_split(cmd->av[CMD], '/');
	if (!split_path || !cmd_name || ((split_path[i]
		&& (!ft_strcmp("..", split_path[i]) || !ft_strcmp(".", split_path[i])))
		&& !getcwd(cmd_name, PATH_MAX)))
		return (NULL);
	if (!ft_strcmp(".", split_path[i]))
		i++;
	while (split_path[i])
	{
		if (!ft_strcmp(split_path[i], ".."))
			cmd_name = remove_last_folder(cmd_name);
		else if (!ft_strcmp(split_path[i], "~"))
		{
			ft_bzero(cmd_name, PATH_MAX);
			home = ft_getenv(env, "HOME");
			ft_strlcpy(cmd_name, home, ft_strlen(home));
			ft_freestr(&home);
		}
		else if (ft_strcmp(split_path[i], "."))
			cmd_name = add_last_folder(cmd_name, split_path[i]);
		i++;
	}
	split_path = ft_free_tab(split_path);
	return (cmd_name);
}
