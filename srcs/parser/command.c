/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:21:21 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/08 12:16:39 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*malloc_command(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit_error(minishell, MALLOC_COMMAND);
	cmd->ac = -1;
	cmd->av = NULL;
	cmd->heredoc = 0;
	cmd->hd_name = NULL;
	cmd->binary = NULL;
	cmd->is_builtin = false;
	cmd->command = NULL;
	cmd->fd_in = NO_REDIR;
	cmd->fd_out = NO_REDIR;
	cmd->name = NULL;
	cmd->type = 0;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	free_command(t_cmd **command)
{
	t_cmd	*next;
	t_cmd	*current;

	if (!command)
		return ;
	current = *command;
	while (current)
	{
		next = current->next;
		close_fd(current->fd_in);
		close_fd(current->fd_out);
		if (current->heredoc == 1)
		{
			unlink(current->hd_name);
			ft_freestr(&current->hd_name);
		}
		ft_free_tab(current->av);
		ft_freestr(&current->binary);
		ft_freestr(&current->name);
		free(current);
		current = next;
	}
	*command = NULL;
}
