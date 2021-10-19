/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:19:19 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/19 14:39:59 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	do_redir(t_cmd *cmd)
{
	if (cmd->fd_in != NO_REDIR)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (RET_ERROR);
		close_fd(cmd->fd_in);
	}
	if (cmd->fd_out != NO_REDIR)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (RET_ERROR);
		close_fd(cmd->fd_out);
	}
	return (EXIT_SUCCESS);
}

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
	if (WIFSIGNALED(status))
	{
		set_state(WTERMSIG(status) + FATAL_SIGN);
		if (WTERMSIG(status) == SIGSEGV)
			ft_putstr_fd("Segmentation fault (Core dumped)\n", STDERR_FILENO);
	}
}

void	execute_simple_command(t_minishell *minishell, t_cmd *cmd)
{
	if (do_redir(cmd) == RET_ERROR)
		return (default_fd(minishell));
	if (cmd->ac == 0)
	{
		default_fd(minishell);
		return ;
	}
	else if (cmd->is_builtin == true)
		cmd->command(cmd->ac, cmd->av, minishell);
	else if (!cmd->binary || (cmd->binary[0] != '/' && cmd->binary[0] != '.'))
	{
		errno = ENOENT;
		print_errno(cmd->av[CMD], EXECVE);
		default_fd(minishell);
		return ;
	}
	else if (cmd->binary[0] == '.')
		print_dot_error(cmd->av[CMD]);
	else
		fork_process(minishell, cmd);
	default_fd(minishell);
}
