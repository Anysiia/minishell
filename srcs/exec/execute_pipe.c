/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:18:40 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/06 12:24:11 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execve_cmd(t_minishell *minishell, t_cmd *cmd)
{
	char	*cmd_name;
	char	**cmd_arg;
	t_cmd	*next;
	t_cmd	*current;

	cmd_name = cmd->binary;
	cmd_arg = cmd->av;
	if (minishell->lexer)
		free_lexer(minishell->lexer);
	if (minishell->envp)
		free_envp(&minishell->envp);
	close_fd(minishell->back_stdin);
	close_fd(minishell->back_stdout);
	rl_clear_history();
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
	minishell->cmd = NULL;
	execve(cmd_name, cmd_arg, minishell->env);
	print_errno(cmd->av[CMD], EXECVE);
}

static void	error_cmd(t_minishell *minishell, char *cmd_name, int errno_code)
{
	errno = errno_code;
	print_errno(cmd_name, EXECVE);
	exit_shell(minishell);
}

static void	exec_cmd(t_minishell *minishell, t_cmd *cmd, int *fd, int fdd)
{
	if (redir_file(cmd, fd, fdd, minishell->nb_cmd) == RET_ERROR)
		exit_shell(minishell);
	if (cmd->ac == 0)
	{
		set_state(0);
		exit_shell(minishell);
	}
	else if (cmd->is_builtin == true)
		cmd->command(cmd->ac, cmd->av, minishell);
	else if (!cmd->binary || (cmd->binary[0] != '/' && cmd->binary[0] != '.'))
		error_cmd(minishell, cmd->av[CMD], ENOENT);
	else if (is_directory(cmd->binary))
		error_cmd(minishell, cmd->av[CMD], EISDIR);
	else if (cmd->binary[0] == '.')
	{
		print_dot_error(cmd->av[CMD]);
		exit_shell(minishell);
	}
	else
		execve_cmd(minishell, cmd);
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
		if (minishell->nb_cmd > 1)
			close_fd(fd[1]);
		close_fd(fdd);
		fdd = fd[0];
		tmp = tmp->next;
	}
	wait_childs(pid, minishell->nb_cmd);
	default_fd(minishell);
}
