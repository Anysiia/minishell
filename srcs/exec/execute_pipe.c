/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:36:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/30 15:53:10 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_cmd(t_minishell *minishell, t_cmd *cmd, int *fd, int fdd)
{
	if (dup2(fdd, 0) < 0 || (cmd->next && dup2(fd[1], 1) < 0))
		exit_shell(minishell);
	close_fd(fd[1]);
	close_fd(fdd);
	if (redir_file(cmd) == RET_ERROR)
		exit_shell(minishell);
	if (!cmd->binary || (cmd->binary[0] != '/' && cmd->is_builtin != true))
	{
		errno = ENOENT;
		exit_errno(minishell, cmd->av[CMD], EXECVE);
	}
	else if (cmd->is_builtin == true)
		cmd->command(cmd->ac, cmd->av, minishell);
	else
	{
		execve(cmd->binary, cmd->av, minishell->env);
		print_errno(cmd->av[CMD], EXECVE);
	}
	exit_shell(minishell);
}

static void	exec_pipe(t_minishell *minishell, t_cmd *tmp, int nb_cmd)
{
	int		fd[2];
	int		fdd;
	int		status;
	pid_t	pid;

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
		fdd = fd[0];
		tmp = tmp->next;
	}
	close_fd(fd[0]);
	while (nb_cmd-- > 0)
		wait(&status);
	if (WIFEXITED(status))
		set_state(WEXITSTATUS(status));
}

void	execute_pipe(t_minishell *minishell, t_cmd *command)
{
	t_cmd	*tmp;
	int		nb_cmd;
	int		backup[2];

	if (!command)
		return ;
	backup_fd(minishell, backup);
	tmp = command;
	nb_cmd = 0;
	while (tmp)
	{
		tmp = tmp->next;
		nb_cmd++;
	}
	tmp = command;
	exec_pipe(minishell, tmp, nb_cmd);
	default_fd(minishell, backup);
}
