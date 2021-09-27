/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:36:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 12:02:42 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redir_file(t_minishell *minishell, t_cmd *cmd)
{
	if (cmd->fd[0] != STDIN)
	{
		if (dup2(cmd->fd[0], STDIN) < 0)
			exit_shell(minishell);
		close_fd(cmd->fd[0]);
	}
	if (cmd->fd[1] != STDOUT)
	{
		if (dup2(cmd->fd[1], STDOUT) < 0)
			exit_shell(minishell);
		close_fd(cmd->fd[1]);
	}
}

static void	exec_cmd(t_minishell *minishell, t_cmd *cmd, int *fd, int fdd)
{
	if (dup2(fdd, 0) < 0 || (cmd->next && dup2(fd[1], 1) < 0))
		exit_shell(minishell);
	redir_file(minishell, cmd);
	if (cmd->is_builtin == true)
		cmd->command(cmd->ac, cmd->av, minishell);
	else
	{
		execve(cmd->av[CMD], cmd->av, minishell->env);
		print_errno(cmd->av[CMD]);
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
			exit_errno(minishell, "pipe");
		pid = fork();
		if (pid < 0)
			exit_errno(minishell, "fork");
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

	if (command->ac < 0)
		return ;
	backup[0] = dup(STDIN);
	backup[1] = dup(STDOUT);
	if (backup[0] == RET_ERROR || backup[1] == RET_ERROR)
	{
		default_fd(backup);
		return (print_errno("dup"));
	}
	tmp = command;
	nb_cmd = 0;
	while (tmp)
	{
		tmp = tmp->next;
		nb_cmd++;
	}
	tmp = command;
	exec_pipe(minishell, tmp, nb_cmd);
	default_fd(backup);
}