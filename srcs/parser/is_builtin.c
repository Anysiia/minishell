/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:57:38 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 11:54:11 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_builtin(t_cmd *cmd, t_function builtin)
{
	cmd->is_builtin = true;
	cmd->command = builtin;
	return (EXIT_SUCCESS);
}

static int	get_builtin(t_cmd *cmd, const char *name)
{
	if (!name)
		return (RET_ERROR);
	else if (!ft_strcmp("cd", name))
		return (set_builtin(cmd, &cd_builtin));
	else if (!ft_strcmp("echo", name))
		return (set_builtin(cmd, &echo_builtin));
	else if (!ft_strcmp("env", name))
		return (set_builtin(cmd, &env_builtin));
	else if (!ft_strcmp("exit", name))
		return (set_builtin(cmd, &exit_builtin));
	else if (!ft_strcmp("export", name))
		return (set_builtin(cmd, &export_builtin));
	else if (!ft_strcmp("pwd", name))
		return (set_builtin(cmd, &pwd_builtin));
	else if (!ft_strcmp("unset", name))
		return (set_builtin(cmd, &unset_builtin));
	else
		return (NOT_FOUND);
}

static char	*get_command_name(const char *name)
{
	int		len;
	int		len_command;
	int		i;
	char	*cmd;

	if (!ft_test_set('/', name))
		return (ft_strdup(name));
	len = ft_strlen(name);
	i = len;
	len_command = 0;
	while (name[i] != '/' && i >= 0)
	{
		i--;
		len_command++;
	}
	cmd = ft_strnew(len_command + 1);
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, name + len - len_command + 1, len_command + 1);
	return (cmd);
}

int	is_builtin(t_cmd *cmd)
{
	char	*command_name;
	int		ret;

	if (cmd->av[CMD][0] != '/')
		return (get_builtin(cmd, cmd->av[CMD]));
	if (!is_file(cmd->av[CMD]))
		return (RET_ERROR);
	command_name = get_command_name(cmd->av[CMD]);
	if (!command_name)
		return (RET_ERROR);
	ret = get_builtin(cmd, command_name);
	ft_freestr(&command_name);
	return (ret);
}
