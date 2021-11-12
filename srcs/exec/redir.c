/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:20:44 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/12 11:04:02 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_error_redir(t_cmd *cmd)
{
	errno = cmd->set_errno;
	print_errno(cmd->name, 0);
}

int	redir_file(t_cmd *cmd, int *fd, int fdd, int nb_cmd)
{
	if (cmd->fd_in == NO_REDIR && cmd->prev && dup2(fdd, 0) < 0)
		return (RET_ERROR);
	if (cmd->fd_out == NO_REDIR && cmd->next && dup2(fd[1], 1) < 0)
		return (RET_ERROR);
	if (nb_cmd > 1)
	{
		close_fd(fd[1]);
		close_fd(fd[0]);
		close_fd(fdd);
	}
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

void	default_fd(t_minishell *minishell)
{
	if (dup2(minishell->back_stdin, STDIN_FILENO) == RET_ERROR)
		exit_errno(minishell, "fatal error on dup default fd", DUP);
	if (dup2(minishell->back_stdout, STDOUT_FILENO) == RET_ERROR)
		exit_errno(minishell, "fatal error on dup default fd", DUP);
}

void	close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}
