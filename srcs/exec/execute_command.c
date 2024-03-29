/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:18:21 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/06 08:43:01 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_all_args(t_minishell *minishell, t_cmd *command)
{
	int		i;
	int		ret;

	i = 0;
	while (command->av && command->av[i])
	{
		if (command->av[i][0] == '~' || ft_test_set(WEAK_QUOTE, command->av[i])
			|| ft_test_set(STRONG_QUOTE, command->av[i])
			|| ft_test_set(ENV_VAR_SIGN, command->av[i]))
		{
			ret = expand_token_word(minishell->envp, command, &i);
			if (ret)
			{
				print_error(minishell, ARG_EXPANSION, 0);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	find_command(minishell->envp, command);
	return (EXIT_SUCCESS);
}

static void	execute_builtin(t_minishell *minishell, t_cmd *cmd)
{
	if (cmd->type)
		return (handle_error_redir(cmd));
	if (cmd->fd_in != NO_REDIR)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (default_fd(minishell));
		close_fd(cmd->fd_in);
	}
	if (cmd->fd_out != NO_REDIR)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (default_fd(minishell));
		close_fd(cmd->fd_out);
	}
	cmd->command(cmd->ac, cmd->av, minishell);
	default_fd(minishell);
}

void	execute_command(t_minishell *minishell, t_cmd *command)
{
	t_cmd	*tmp;
	int		ret;

	if (!command)
		return ;
	tmp = command;
	while (tmp)
	{
		ret = expand_all_args(minishell, tmp);
		if (ret == RET_ERROR)
		{
			g_state = EXIT_FAILURE;
			return ;
		}
		tmp = tmp->next;
	}
	exec_signal(minishell);
	convert_env_list_in_tab(minishell);
	if (!command->next && command->is_builtin == true)
		execute_builtin(minishell, command);
	else
		execute_pipe(minishell, command);
	minishell->env = ft_free_tab(minishell->env);
}
