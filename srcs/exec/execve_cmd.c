/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:12:02 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 08:48:45 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd_list(t_minishell *minishell, t_cmd *cmd)
{
	t_cmd	*next;
	t_cmd	*current;

	current = minishell->cmd;
	while (current)
	{
		next = current->next;
		close_fd(current->fd_in);
		close_fd(current->fd_out);
		ft_freestr(&current->hd_name);
		if (current != cmd)
			ft_free_tab(current->av);
		if (current != cmd)
			ft_freestr(&current->binary);
		free(current);
		current = next;
	}
}

void	execve_cmd(t_minishell *minishell, t_cmd *cmd)
{
	char	*cmd_name;
	char	**cmd_arg;

	cmd_name = cmd->binary;
	cmd_arg = cmd->av;
	if (minishell->lexer)
		free_lexer(minishell->lexer);
	if (minishell->envp)
		free_envp(&minishell->envp);
	close_fd(minishell->back_stdin);
	close_fd(minishell->back_stdout);
	rl_clear_history();
	free_cmd_list(minishell, cmd);
	minishell->cmd = NULL;
	execve(cmd_name, cmd_arg, minishell->env);
	print_errno(cmd->av[CMD], EXECVE);
	ft_freestr(&cmd_name);
	ft_free_tab(cmd_arg);
	ft_free_tab(minishell->env);
	minishell->env = NULL;
	exit(g_state);
}
