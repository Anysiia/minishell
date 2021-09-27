/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:15:42 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 11:50:13 by cmorel-a         ###   ########.fr       */
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

void	print_errno(const char *error_command)
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
	ft_strlcat(str, strerror(errno), MAX_MSG);
	ft_strlcat(str, "\n", MAX_MSG);
	ft_putstr_fd(str, STDERR);
}

void	print_error(const char *msg, bool quit)
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
		ft_putstr_fd(str, STDERR);
	}
	if (quit)
		set_exit(1);
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
		ft_putstr_fd(str, STDERR);
	}
	exit_shell(minishell);
}

void	exit_errno(t_minishell *minishell, const char *msg)
{
	print_errno(msg);
	exit_shell(minishell);
}
