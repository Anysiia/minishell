/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:36:24 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/25 15:55:14 by cmorel-a         ###   ########.fr       */
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
	char	*new;
	char	len;

	if (!cmd_name || !new_folder)
		return (cmd_name);
	len = ft_strlen(cmd_name) + ft_strlen(new_folder);
	new = ft_strnew(len + 2);
	if (!new)
		return (NULL);
	ft_strlcpy(new, cmd_name, ft_strlen(cmd_name));
	new[ft_strlen(cmd_name) + 2] = '/';
	ft_strlcat(new, new_folder, len + 2);
	ft_freestr(&cmd_name);
	return (new);
}

char	*expand_relative_path(char **env, t_cmd *cmd)
{
	char	*cmd_name;
	char	**split_path;
	int		i;

	split_path = ft_split(cmd->av[CMD], '/');
	cmd_name = ft_strnew(PATH_MAX);
	if (!split_path || !cmd_name || !getcwd(cmd_name, PATH_MAX))
		return (NULL);
	i = 0;
	while (split_path[i])
	{
		if (!ft_strcmp(split_path[i], ".."))
			cmd_name = remove_last_folder(cmd_name);
		else if (!ft_strcmp(split_path[i], "~"))
		{
			ft_freestr(&cmd_name);
			cmd_name = ft_getenv(env, "HOME");
		}
		else if (ft_strcmp(split_path[i], "."))
			cmd_name = add_last_folder(cmd_name, split_path[i]);
		if (!cmd_name)
			return (NULL);
		ft_putendl(split_path[i]);
		ft_putendl(cmd_name);
		i++;
	}
	split_path = ft_free_tab(split_path);
	return (cmd_name);
}
