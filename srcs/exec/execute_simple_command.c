/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:32:38 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/30 11:57:13 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fork_process(t_minishell *minishell, t_cmd *command)
{
	int		status;
	pid_t	pid;

	pid = fork();
	status = 0;
	if (pid == RET_ERROR)
		exit_errno(minishell, "fork", FORK);
	if (pid == 0)
	{
		execve(command->binary, command->av, minishell->env);
		exit_errno(minishell, command->av[CMD], EXECVE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_state(WEXITSTATUS(status));
}

void	execute_simple_command(t_minishell *minishell, t_cmd *cmd)
{
	int		fd[2];

	backup_fd(minishell, fd);
	if (redir_file(cmd) == RET_ERROR)
	{
		default_fd(minishell, fd);
		return ;
	}
	if (cmd->is_builtin == true)
		cmd->command(cmd->ac, cmd->av, minishell);
	else
		fork_process(minishell, cmd);
	default_fd(minishell, fd);
}
