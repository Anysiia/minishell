/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:32:38 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/29 11:19:18 by cmorel-a         ###   ########.fr       */
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
		execve(command->av[CMD], command->av, minishell->env);
		exit_errno(minishell, command->av[CMD], EXECVE);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_state(WEXITSTATUS(status));
}

void	execute_simple_command(t_minishell *minishell, t_cmd *command)
{
	int		fd[2];

	manage_redir(command, fd);
	if (command->is_builtin == true)
		command->command(command->ac, command->av, minishell);
	else
		fork_process(minishell, command);
	default_fd(fd);
}
