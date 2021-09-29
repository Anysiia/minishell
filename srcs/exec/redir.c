/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:30:16 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/29 16:55:58 by cmorel-a         ###   ########.fr       */
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
	if (cmd->fd[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd[0], STDIN_FILENO) < 0)
		{
			ft_putendl("stdin redir");
			return (RET_ERROR);
		}
		close_fd(cmd->fd[0]);
	}
	if (cmd->fd[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd[1], STDOUT_FILENO) < 0)
		{
			ft_putendl("stdout redir");
			return (RET_ERROR);
		}
		close_fd(cmd->fd[1]);
	}
	return (EXIT_SUCCESS);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}
