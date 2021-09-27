/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:30:16 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 17:02:36 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redir(int initial, int new)
{
	if (initial == new)
		return ;
	if (dup2(initial, new) != RET_ERROR)
		close(initial);
}

void	default_fd(int fd[2])
{
	redir(fd[0], STDIN_FILENO);
	redir(fd[1], STDOUT_FILENO);
}

void	manage_redir(t_cmd *command, int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	redir(command->fd[STDIN_FILENO], STDIN_FILENO);
	redir(command->fd[STDOUT_FILENO], STDOUT_FILENO);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}
