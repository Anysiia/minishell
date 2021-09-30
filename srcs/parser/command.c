/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:14:31 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/30 11:15:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*malloc_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		set_state(EXIT_FAILURE);
		set_exit(EXIT_FAILURE);
		return (NULL);
	}
	cmd->ac = -1;
	cmd->av = NULL;
	cmd->binary = NULL;
	cmd->is_builtin = false;
	cmd->command = NULL;
	cmd->fd_in = NO_REDIR;
	cmd->fd_out = NO_REDIR;
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
		ft_free_tab(current->av);
		ft_freestr(&current->binary);
		free(current);
		current = next;
	}
	*command = NULL;
}
