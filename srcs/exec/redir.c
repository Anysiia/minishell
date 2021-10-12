/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:30:16 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/12 16:14:53 by cmorel-a         ###   ########.fr       */
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
