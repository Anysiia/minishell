/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:20:44 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:20:47 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
