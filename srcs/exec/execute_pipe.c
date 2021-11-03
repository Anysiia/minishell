/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:18:40 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/03 17:27:38 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_file(t_cmd *cmd, int *fd, int fdd)
{
	if (cmd->fd_in == NO_REDIR && cmd->prev && dup2(fdd, 0) < 0)
		return (RET_ERROR);
	if (cmd->fd_out == NO_REDIR && cmd->next && dup2(fd[1], 1) < 0)
		return (RET_ERROR);
	close_fd(fd[1]);
	close_fd(fd[0]);
	close_fd(fdd);
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

static void	exec_cmd(t_minishell *minishell, t_cmd *cmd, int *fd, int fdd)
{
	if (redir_file(cmd, fd, fdd) == RET_ERROR)
		exit_shell(minishell);
	if (cmd->ac == 0)
	{
		set_state(0);
		exit_shell(minishell);
	}
	else if (cmd->is_builtin == true)
		cmd->command(cmd->ac, cmd->av, minishell);
	else if (!cmd->binary || (cmd->binary[0] != '/' && cmd->binary[0] != '.'))
	{
		errno = ENOENT;
		print_errno(cmd->av[CMD], EXECVE);
	}
	else if (cmd->binary[0] == '.')
		print_dot_error(cmd->av[CMD]);
	else
	{
		execve(cmd->binary, cmd->av, minishell->env);
		print_errno(cmd->av[CMD], EXECVE);
	}
	exit_shell(minishell);
}

static void	wait_childs(pid_t pid, int nb_cmd)
{
	int	status;

	waitpid(pid, &status, 0);
	while (nb_cmd-- > 1)
		wait(NULL);
	if (WIFEXITED(status))
		set_state(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		set_state(WTERMSIG(status) + FATAL_SIGN);
		if (WTERMSIG(status) == SIGSEGV)
			ft_putstr_fd("Segmentation fault (Core dumped)\n", STDERR_FILENO);
	}
}

void	execute_pipe(t_minishell *minishell, t_cmd *command)
{
	t_cmd	*tmp;
	int		fd[2];
	int		fdd;
	pid_t	pid;

	tmp = command;
	fdd = 0;
	while (tmp)
	{
		if (tmp->next && pipe(fd) < 0)
			exit_errno(minishell, "pipe", PIPE);
		pid = fork();
		if (pid < 0)
			exit_errno(minishell, "fork", FORK);
		else if (pid == 0)
			exec_cmd(minishell, tmp, fd, fdd);
		close_fd(fd[1]);
		close_fd(fdd);
		fdd = fd[0];
		tmp = tmp->next;
	}
	wait_childs(pid, minishell->nb_cmd);
	default_fd(minishell);
}
