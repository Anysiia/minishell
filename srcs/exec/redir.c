/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:30:16 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/29 20:37:18 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	default_fd(t_minishell *minishell, int fd[2])
{
	if (fd[0] != STDIN_FILENO)
	{
		if (dup2(fd[0], STDIN_FILENO) == RET_ERROR)
			exit_errno(minishell, "fatal error on dup default fd", DUP);
		close_fd(fd[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		if (dup2(fd[1], STDOUT_FILENO) == RET_ERROR)
			exit_errno(minishell, "fatal error on dup default fd", DUP);
		close_fd(fd[1]);
	}
}

void	backup_fd(t_minishell *minishell, int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (fd[0] == RET_ERROR || fd[1] == RET_ERROR)
	{
		default_fd(minishell, fd);
		exit_errno(minishell, "fatal error on dup default fd", DUP);
	}
}

int	redir_file(t_cmd *cmd)
{
	if (cmd->fd_in != NO_REDIR)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (RET_ERROR);
		close_fd(cmd->fd_in);
	}
	if (cmd->fd_out != NO_REDIR)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (RET_ERROR);
		close_fd(cmd->fd_out);
	}
	return (EXIT_SUCCESS);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}
