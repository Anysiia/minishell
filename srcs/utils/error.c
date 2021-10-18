/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:24:55 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/18 10:51:15 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_directory(const char *path)
{
	struct stat	buff;
	int			ret;

	ret = stat(path, &buff);
	if (ret != RET_ERROR)
		return (S_ISDIR(buff.st_mode));
	return (ret);
}

void	print_errno(const char *error_command, int mode)
{
	char	str[MAX_MSG];

	set_state(EXIT_FAILURE);
	if (errno == EACCES)
	{
		if (is_directory(error_command))
			errno = EISDIR;
	}
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, SHELL_NAME, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, error_command, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	if (errno == ENOENT && mode == EXECVE)
	{
		ft_strlcat(str, COMMAND_NOT_FOUND, MAX_MSG);
		set_state(CMD_NOT_FOUND);
	}
	else
		ft_strlcat(str, strerror(errno), MAX_MSG);
	ft_strlcat(str, "\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
}

void	print_error(t_minishell *minishell, const char *msg, bool quit)
{
	char	str[MAX_MSG];

	set_state(EXIT_FAILURE);
	if (msg)
	{
		ft_bzero(str, MAX_MSG);
		ft_strlcpy(str, SHELL_NAME, MAX_MSG);
		ft_strlcat(str, ": ", MAX_MSG);
		ft_strlcat(str, msg, MAX_MSG);
		ft_strlcat(str, "\n", MAX_MSG);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	if (quit)
		exit_shell(minishell);
}

void	exit_error(t_minishell *minishell, const char *msg)
{
	char	str[MAX_MSG];

	set_state(EXIT_FAILURE);
	if (msg)
	{
		ft_bzero(str, MAX_MSG);
		ft_strlcpy(str, SHELL_NAME, MAX_MSG);
		ft_strlcat(str, ": ", MAX_MSG);
		ft_strlcat(str, msg, MAX_MSG);
		ft_strlcat(str, "\n", MAX_MSG);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	exit_shell(minishell);
}

void	print_dot_error(const char *cmd_name)
{
	char	str[MAX_MSG];

	set_state(INC_USAGE);
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, SHELL_NAME, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, cmd_name, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, ARG_REQUIRED, MAX_MSG);
	ft_strlcat(str, "\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
}
