/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:24:55 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/02 13:44:33 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buffer_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_src + len_dst >= dstsize)
	{
		ft_putstr_fd(dst, STDERR_FILENO);
		ft_putstr_fd(src, STDERR_FILENO);
		ft_bzero(dst, dstsize);
	}
	else
		ft_strlcat(dst, src, dstsize);
}

int	is_directory(const char *path)
{
	struct stat	buff;
	int			ret;

	ret = stat(path, &buff);
	if (ret != RET_ERROR)
	{
		if (S_ISDIR(buff.st_mode))
			return (1);
		else
			return (0);
	}
	return (ret);
}

void	print_errno(const char *error_command, int mode)
{
	char	str[MAX_MSG];

	g_state = EXIT_FAILURE;
	if (errno == EACCES && is_directory(error_command) == 1)
		errno = EISDIR;
	if (errno == EISDIR && mode == EXECVE)
		g_state = CMD_DIRECTORY;
	if (errno == EACCES && mode == EXECVE)
		g_state = CMD_DIRECTORY;
	ft_bzero(str, MAX_MSG);
	buffer_strlcat(str, SHELL_NAME, MAX_MSG);
	buffer_strlcat(str, ": ", MAX_MSG);
	buffer_strlcat(str, error_command, MAX_MSG);
	buffer_strlcat(str, ": ", MAX_MSG);
	if (errno == ENOENT && mode == EXECVE)
	{
		buffer_strlcat(str, COMMAND_NOT_FOUND, MAX_MSG);
		g_state = CMD_NOT_FOUND;
	}
	else
		buffer_strlcat(str, strerror(errno), MAX_MSG);
	buffer_strlcat(str, "\n", MAX_MSG);
	if (errno == ENOENT && mode == NOT_EXIST)
		g_state = CMD_NOT_FOUND;
	ft_putstr_fd(str, STDERR_FILENO);
}

void	print_error(t_minishell *minishell, const char *msg, bool quit)
{
	char	str[MAX_MSG];

	g_state = EXIT_FAILURE;
	if (msg)
	{
		ft_bzero(str, MAX_MSG);
		buffer_strlcat(str, SHELL_NAME, MAX_MSG);
		buffer_strlcat(str, ": ", MAX_MSG);
		buffer_strlcat(str, msg, MAX_MSG);
		buffer_strlcat(str, "\n", MAX_MSG);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	if (quit)
		exit_shell(minishell);
}

void	print_dot_error(const char *cmd_name)
{
	char	str[MAX_MSG];

	g_state = INC_USAGE;
	ft_bzero(str, MAX_MSG);
	buffer_strlcat(str, SHELL_NAME, MAX_MSG);
	buffer_strlcat(str, ": ", MAX_MSG);
	buffer_strlcat(str, cmd_name, MAX_MSG);
	buffer_strlcat(str, ": ", MAX_MSG);
	buffer_strlcat(str, ARG_REQUIRED, MAX_MSG);
	buffer_strlcat(str, "\n.: usage: . filename [arguments]\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
}
