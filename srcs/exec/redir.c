/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:30:16 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/25 12:31:25 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redir(int initial, int new)
{
	if (initial == -1 || new == -1 || initial == new)
		return ;
	if (dup2(initial, new) != RET_ERROR)
		close(initial);
}

void	default_fd(int fd[2])
{
	redir(fd[0], STDIN);
	redir(fd[1], STDOUT);
}

void	manage_redir(t_cmd *command, int fd[2])
{
	fd[0] = dup(STDIN);
	fd[1] = dup(STDOUT);
	redir(command->fd[STDIN], STDIN);
	redir(command->fd[STDOUT], STDOUT);
}
